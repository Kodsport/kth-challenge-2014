//Solution by lukasP (Lukáš Poláček)
using System;
using System.Linq;

class Numbertree
{
    public static void Main()
    {
        int d = int.Parse(Console.ReadLine());
        for (int i = 0; i < 200000; i++)
        {
            int si = i * i;
            for (int j = i + 1; j < 200000; j++)
            {
                int sj = j * j;
                if (sj - si > d) break;
                if (sj - si == d)
                {
                    Console.WriteLine(i + " " + j);
                    return;
                }
            }
        }
        Console.WriteLine("impossible");
    }
}
