namespace Fractals
open System

[<Interface>]
type IFractalDrawing = 

    abstract member Width : int
    abstract member Height : int

    abstract member Line: float -> float -> float 
        -> float -> float -> (int * int * int ) 
        -> unit

    abstract member Circle: float -> float -> int -> (int * int * int) -> unit

    abstract member Show: string -> unit

