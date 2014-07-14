namespace Fractals

open FractalFunctions
open FractalForms

// Taken from https://github.com/relentless/FractalFun
module Circles = 

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

    let fractalForm = new SizedFractalForm()

    let rec sphere x y radius seed iteration =

        if iteration < 5 then

            fractalForm.Circle x y (int radius) <| randCol seed

            let nextDist = radius/2.0

            sphere (x-nextDist) (y-nextDist) nextDist (seed*2) (iteration+1)
            sphere (x+nextDist) (y-nextDist) nextDist (seed/2) (iteration+1)
            sphere (x+nextDist) (y+nextDist) nextDist (seed/3) (iteration+1)
            sphere (x-nextDist) (y+nextDist) nextDist (seed*3) (iteration+1)

    let execute() =
        sphere
            (float fractalForm.FormWidth/2.0) 
            (float fractalForm.FormHeight/2.0)
            200.0
            System.DateTime.Now.Millisecond
            0
        fractalForm.CreateForm("Circle").Show() |> ignore