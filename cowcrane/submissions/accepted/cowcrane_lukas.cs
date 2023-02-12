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
            int second = 1 - first;
            int time = Math.Abs(m[first]) + Math.Abs(m[first] - m[second]);
            time += Math.Abs(m[second] - M[second]);
            if (time > t[second]) continue;

            time += Math.Abs(m[second] - M[second]);
            time += Math.Abs(m[second] - M[first]);
            if (time <= t[first]) ok = true;
        }

        for (int first = 0; first < 2; first++)
        {
            int time = Math.Abs(m[first]) + Math.Abs(M[first] - m[first]);
            int second = 1 - first;
            if (time > t[first]) continue;

            time += Math.Abs(M[first] - m[second]) + Math.Abs(m[second] - M[second]);
            if (time <= t[second]) ok = true;
        }

        Console.WriteLine(ok ? "possible" : "impossible");
    }
}
