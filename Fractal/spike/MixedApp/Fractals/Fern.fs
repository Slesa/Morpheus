namespace Fractals

open FractalFunctions
open FractalForms

// Taken from https://github.com/relentless/FractalFun
module Fern =

    let branchAngle = 0.45
    let startWidth = 3.5
    let startLength = 125.0

    let minGreen = 80.0
    let maxGreen = 200.0

    let getColour width =
        (0, int (maxGreen - ((maxGreen-minGreen)/startWidth*width)), 0)

    let fractalForm = new SizedFractalForm()

    let rec branch x y length width colour angle bendAngle =
        if width>0.4 then
            let angleDegrees = (pi*angle)
            fractalForm.Line x y angleDegrees length width colour

            let (nextX, nextY) = endpoint x y angleDegrees length

            branch nextX nextY (length*0.3) (width*0.8) (getColour width) (angle+branchAngle) bendAngle
            branch nextX nextY (length*0.8) (width*0.9) (getColour width) (angle+bendAngle) bendAngle
            branch nextX nextY (length*0.3) (width*0.8) (getColour width) (angle-branchAngle) bendAngle

    let execute() = 
        branch (fractalForm.ImageCentre - startWidth/2.0) 100.0 startLength startWidth startColour 0.5 0.01

        fractalForm.CreateForm("Fern").Show() |> ignore
