//Solution by lukasP (Lukáš Poláček)
using System;
using System.Linq;

class Numbertree
{
    public static void Main()
    {
        string[] ss = Console.ReadLine().Split();
        int h = int.Parse(ss[0]);
        int num = ss[1].Aggregate(1, (x, y) => 2 * x + Convert.ToInt32(y == 'R'));
        Console.WriteLine((1 << (h + 1)) - num);
    }
}
