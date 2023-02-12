//Solution by lukasP (Lukáš Poláček)
using System;
using System.Linq;

class CowCrane
{
    public static void Main()
    {
        int[] m = Console.ReadLine().Split().Select(x => int.Parse(x)).ToArray();
        int[] M = Console.ReadLine().Split().Select(x => int.Parse(x)).ToArray();
        int[] t = Console.ReadLine().Split().Select(x => int.Parse(x)).ToArray();

        bool ok = false;
        for (int first = 0; first < 2; first++)
        {
            int time = Math.Abs(m[first]) + Math.Abs(M[first] - m[first]);
            if (time > t[first]) continue;

            time += Math.Abs(M[first] - m[1 - first]) + Math.Abs(m[1 - first] - M[1-first]);
            if (time <= t[1 - first]) ok = true;
        }

        Console.WriteLine(ok ? "possible" : "impossible");
    }
}
