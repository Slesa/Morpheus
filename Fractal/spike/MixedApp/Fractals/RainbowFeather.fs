namespace Fractals

open FractalFunctions

// Taken from https://github.com/relentless/FractalFun
module RainbowFeather =

    let branchAngle = 0.25
    let lengthMultiplier = 1.3/2.0
    let widthModifier = -0.5
    let startWidth = 3.0
    let startLength = 250.0
    let numBranches = 5

    let asColour (drawings: IFractalDrawing) x y factor =
        let centre = Helpers.ImageCentre drawings
        let centredX = abs ((centre - startWidth/2.0) - x)
        abs ((int ((centredX+y)*factor)%510) - 255)

    let getColour (drawings: IFractalDrawing) x y =
        (asColour drawings x y 2.0, asColour drawings x y 1.5, asColour drawings x y 2.5)

    let rec endpoints x y angle length iteration = seq {
        let segLength = length / float numBranches
        yield endpoint x y (pi*angle) (segLength*float iteration)
        if iteration < numBranches then
            yield! endpoints x y angle length (iteration+1)
    }

    let rec branch (drawings: IFractalDrawing) x y length width colour angle =
        if width > 0.0 then
            let angleDegrees = (pi * angle)
            drawings.Line x y angleDegrees length width colour

            endpoints x y angle length 0
            |> Seq.iteri ( fun i (nextX, nextY) -> 
                let stageLengthMultiplier = (1.0/float numBranches*float i)
                branch drawings nextX nextY (length*lengthMultiplier*stageLengthMultiplier) (width+widthModifier) (getColour drawings x y) (angle+branchAngle)
                branch drawings nextX nextY (length*lengthMultiplier*stageLengthMultiplier) (width+widthModifier) (getColour drawings x y) (angle-branchAngle)
                )

    let execute(drawings: IFractalDrawing) = 
        let centre = Helpers.ImageCentre drawings
        branch drawings (centre - startWidth/2.0) 70.0 startLength startWidth startColour 0.5
        drawings.Show "Rainbow Feather"