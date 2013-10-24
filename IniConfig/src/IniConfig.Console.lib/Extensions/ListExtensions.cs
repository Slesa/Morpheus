using System.Collections.Generic;
using System.Linq;

namespace IniConfig.Console.lib.Extensions
{
    public static class ListExtensions
    {
         public static T Head<T>(this List<T> list)
         {
             return list.FirstOrDefault();
         }

         public static IEnumerable<T> Tail<T>(this List<T> list)
         {
             if(!list.Any()) yield break;
             for (var i = 1; i < list.Count; i++)
                 yield return list[i];
         }
    }
}