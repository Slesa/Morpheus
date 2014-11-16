namespace Aufgaben


module Number =
    let Divides num by =
        match num%by with
        | 0 -> true
        | _ -> false
    let Divides64 num by =
        match num%by with
        | 0L -> true
        | _ -> false


[<Interface>]
type INumbers =
    abstract member IsPrime : int -> bool
    abstract member IsPrime64 : int64 -> bool

type Numbers() =

    interface INumbers with
        member this.IsPrime64 num =
            let limit = max (num/2L) 2L

            let sequence = seq { limit .. -1L .. 2L }
            let divisors = Seq.tryFind (fun a -> Number.Divides64 num a) sequence
            match divisors with
            | None -> true
            | Some _ -> false

        member this.IsPrime num =
            let limit = max (num/2) 2

            let sequence = seq { limit .. -1 .. 2 }
            let divisors = Seq.tryFind (fun a -> Number.Divides num a) sequence
            match divisors with
            | None -> true
            | Some _ -> false

