//Solution by lukasP (Lukáš Poláček)
using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Globalization;
using System.Threading;

class Tomosynthesis
{
    static double norm(double x)
    {
        while (x < 0) x += Math.PI;
        while (x >= Math.PI) x -= Math.PI;
        return x;
    }
    public static void Main()
    {
        Thread.CurrentThread.CurrentCulture = System.Globalization.CultureInfo.InvariantCulture;
        int n = int.Parse(Console.ReadLine());
        var p = new List<Complex> ();
        var r = new List<double> ();

        var events = new List<Tuple<double, int>> ();
        int cnt = 0;
        foreach (int i in Enumerable.Range(0, n))
        {
            double[] q = Console.ReadLine().Split().Select(x => double.Parse(x)).ToArray();
            p.Add(new Complex(q[0], q[1]));
            r.Add(q[2]);
            foreach (int j in Enumerable.Range(0, i))
            {
                double b = (p[j] - p[i]).Phase;
                double a = Math.Asin((r[j] + r[i]) / (p[j] - p[i]).Magnitude);
                events.Add(Tuple.Create(norm(b - a), 1));
                events.Add(Tuple.Create(norm(b + a), -1));
                cnt += Convert.ToInt32(events[events.Count - 2].Item1 > events.Last().Item1);
            }
        }

        events.Sort();
        double res = 0;
        double prev = events.Last().Item1 - Math.PI;
        foreach (var w in events)
        {
            if (cnt == 0)
                res = Math.Max(res, w.Item1 - prev);
            prev = w.Item1;
            cnt += w.Item2;
        }
        Console.WriteLine("{0:0.##########}", res);
    }
}
