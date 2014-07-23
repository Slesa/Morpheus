namespace Fractals

open FractalFunctions

// Taken from https://github.com/relentless/FractalFun
type Fern(parameters: IParameters) =

    let branchAngle = 0.45
    let startWidth = 3.5
    let startLength = 105.0

    let minGreen = 80.0
    let maxGreen = 200.0

    let getColour width =
        (0, int (maxGreen - ((maxGreen-minGreen)/startWidth*width)), 0)

    let rec branch (drawings: IFractalDrawing) x y length width colour angle bendAngle =
        if width>0.4 then
            let angleDegrees = (pi*angle)
            drawings.Line x y angleDegrees length width colour

            let (nextX, nextY) = endpoint x y angleDegrees length

            branch drawings nextX nextY (length*0.3) (width*0.8) (getColour width) (angle+branchAngle) bendAngle
            branch drawings nextX nextY (length*0.8) (width*0.9) (getColour width) (angle+bendAngle) bendAngle
            branch drawings nextX nextY (length*0.3) (width*0.8) (getColour width) (angle-branchAngle) bendAngle

    interface IFractal with

        member this.Title = "Fern"
        member this.Parameters = parameters

        member this.Calculate drawings =
            let centre = Helpers.ImageCentre drawings
            branch drawings (centre - startWidth/2.0) 10.0 startLength startWidth startColour 0.5 0.01
