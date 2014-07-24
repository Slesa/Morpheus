namespace Fractals

open FractalFunctions
open System.ComponentModel

type KidneyParameters(smallBranch, largeBranch, smallLength, largeLength, smallWidth, largeWidth, startWidth, startLength, startColour, endColour) =

    let mutable _smallBranch = smallBranch
    let mutable _largeBranch = largeBranch
    let mutable _smallLength = smallLength
    let mutable _largeLength = largeLength
    let mutable _smallWidth = smallWidth
    let mutable _largeWidth = largeWidth
    let mutable _startWidth = startWidth
    let mutable _startLength = startLength
    let mutable _startColour = startColour
    let mutable _endColour = endColour

    static member Default =
        new KidneyParameters(0.11, 0.16, 0.85, 0.9, -2.2, -1.8, 30.0, 80.0, (40, 20, 0), (240, 0, 0))

    [<Category("Parameters")>]
    [<Description("The small branch angle which is added")>]
    member this.SmallBranchAngle
        with get () = _smallBranch
        and set (value) = _smallBranch <- value

    [<Category("Parameters")>]
    [<Description("The large branch angle which is subtracted")>]
    member this.LargeBranchAngle
        with get () = _largeBranch
        and set (value) = _largeBranch <- value

    [<Category("Parameters")>]
    [<Description("The small multiplier of the length")>]
    member this.SmallLengthMultiplier
        with get () = _smallLength
        and set (value) = _smallLength <- value

    [<Category("Parameters")>]
    [<Description("The large multiplier of the length")>]
    member this.LargeLengthMultiplier
        with get () = _largeLength
        and set (value) = _largeLength <- value

    [<Category("Parameters")>]
    [<Description("The small modifier of the width")>]
    member this.SmallWidthModifier
        with get () = _smallWidth
        and set (value) = _smallWidth <- value

    [<Category("Parameters")>]
    [<Description("The large modifier of the width")>]
    member this.LargeWidthModifier
        with get () = _largeWidth
        and set (value) = _largeWidth <- value

    [<Category("Parameters")>]
    [<Description("The length to start with")>]
    member this.StartLength
        with get () = _startLength
        and set (value) = _startLength <- value

    [<Category("Parameters")>]
    [<Description("The width to start with")>]
    member this.StartWidth
        with get () = _startWidth
        and set (value) = _startWidth <- value

    [<Category("Colours")>]
    [<Description("The colour to start with")>]
    member this.StartColour
        with get () = _startColour
        and set (value) = _startColour <- value

    [<Category("Colours")>]
    [<Description("The colour to end with")>]
    member this.EndColour
        with get () = _endColour
        and set (value) = _endColour <- value

    interface IParameters with

        member this.Name = "Kidney"

// Taken from https://github.com/relentless/FractalFun
type Kidney(parameters: KidneyParameters) =

    let numSteps = int (parameters.StartWidth / -parameters.LargeWidthModifier)
    let step = colourStep parameters.StartColour parameters.EndColour numSteps

    let rec branch (drawings: IFractalDrawing) x y length width colour angle =
        if width > 0.0 then
            let angleDegrees = (pi * angle)
            drawings.Line x y angleDegrees length width colour
            let nextX, nextY = endpoint x y angleDegrees length

            branch drawings nextX nextY (length*parameters.SmallLengthMultiplier) (width+parameters.SmallWidthModifier) (colour |> next step) (angle+parameters.SmallBranchAngle)
            branch drawings nextX nextY (length*parameters.LargeLengthMultiplier) (width+parameters.LargeWidthModifier) (colour |> next step) (angle-parameters.LargeBranchAngle)

    interface IFractal with

        member this.Title = "Kidney"
        member this.Parameters = parameters :> IParameters

        member this.Calculate drawings = 
            let centre = Helpers.ImageCentre drawings
            branch drawings (centre - 50.0) 200.0 parameters.StartLength parameters.StartWidth parameters.StartColour 0.5

