namespace Fractals
open System
open System.Drawing
open System.Windows.Forms
open FractalFunctions

type FormsDrawing(width : int, height : int) = 
    
    let image = new Bitmap(width, height)
    let graphics  = Graphics.FromImage(image)

    let drawLine (target: Graphics) (brush: Brush) (x: float) (y: float) (angle: float) (length: float) (width: float) (height: float) =
       let x_end, y_end = endpoint x y angle length
       let origin = new PointF((single)x, (single)(y |> flip height))
       let destination = new PointF((single)x_end, (single)(y_end |> flip height))
       let pen = new Pen(brush, (single)width)
       target.DrawLine(pen, origin, destination)

    let drawCircle (target : Graphics) (brush : Brush) (x : float) (y : float) (radius : int) (height : float) =
        target.FillEllipse(brush, (int x-radius), int (flip height y)-radius, radius*2, radius*2)

    let createForm title =
        let form = new Form(Text=title, Width=width, Height=height)
        let box = new PictureBox(BackColor=Color.White, Dock=DockStyle.Fill)
        box.Image <- image
        form.Controls.Add(box)
        form

    interface IFractalDrawing with
          
        member this.Width = width
        member this.Height = height

        member this.Line x y angle length width colour =
            drawLine graphics (colour |> brush) x y angle length width ((double)height)

        member this.Circle x y radius colour =
            drawCircle graphics (colour |> brush) x y radius (float height)

        member this.Show title =
            (createForm title).Show() |> ignore
