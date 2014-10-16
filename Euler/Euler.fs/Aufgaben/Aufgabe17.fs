namespace Aufgaben

// If the numbers 1 to 5 are written out in words: one, two, three, four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.

// If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used?

// NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two) contains 23 letters and 115 (one hundred and fifteen) contains 20 letters. 
// The use of "and" when writing out numbers is in compliance with British usage.

[<Interface>]
type Loesung17 =
    abstract member Calculate : int -> int

type Aufgabe17() =

    let einer = [| "one"; "two"; "three"; "four"; "five"; "six"; "seven"; "eight"; "nine" |];
    let zehner = [| "eleven"; "twelve"; "thirteen"; "fourteen"; "fifteen"; "sixteen"; "seventeen"; "eighteen"; "nineteen" |];
    let zwanziger = [| "twenty"; "thirty"; "fourty"; "fifty"; "sixty"; "seventy"; "eighty"; "ninety" |];
    let und = "and";

    let EinerLength index =
        einer.[index].Length

    interface Loesung17 with

        member this.Calculate limit =
            42

    interface Aufgabe with

        member this.Title = "Aufgabe 17"

        member this.Run() =
            let result = (this :> Loesung17).Calculate 1000
            result.ToString()
