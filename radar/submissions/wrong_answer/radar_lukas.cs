//Solution by lukasP (Lukáš Poláček)
using System;
using System.Collections.Generic;
using System.Linq;

class Radar
{
    static Tuple<long, long> gcd(long a, long b)
    {
        if (a == 0) return Tuple.Create(0L, 1L);
        Tuple<long, long> f = gcd(b % a, a);
        return Tuple.Create(f.Item2 - b / a * f.Item1, f.Item1);
    }

    static long inver(long a, long m)
    {
        return (m + gcd(a, m).Item1) % m;
    }

    static long M;
    static List<long> iM, dM;
    static long cinska_zvyskova(List<long> m, List<long> x)
    {
        return Enumerable.Range(0, 3).Sum(i => dM[i] * (iM[i] * x[i] % m[i])) % M;
    }

    static int norm(int x, int m)
    {
        return (x % m + m) % m;
    }

    static List<long> line()
    {
        return Console.ReadLine().Split().Select(t => long.Parse(t)).ToList();
    }

    public static void Main()
    {
        List<long> m = line();
        M = m.Aggregate(1L, (u, v) => (u * v));
        dM = m.Select(u => M / u).ToList();
        iM = Enumerable.Range(0, 3).Select(i => inver(dM[i], m[i])).ToList();
        List<long> x = line(), y = line();

        long res = 1L<<62;
        foreach (int l in Enumerable.Range(0, 3))
        {
            int[, ] r = new int[3, 2];
            foreach (int i in Enumerable.Range(0, 3))
            {
                r[i, 0] = norm((int)(x[i] - y[i]), (int)m[i]);
                if (i != l) r[i, 1] = (int)(x[i] + y[i]);
                else r[i, 1] = r[i, 0];
            }

            for (int i = r[0, 0]; i <= r[0, 1]; i++)
                for (int j = r[1, 0]; j <= r[1, 1]; j++)
                    for (int k = r[2, 0]; k <= r[2, 1]; k++)
                    {
                        List<long> rem = new List<long> {i, j, k};
                        res = Math.Min(res, cinska_zvyskova(m, rem));
                    }
        }
        Console.WriteLine(res);
    }
}
