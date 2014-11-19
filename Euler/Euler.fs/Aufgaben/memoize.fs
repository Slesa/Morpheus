namespace Aufgaben

module Helpers =

    open System.Collections.Generic 

    let memoize f =
        let cache = Dictionary<_,_>()
        fun x ->
            if cache.ContainsKey(x) then 
                Debug.writefn "Hit"
                cache.[x]
            else
                let f_x = f x
                cache.[x] <- f_x
                f_x
        

