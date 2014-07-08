module FractalFunctions

open System
open System.Drawing


// *** Colors *******************************************************

let red (r, _, _) = r
let green (_, g, _) = g
let blue (_, _, b) = b

let startColour = (60, 30, 0) // brown
let endColour = (0, 170, 0)

let brush colour = new SolidBrush(Color.FromArgb(colour |> red, colour |> green, colour |> blue))


// *** Radients *****************************************************

let endpoint x y angle length =
    x + length * cos angle,
    y + length * sin angle

let pi = Math.PI

let flip height y = height-y

// *** Graphics *****************************************************

let drawLine (target: Graphics) (brush: Brush) (x: float) (y: float) (angle: float) (length: float) (width: float) (height: float) =
   let x_end, y_end = endpoint x y angle length
   let origin = new PointF((single)x, (single)(y |> flip height))
   let destination = new PointF((single)x_end, (single)(y_end |> flip height))
   let pen = new Pen(brush, (single)width)
   target.DrawLine(pen, origin, destination)

