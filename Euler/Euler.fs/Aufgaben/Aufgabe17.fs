namespace Aufgaben

// If the numbers 1 to 5 are written out in words: one, two, three, four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.

// If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used?

// NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two) contains 23 letters and 115 (one hundred and fifteen) contains 20 letters. 
// The use of "and" when writing out numbers is in compliance with British usage.

[<Interface>]
type Loesung17 =
    abstract member Calculate : int -> int

type Aufgabe17() =

    //               3      3       5       4       4       3       5        5       4                                          = 36
    let einer = [| "one"; "two"; "three"; "four"; "five"; "six"; "seven"; "eight"; "nine"; |];
    //                 6         6           8           8          7          7          9             8           8           = 67
    let zehner = [| "eleven"; "twelve"; "thirteen"; "fourteen"; "fifteen"; "sixteen"; "seventeen"; "eighteen"; "nineteen" |];
    //                    6         6         6         5        5         7          6         6
    let zwanziger = [| "twenty"; "thirty"; "fourty"; "fifty"; "sixty"; "seventy"; "eighty"; "ninety" |];
    let und = "and";
    let zehn = "ten";
    let hundert = "hundred";
    let tausend = "thousand";

    let LimitToIndex limit =
        match limit with
        | 0 -> 9
        | _ -> limit

    let Calculate array limit =
        let index = LimitToIndex limit
        let range = Array.sub array 0 index
        let sum = Array.fold (fun acc (elem:string) -> acc + elem.Length) 0 range
        sum

    let EinerLength limit =
        let sum = Calculate einer (limit % 10)
        sum

    let ZehnerLength limit =
        let calcLimit = (limit % 100)
        let sum = match calcLimit with
        | x when x >= 20 -> Calculate zehner 0
        | x when x > 10 && x < 20 -> Calculate zehner (limit % 10)
        | _ -> 0
        sum

    let ZwanzigerLength limit =
        let calcLimit = (limit % 100)
        let range = calcLimit / 10
        let sum = match calcLimit with
        | x when x>=20 -> (range-2) * EinerLength(0) + Calculate zwanziger (range-1) // 0-9 und 11-20 schon drin
        | _ -> 0
        sum

    interface Loesung17 with

        member this.Calculate limit =
            let sumEiner = EinerLength limit
            let sumZehner = ZehnerLength limit
            let sumZwanziger = ZwanzigerLength limit
            sumEiner + sumZehner + sumZwanziger

    interface Aufgabe with

        member this.Title = "Aufgabe 17"

        member this.Run() =
            let result = (this :> Loesung17).Calculate 1000
            result.ToString()
