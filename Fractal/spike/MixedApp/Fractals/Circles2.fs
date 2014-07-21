namespace Fractals

open FractalFunctions
open FractalForms


module Circles2 =

    let next colour =
        let red, green, blue = colour
        (red, green+30, blue)

    let rand seed =
        let rnd = System.Random(seed)
        rnd.Next(0, 255)

    let randCol seed =
        let r = rand seed
        let g = rand r
        let b = rand g
        (r, g, b)

    let rec sphere (drawings: IFractalDrawing) x y radius seed iteration =

        if radius > 2.0 then

            drawings.Circle x y (int radius) <| randCol seed

            let nextDist = radius/2.0

            sphere drawings (x+radius) (y) nextDist (seed*2) (iteration+1)
            sphere drawings (x-radius) (y) nextDist (seed/2) (iteration+1)
            sphere drawings (x) (y+radius) nextDist (seed/3) (iteration+1)
            sphere drawings (x) (y-radius) nextDist (seed*3) (iteration+1)

    let execute(drawings: IFractalDrawing) =
        Helpers.measureTime sphere
            drawings
            (float drawings.Width/2.0) 
            (float drawings.Height/2.0)
            200.0
            System.DateTime.Now.Millisecond
            0
        drawings.Show "Circle2"