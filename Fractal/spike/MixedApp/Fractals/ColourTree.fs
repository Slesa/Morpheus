namespace Fractals

open FractalFunctions

type ColourTreeParameters(branchAngle, startWidth, widthModifier, startColour, endColour) =

    let mutable _branchAngle = branchAngle
    let mutable _startWidth = startWidth
    let mutable _widthModifier = widthModifier
    let mutable _startColour = startColour
    let mutable _endColour = endColour

    static member Default =
        new ColourTreeParameters(0.11, 12.0, -0.8, (60,30,0), (130,150,255))

    member this.BranchAngle
        with get () = _branchAngle
        and set (value) = _branchAngle <- value

    member this.StartWidth
        with get () = _startWidth
        and set (value) = _startWidth <- value

    member this.WidthModifier
        with get () = _widthModifier
        and set (value) = _widthModifier <- value

    member this.StartColour
        with get () = _startColour
        and set (value) = _startColour <- value

    member this.EndColour
        with get () = _endColour
        and set (value) = _endColour <- value

    interface IParameters with

       member this.Name = "ColourTree"

// Taken from https://github.com/relentless/FractalFun
type ColourTree(parameters: ColourTreeParameters) =
    
    let lengthMultiplier = 5.0/6.0

    let numSteps = int (parameters.StartWidth / -parameters.WidthModifier)
    let step = colourStep parameters.StartColour parameters.EndColour numSteps

    let rec branch (drawings: IFractalDrawing) x y length width colour angle =
        if width > 0.0 then
            let angleDegrees = (pi * angle)
            drawings.Line x y angleDegrees length width colour
            let nextX, nextY = endpoint x y angleDegrees length

            branch drawings nextX nextY (length*lengthMultiplier) (width+parameters.WidthModifier) (colour |> next step) (angle+parameters.BranchAngle)
            branch drawings nextX nextY (length*lengthMultiplier) (width+parameters.WidthModifier) (colour |> next step) (angle-parameters.BranchAngle)

    interface IFractal with

        member this.Title = "Colour Tree"
        member this.Parameters = parameters :> IParameters

        member this.Calculate drawings = 
            let centre = Helpers.ImageCentre drawings
            branch drawings (centre - parameters.StartWidth/2.0) 50.0 100.0 parameters.StartWidth parameters.StartColour 0.5

