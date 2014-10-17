namespace Aufgaben

// If the numbers 1 to 5 are written out in words: one, two, three, four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.

// If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used?

// NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two) contains 23 letters and 115 (one hundred and fifteen) contains 20 letters. 
// The use of "and" when writing out numbers is in compliance with British usage.

[<Interface>]
type Loesung17 =
    abstract member Calculate : int -> int

type Aufgabe17() =

    //                   3      3       5       4       4       3       5        5       4                                        = 36
    let einer = [| ""; "one"; "two"; "three"; "four"; "five"; "six"; "seven"; "eight"; "nine"; |];
    //                3       6         6           8           8          7          7          9             8           8      = 70
    let zehner = [| "ten"; "eleven"; "twelve"; "thirteen"; "fourteen"; "fifteen"; "sixteen"; "seventeen"; "eighteen"; "nineteen" |];
    //                    6         6         6         5        5         7          6         6                                 = 47
    let zwanziger = [| "twenty"; "thirty"; "fourty"; "fifty"; "sixty"; "seventy"; "eighty"; "ninety" |];
    let und = "and";
    let hundert = "hundred";
    let tausend = "thousand";

    let LimitToIndex limit =
        match limit with
        | 0 -> 9
        | _ -> limit

    let Calculate array limit =
//        let index = LimitToIndex limit
        let range = Array.sub array 0 (limit+1)
        let sum = Array.fold (fun acc (elem:string) -> acc + elem.Length) 0 range
        sum

    // = 1..9
    let EinerLength limit =
        let sum = match limit with
        | x when x < 10 || x > 20 -> Calculate einer (limit % 10)
        | _ -> 0
        sum

    // = 10..19
    let ZehnerLength limit =
        let calcLimit = (limit % 100)
        let sumEiner = match calcLimit with
        | x when x >= 10 -> EinerLength 9
        | _ -> 0
        let sum = match calcLimit with
        | x when x >= 20 -> Calculate zehner 9
        | x when x >= 10 && x < 20 -> Calculate zehner (limit - 10)
        | _ -> 0
        sumEiner + sum

    let ZwanzigerLength limit =
        let calcLimit = (limit % 100)
        let sumZehner = match calcLimit with
        | x when x >= 20 -> ((calcLimit/10)-2) * EinerLength 9 
        | _ -> 0
        let range = calcLimit / 10
        let sum = match calcLimit with
        | x when x >= 20 -> Calculate zwanziger (range-2) // 0-9 und 11-20 schon drin
        | _ -> 0
        sumZehner + sum

    let HunderterLength limit =
        let calcLimit = limit / 100
        let max = calcLimit % 10
        let rest = calcLimit / 10
        if max=0 then 0
        else
            let unterSum = max * ((ZwanzigerLength 99) + (ZehnerLength 99) + (EinerLength 99))
            let hundertSum = max * (EinerLength max + hundert.Length) +          // xxx hundred      100,200
                99 * (max-1) * (EinerLength max + hundert.Length + und.Length) + // xxx hundred and  101-199
                rest * (EinerLength max + hundert.Length + und.Length)          // xxx hundred and  201
                
            unterSum + hundertSum

    let TausenderLength limit =
        let calcLimit = limit / 1000
        if calcLimit=0 then 0
        else
            let unterSum = 9 * (HunderterLength 999) // + (ZwanzigerLength 999) + (ZehnerLength 999) + (EinerLength 999)
            tausend.Length + unterSum

    interface Loesung17 with

        member this.Calculate limit =
            let sumEiner = EinerLength limit
            let sumZehner = ZehnerLength limit
            let sumZwanziger = ZwanzigerLength limit
            let sumHundert = HunderterLength limit
            let sumTausend = TausenderLength limit
            sumEiner + sumZehner + sumZwanziger + sumHundert + sumTausend

    interface Aufgabe with

        member this.Title = "Aufgabe 17"

        member this.Run() =
            let result = (this :> Loesung17).Calculate 1000
            result.ToString()
