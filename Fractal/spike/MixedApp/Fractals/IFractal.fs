namespace Fractals
open System

[<Interface>]
type IFractal =

    abstract member Title : string
    abstract member Calculate: IFractalDrawing -> unit
