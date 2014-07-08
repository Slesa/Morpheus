module FractalForm

open FractalFunctions
open System.Drawing
open System.Windows.Forms

let formWidth, formHeight = 1000, 800
let form = new Form(Width=formWidth, Height=formHeight)
let box = new PictureBox(BackColor=Color.White, Dock=DockStyle.Fill)
let image = new Bitmap(formWidth, formHeight)

let graphics = Graphics.FromImage(image)
let imageCentre = float formWidth/2.0

box.Image <- image
form.Controls.Add(box)

let line x y angle length width colour =
    drawLine graphics (colour |> brush) x y angle length width ((double)formHeight)
