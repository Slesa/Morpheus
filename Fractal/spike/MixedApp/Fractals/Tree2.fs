namespace Fractals

open FractalFunctions
open System.ComponentModel

type Tree2(parameters: IParameters) =

    let lineWidth = 1.0
    let colour = (180, 230, 0)
    let window = (-2.0, -0.5, 2.0, 2.5)

    let wleft (x, _, _, _) = x
    let wtop (_, y, _, _) = y
    let wlength (_, _, l, _) = l
    let wheight (_, _, _, h) = h
    
//    let scaleUp x1 y1 x2 y2 =
//        (x1-(wleft window)) (y1-(wtop window)) (x2+(wlength window)) (y2+(wheight window))

    let rec drawLines (drawings: IFractalDrawing) limit l h =
        
        if l <= limit then
            let x = -2.0 + (4.0*l-2.0) * float h
            let y = 2.0-float h
            // let 
            drawings.LineTo (x - float h) (y + float h/2.0) (x - float h) y lineWidth colour
            drawings.LineTo (x - float h) y (x + float h) y lineWidth colour
            drawings.LineTo (x + float h) y (x + float h) (y + float h/2.0) lineWidth colour
            drawLines drawings limit (l+1.0) h

    let rec calculate (drawings: IFractalDrawing) iteration =
        
        drawings.LineTo 0.0 0.0 0.0 0.1 lineWidth colour
        if iteration <= 7 then
            
            let h = 2.0 ** (1.0 - float iteration)
            let limit = 2.0 ** float iteration
            drawLines drawings limit 1.0 h

            calculate drawings (iteration+1)

         
    interface IFractal with

        member this.Title = "Treeh2"
        member this.Parameters = parameters

        member this.Calculate drawings =

            Helpers.measureTime calculate drawings 1

