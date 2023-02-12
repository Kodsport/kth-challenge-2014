//Solution by lukasP (Lukáš Poláček)
using System;
using System.Linq;

class Numbertree
{
    public static void Main()
    {
        int d = int.Parse(Console.ReadLine());
        if (d % 4 == 0)
        {
            int n = d / 4 - 1;
            Console.WriteLine(n + " " + (n + 2));
        }
        else if ((d & 1) == 1)
        {
            int n = d / 2;
            Console.WriteLine(n + " " + (n + 1));
        }
        else
        {
            Console.WriteLine("impossible");
        }
    }
}
