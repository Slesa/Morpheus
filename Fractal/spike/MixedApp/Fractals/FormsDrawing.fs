namespace Fractals
open System
open System.Drawing
open System.Windows.Forms
open FractalFunctions

type FormsDrawing(canvas) = 
    
    let image = canvas
    let graphics  = Graphics.FromImage(image)
    let width = canvas.Width
    let height = canvas.Height

    let drawLineTo (target: Graphics) (brush: Brush) (x1: float) (y1: float) (x2: float) (y2: float) (width: float) =
       let origin = new PointF((single)x1, (single)y1)
       let destination = new PointF((single)x2, (single)y2)
       let pen = new Pen(brush, (single)width)
       target.DrawLine(pen, origin, destination)

    let drawLine (target: Graphics) (brush: Brush) (x: float) (y: float) (angle: float) (length: float) (width: float) (height: float) =
       let x_end, y_end = endpoint x y angle length
       let origin = new PointF((single)x, (single)(y |> flip height))
       let destination = new PointF((single)x_end, (single)(y_end |> flip height))
       let pen = new Pen(brush, (single)width)
       target.DrawLine(pen, origin, destination)

    let drawCircle (target : Graphics) (brush : Brush) (x : float) (y : float) (radius : int) (height : float) =
        target.FillEllipse(brush, (int x-radius), int (flip height y)-radius, radius*2, radius*2)


    interface IFractalDrawing with
          
        member this.Width = width
        member this.Height = height

        member this.LineTo x1 y1 x2 y2 width colour =
            drawLineTo graphics (colour |> brush) x1 y1 x2 y2 width

        member this.Line x y angle length width colour =
            drawLine graphics (colour |> brush) x y angle length width ((double)height)

        member this.Circle x y radius colour =
            drawCircle graphics (colour |> brush) x y radius (float height)
