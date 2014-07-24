namespace Fractals

open FractalFunctions
open System.ComponentModel

type RainbowFeatherParameters(numBranches, branchAngle, startWidth, startLength, widthModifier, lengthMultiplier) =

    let mutable _numBranches = numBranches
    let mutable _branchAngle = branchAngle
    let mutable _startWidth = startWidth
    let mutable _startLength = startLength
    let mutable _widthModifier = widthModifier
    let mutable _lengthMultiplier = lengthMultiplier

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

    static member Default =
        new RainbowFeatherParameters(5, 0.25, 3.0, 250.0, -0.5, 1.3/2.0)

    interface IParameters with

        member this.Name = "Rainbow Feather"

// Taken from https://github.com/relentless/FractalFun
type RainbowFeather(parameters: RainbowFeatherParameters) =

    let asColour (drawings: IFractalDrawing) x y factor =
        let centre = Helpers.ImageCentre drawings
        let centredX = abs ((centre - parameters.StartWidth/2.0) - x)
        abs ((int ((centredX+y)*factor)%510) - 255)

    let getColour (drawings: IFractalDrawing) x y =
        (asColour drawings x y 2.0, asColour drawings x y 1.5, asColour drawings x y 2.5)

    let rec endpoints x y angle length iteration = seq {
        let segLength = length / float parameters.NumBranches
        yield endpoint x y (pi*angle) (segLength*float iteration)
        if iteration < parameters.NumBranches then
            yield! endpoints x y angle length (iteration+1)
    }

    let rec branch (drawings: IFractalDrawing) x y length width colour angle =
        if width > 0.0 then
            let angleDegrees = (pi * angle)
            drawings.Line x y angleDegrees length width colour

            endpoints x y angle length 0
            |> Seq.iteri ( fun i (nextX, nextY) -> 
                let stageLengthMultiplier = (1.0/float parameters.NumBranches*float i)
                branch drawings nextX nextY (length*parameters.LengthMultiplier*stageLengthMultiplier) (width+parameters.WidthModifier) (getColour drawings x y) (angle+parameters.BranchAngle)
                branch drawings nextX nextY (length*parameters.LengthMultiplier*stageLengthMultiplier) (width+parameters.WidthModifier) (getColour drawings x y) (angle-parameters.BranchAngle)
                )

    interface IFractal with

        member this.Title = "Rainbow Feather"
        member this.Parameters = parameters :> IParameters

        member this.Calculate drawings =
            let centre = Helpers.ImageCentre drawings
            branch drawings (centre - parameters.StartWidth/2.0) 70.0 parameters.StartLength parameters.StartWidth startColour 0.5