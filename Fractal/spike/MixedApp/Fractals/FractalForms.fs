namespace Fractals

open FractalFunctions
open System.Drawing
open System.Windows.Forms

// Taken from https://github.com/relentless/FractalFun
module FractalForms =

    type FractalForm(formWidth : int, formHeight : int) =

        [<Literal>]
        let DefaultWidth = 1000
        [<Literal>]
        let DefaultHeight = 800
        let image = new Bitmap(formWidth, formHeight)
        let graphics  = Graphics.FromImage(image)

        member this.FormWidth = formWidth
        member this.FormHeight = formHeight
        member this.ImageCentre = float formWidth / 2.0
        member this.Image = image
        member this.Graphics  = graphics

        member this.CreateForm(title) =
            let form = new Form(Text=title, Width=formWidth, Height=formHeight)
            let box = new PictureBox(BackColor=Color.White, Dock=DockStyle.Fill)
            box.Image <- this.Image
            form.Controls.Add(box)
            form

        member this.Line x y angle length width colour =
            drawLine this.Graphics (colour |> brush) x y angle length width ((double)this.FormHeight)

        member this.Circle x y radius colour =
            drawCircle this.Graphics (colour |> brush) x y radius (float this.FormHeight)


    type SizedFractalForm() =
        inherit FractalForm(1000, 800)
        //inherit FractalForm(FractalForm.DefaultWidth, DefaultHeight)
