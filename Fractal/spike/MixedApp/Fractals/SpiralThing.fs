namespace Fractals

open FractalFunctions
open System.ComponentModel

type SpiralThingParameters(leftBranch, rightBranch, startWidth, startLength, widthMultiplier, lengthMultiplier, rightMultiplier) =

    let mutable _leftBranch = leftBranch
    let mutable _rightBranch = rightBranch
    let mutable _startWidth = startWidth
    let mutable _startLength = startLength
    let mutable _widthMultiplier = widthMultiplier
    let mutable _lengthMultiplier = lengthMultiplier
    let mutable _rightMultiplier = rightMultiplier

    static member Default =
        new SpiralThingParameters(0.15, 0.5, 16.0, 100.0, 5.5/6.0, 5.5/6.0, 0.5)

    [<Category("Parameters")>]
    [<Description("The angle of the branches on the left side")>]
    member this.LeftBranchAngle
        with get () = _leftBranch
        and set (value) = _leftBranch <- value

    [<Category("Parameters")>]
    [<Description("The angle of the branches branches on the right side")>]
    member this.RightBranchAngle
        with get () = _rightBranch
        and set (value) = _rightBranch <- value

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
    [<Description("The multiplier of the width")>]
    member this.WidthMultiplier
        with get () = _widthMultiplier
        and set (value) = _widthMultiplier <- value

    [<Category("Parameters")>]
    [<Description("The multiplier of the length")>]
    member this.LengthMultiplier
        with get () = _lengthMultiplier
        and set (value) = _lengthMultiplier <- value

    [<Category("Parameters")>]
    [<Description("The multiplier of the length")>]
    member this.RightMultiplier
        with get () = _rightMultiplier
        and set (value) = _rightMultiplier <- value

    interface IParameters with

        member this.Name = "Spiral Thing"

// Taken from https://github.com/relentless/FractalFun
type SpiralThing(parameters: SpiralThingParameters) =

    let rec branch (drawings: IFractalDrawing) x y length width colour angle =
        if width > 0.4 then
            let angleDegrees = (pi*angle)
            drawings.Line x y angleDegrees length width colour
            let nextX, nextY = endpoint x y angleDegrees (length-2.0)

            branch drawings nextX nextY (length*parameters.LengthMultiplier) (width*parameters.WidthMultiplier) colour (angle+parameters.LeftBranchAngle)
            branch drawings nextX nextY (length*0.5) (width*0.5) colour (angle-parameters.RightBranchAngle)

    interface IFractal with

        member this.Title = "Spiral Thing"
        member this.Parameters = parameters :> IParameters

        member this.Calculate drawings = 
            let centre = Helpers.ImageCentre drawings
            branch drawings (centre - parameters.StartWidth/2.0) 150.0 parameters.StartLength parameters.StartWidth (0,0,0) 0.5


