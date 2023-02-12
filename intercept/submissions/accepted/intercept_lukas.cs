//Solution by lukasP (Lukáš Poláček)
using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;

class Numbertree
{
    static int mod = 459460189;
    static List<int> Dijkstra(int s, List<List<Tuple<int, int>>> g, List<long> dist)
    {
        int n = g.Count;
        List<int> cnt = Enumerable.Repeat(0, n).ToList();

        var q = new SortedSet<Tuple<long, int>> ();
        dist[s] = 0;
        cnt[s] = 1;
        for (q.Add(Tuple.Create(0L, s)); q.Count > 0; q.Remove(q.Min))
        {
            var best = q.Min;
            foreach (var x in g[best.Item2])
                if (dist[x.Item1] > dist[best.Item2] + x.Item2)
                {
                    q.Remove(Tuple.Create(dist[x.Item1], x.Item1));
                    cnt[x.Item1] = cnt[best.Item2];
                    dist[x.Item1] = dist[best.Item2] + x.Item2;
                    q.Add(Tuple.Create(dist[x.Item1], x.Item1));
                }
                else if (dist[x.Item1] == dist[best.Item2] + x.Item2)
                    cnt[x.Item1] = (cnt[x.Item1] + cnt[best.Item2]) % mod;
        }

        return cnt;
    }

    public static void Main()
    {
        var bs = new BufferedStream(Console.OpenStandardInput());
        StreamReader reader = new StreamReader(bs);

        string[] ss = reader.ReadLine().Split(' ');
        int n = int.Parse(ss[0]), m = int.Parse(ss[1]);

        var g = Enumerable.Range(0, n).Select(x => new List<Tuple<int, int>> ()).ToList();
        var rg = Enumerable.Range(0, n).Select(x => new List<Tuple<int, int>> ()).ToList();
        foreach (int j in Enumerable.Range(0, m))
        {
            int[] ii = reader.ReadLine().Split(' ').Select(x => int.Parse(x)).ToArray();
            int u = ii[0], v = ii[1], w = ii[2];
            g[u].Add(Tuple.Create(v, w));
            rg[v].Add(Tuple.Create(u, w));
        }

        int[] jj = reader.ReadLine().Split(' ').Select(x => int.Parse(x)).ToArray();
        int s = jj[0], t = jj[1];

        List<long> dist = Enumerable.Repeat(1L << 60, n).ToList();
        var cnt = Dijkstra(s, g, dist);
        List<long> dist2 = Enumerable.Repeat(1L << 60, n).ToList();
        var cnt2 = Dijkstra(t, rg, dist2);

        var qq = Enumerable.Range(0, n)
            .Where(x => dist[x] + dist2[x] == dist[t] && (long)cnt[x] * cnt2[x] % mod == cnt[t]);
        Console.WriteLine(string.Join(" ", qq));
    }
}
