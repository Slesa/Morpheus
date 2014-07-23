namespace Fractals

open FractalFunctions

// Taken from https://github.com/relentless/FractalFun
type ColourTree(parameters: IParameters) =
    
    let branchAngle = 0.11
    let lengthMultiplier = 5.0/6.0
    let widthModifier = -0.8
    let startWidth = 12.0

    let startColour = (60, 30, 0) // brown
    let endColour = (130, 150, 255) // green

    let numSteps = int (startWidth / -widthModifier)
    let step = colourStep startColour endColour numSteps

    let rec branch (drawings: IFractalDrawing) x y length width colour angle =
        if width > 0.0 then
            let angleDegrees = (pi * angle)
            drawings.Line x y angleDegrees length width colour
            let nextX, nextY = endpoint x y angleDegrees length

            branch drawings nextX nextY (length*lengthMultiplier) (width+widthModifier) (colour |> next step) (angle+branchAngle)
            branch drawings nextX nextY (length*lengthMultiplier) (width+widthModifier) (colour |> next step) (angle-branchAngle)

    interface IFractal with

        member this.Title = "Colour Tree"
        member this.Parameters = parameters

        member this.Calculate drawings = 
            let centre = Helpers.ImageCentre drawings
            branch drawings (centre - startWidth/2.0) 50.0 100.0 startWidth startColour 0.5

