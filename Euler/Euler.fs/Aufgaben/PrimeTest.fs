namespace Aufgaben
open Helpers

module Number =
    let Divides64 num by =
        match num%by with
        | 0L -> true
        | _ -> false
    let Divides num by =
        match num%by with
        | 0 -> true
        | _ -> false


[<Interface>]
type INumbers =
    abstract member IsPrime : int -> bool
    abstract member IsPrime64 : int64 -> bool
    abstract member FindNextPrime : int -> int
    abstract member FindNextPrime64 : int64 -> int64

type Numbers() =
    let isPrime64 num =
        if num=2L then true
        else
            let limit = int64(sqrt(float(num)))+1L

            let sequence = seq { limit .. -1L .. 2L }
            let divisors = Seq.tryFind (fun a -> Number.Divides64 num a) sequence
            match divisors with
            | None -> true
            | Some _ -> false

    let isPrime num =
        if num=2 then true
        else
            let limit = int(sqrt(float(num)))+1
//            let limit = max (num/2) 2

            let sequence = seq { limit .. -1 .. 2 }
            let divisors = Seq.tryFind (fun a -> Number.Divides num a) sequence
            match divisors with
            | None -> true
            | Some _ -> false

    let rec findNextPrime64 current =
        if isPrime64 current then current
        else findNextPrime64 (current+1L)
//    let findNextPrime64 current =
//        memoize _findNextPrime64 current

    let rec findNextPrime current =
        if isPrime current then current
        else findNextPrime (current+1)
//    let findNextPrime current =
//        memoize _findNextPrime current

    interface INumbers with

        member this.IsPrime64 num =
            isPrime64 num
        member this.IsPrime num =
            isPrime num
        member this.FindNextPrime64 current =
            findNextPrime64 current    
        member this.FindNextPrime current =
            findNextPrime current    
