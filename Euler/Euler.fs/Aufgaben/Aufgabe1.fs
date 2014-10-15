namespace Aufgaben

[<Interface>]
type Loesung1 = 
    abstract member Calculate : int -> int

type Aufgabe1() = 

    let rec Calc result number limit (op : int -> int -> int) : int =
        if limit = 0 then 
            0
        else
        if (limit % number).Equals 0 then
            op number (Calc result number (limit-1) op)
        else
            Calc result number (limit-1) op
         
    let Calc number limit (op : int -> int -> int) =
       Calc 0 number limit op
        
    let Add number limit =
        Calc number limit ( + )

    let Subtract number limit =
        Calc number limit ( - )

    interface Loesung1 with
        member this.Calculate limit = 
            let by5 = Add 5 (limit-1)
            let by3 = by5 + Add 3 limit
            let result = by3 - Subtract 15 limit
            result

    interface Aufgabe with

        member this.Title = "Aufgabe 1"
        member this.Run() =
            let result = (this :> Loesung1).Calculate 1000
            result.ToString();


