//Solution by lukasP (Lukáš Poláček)
using System;
using System.Linq;
using System.Globalization;

class Numbertree
{
    public static void Main()
    {
        string[] ss = Console.ReadLine().Split();
        double d = double.Parse(ss[0], System.Globalization.CultureInfo.InvariantCulture);

        double len = 0, sum = 0;
        double low = 0, high = 1;
        ss = Console.ReadLine().Split();
        foreach (int x in ss.Select(y => int.Parse(y)))
        {
            sum += x;
            len += d;
            double nlow = len - sum;
            double nhigh = len - sum + 1;

            low = Math.Max(low, nlow);
            high = Math.Min(high, nhigh);
        }
        Console.WriteLine((low < high) ? "possible" : "impossible");
    }
}
