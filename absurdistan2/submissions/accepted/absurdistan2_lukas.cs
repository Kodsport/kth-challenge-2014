//Solution by lukasP (Lukáš Poláček)
using System;
using System.Linq;
using System.Globalization;
using System.Threading;

class Absurdistan2
{
    public static void Main()
    {
        Thread.CurrentThread.CurrentCulture = System.Globalization.CultureInfo.InvariantCulture;
        int n = int.Parse(Console.ReadLine());
        double[] p = new double[n + 1];

        double[,] c = new double[n + 5, n + 5];
        foreach (int i in Enumerable.Range(0, n + 1))
        {
            c[i, 0] = 1;
            c[i, i + 1] = 0;
            foreach (int j in Enumerable.Range(1, i))
                c[i, j] = c[i - 1, j] + c[i - 1, j - 1];

            p[i] = Math.Pow(i - 1, i);
            for (int j = 2; j < i - 1; j++)
                p[i] -= Math.Pow(i - j - 1, i - j) * c[i - 1, j - 1] * p[j];
        }

        Console.WriteLine("{0:0.###########}", p[n] / Math.Pow(n - 1, n));
    }
}
