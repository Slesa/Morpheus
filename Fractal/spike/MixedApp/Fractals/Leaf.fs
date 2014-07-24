namespace Fractals

open FractalFunctions
open System.ComponentModel

type LeafParameters(numBranches, branchAngle, startWidth, startLength, widthModifier, lengthMultiplier, startColour, endColour) =

    let mutable _numBranches = numBranches
    let mutable _branchAngle = branchAngle
    let mutable _startWidth = startWidth
    let mutable _startLength = startLength
    let mutable _widthModifier = widthModifier
    let mutable _lengthMultiplier = lengthMultiplier
    let mutable _startColour = startColour
    let mutable _endColour = endColour

    static member Default =
        new LeafParameters(6, 0.25, 3.0, 500.0, -0.6, 1.0/2.0, (0, 80, 0), (0, 180, 0))

    [<Category("Parameters")>]
    [<Description("The number of branches to iterate")>]
    member this.NumBranches
        with get () = _numBranches
        and set (value) = _numBranches <- value

    [<Category("Parameters")>]
    [<Description("The angle between branches")>]
    member this.BranchAngle
        with get () = _branchAngle
        and set (value) = _branchAngle <- value

    [<Category("Parameters")>]
    [<Description("The width to start with")>]
    member this.StartWidth
        with get () = _startWidth
        and set (value) = _startWidth <- value

    [<Category("Parameters")>]
    [<Description("The length to start with")>]
    member this.StartLength 
        with get () = _startLength
        and set (value) = _startLength <- value

    [<Category("Parameters")>]
    [<Description("The modifier of the width")>]
    member this.WidthModifier
        with get () = _widthModifier
        and set (value) = _widthModifier <- value

    [<Category("Parameters")>]
    [<Description("The multiplier of the length")>]
    member this.LengthMultiplier
        with get () = _lengthMultiplier
        and set (value) = _lengthMultiplier <- value

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

        member this.Name = "Leaf"

// Taken from https://github.com/relentless/FractalFun
type Leaf(parameters: LeafParameters) =

    let numSteps = int (parameters.StartWidth / -parameters.WidthModifier)
    let step = colourStep parameters.StartColour parameters.EndColour numSteps

    let rec endpoints x y length angle iteration = seq {
        let segLength = length / float parameters.NumBranches
        yield endpoint x y (pi*angle) (segLength*float iteration)
        if iteration < parameters.NumBranches then
            yield! endpoints x y angle length (iteration+1)
    }

    let rec branch (drawings: IFractalDrawing) x y length width colour angle =
        if width > 0.0 then
            let angleDegrees = (pi*angle)
            drawings.Line x y angleDegrees length width colour

            endpoints x y angle length 0
            |> Seq.iteri (fun i (nextX, nextY) ->
                let stageLengthMultiplier = 1.0 - (0.5/float parameters.NumBranches*float i)
                let stageWidthMultiplier = 1.0 - (0.1/float parameters.NumBranches*float i)
                branch drawings nextX nextY (length*parameters.LengthMultiplier*stageLengthMultiplier) (width*stageWidthMultiplier+parameters.WidthModifier) (colour |> next step) (angle+parameters.BranchAngle)
                branch drawings nextX nextY (length*parameters.LengthMultiplier*stageLengthMultiplier) (width*stageWidthMultiplier+parameters.WidthModifier) (colour |> next step) (angle-parameters.BranchAngle)
                )

    interface IFractal with

        member this.Title = "Leaf"
        member this.Parameters = parameters :> IParameters

        member this.Calculate drawings =
            let centre = Helpers.ImageCentre drawings
            branch drawings (centre - parameters.StartWidth/2.0) 150.0 parameters.StartLength parameters.StartWidth parameters.StartColour 0.5


