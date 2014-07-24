namespace Fractals

open FractalFunctions
open System.ComponentModel

type Circles2Parameters(radius, minimum) =

    let mutable _radius = radius
    let mutable _minimum = minimum

    static member Default =
        new Circles2Parameters(200.0, 2.0)

    [<Category("Parameters")>]
    [<Description("The starting radius of the circles")>]
    member this.Radius  
        with get () = _radius
        and set (value) = _radius <- value

    [<Category("Parameters")>]
    [<Description("The minimum radius to stop with")>]
    member this.Minimum
        with get () = _minimum
        and set (value) = _minimum <- value

    interface IParameters with

        member this.Name = "Circles2"


// Taken from https://github.com/relentless/FractalFun
type Circles2(parameters: Circles2Parameters) =

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

        if radius > parameters.Minimum then

            drawings.Circle x y (int radius) <| randCol seed

            let nextDist = radius/2.0

            sphere drawings (x+radius) (y) nextDist (seed*2) (iteration+1)
            sphere drawings (x-radius) (y) nextDist (seed/2) (iteration+1)
            sphere drawings (x) (y+radius) nextDist (seed/3) (iteration+1)
            sphere drawings (x) (y-radius) nextDist (seed*3) (iteration+1)

    interface IFractal with

        member this.Title = "Circles2"
        member this.Parameters = parameters :> IParameters

        member this.Calculate drawings = 
            Helpers.measureTime sphere
                drawings
                (float drawings.Width/2.0) 
                (float drawings.Height/2.0)
                200.0
                System.DateTime.Now.Millisecond
                0