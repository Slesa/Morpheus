namespace Fractals

open FractalFunctions
open System.ComponentModel

type FernParameters(branchAngle, startWidth, startLength, minGreen, maxGreen) =

    let mutable _branchAngle = branchAngle
    let mutable _startWidth = startWidth
    let mutable _startLength = startLength
    let mutable _minGreen = minGreen
    let mutable _maxGreen = maxGreen

    static member Default =
        new FernParameters(0.45, 3.5, 105.0, 80.0, 200.0)

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
    [<Description("The minimum green value")>]
    member this.MinGreen
        with get () = _minGreen
        and set (value) = _minGreen <- value

    [<Category("Parameters")>]
    [<Description("The maximum green value")>]
    member this.MaxGreen
        with get () = _maxGreen
        and set (value) = _maxGreen <- value

    interface IParameters with

        member this.Name = "Fern"

// Taken from https://github.com/relentless/FractalFun
type Fern(parameters: FernParameters) =

    let getColour width =
        (0, int (parameters.MaxGreen - ((parameters.MaxGreen-parameters.MinGreen)/parameters.StartWidth*width)), 0)

    let rec branch (drawings: IFractalDrawing) x y length width colour angle bendAngle =
        if width>0.4 then
            let angleDegrees = (pi*angle)
            drawings.Line x y angleDegrees length width colour

            let (nextX, nextY) = endpoint x y angleDegrees length

            branch drawings nextX nextY (length*0.3) (width*0.8) (getColour width) (angle+parameters.BranchAngle) bendAngle
            branch drawings nextX nextY (length*0.8) (width*0.9) (getColour width) (angle+bendAngle) bendAngle
            branch drawings nextX nextY (length*0.3) (width*0.8) (getColour width) (angle-parameters.BranchAngle) bendAngle

    interface IFractal with

        member this.Title = "Fern"
        member this.Parameters = parameters :> IParameters

        member this.Calculate drawings =
            let centre = Helpers.ImageCentre drawings
            branch drawings (centre - parameters.StartWidth/2.0) 10.0 parameters.StartLength parameters.StartWidth startColour 0.5 0.01
