//Solution by lukasP (Lukáš Poláček)
using System;
using System.Collections.Generic;
using System.Linq;

class Pizza
{
    static bool satisfied(int x, List<bool> val)
    {
        return val[Math.Abs(x)] == x > 0;
    }

    public static void Main()
    {
        int n = int.Parse(Console.ReadLine());
        Random rnd = new Random();

        List<List<int>> clauses = new List<List<int>> (){new List<int> ()};
        List<List<int>> literals = Enumerable.Range(0, n).Select(x => new List<int> ()).ToList();
        Dictionary<string, int> id = new Dictionary<string, int> ();
        List<bool> val = new List<bool> (){false};
        List<int> sat = Enumerable.Repeat(0, n).ToList();
        List<int> size = new List<int> ();
        HashSet<int> unsat = new HashSet<int> ();

        foreach (int i in Enumerable.Range(0, n))
        {
            string[] ss = Console.ReadLine().Split();
            size.Add(int.Parse(ss[0]));
            foreach (string x in ss.Skip(1))
            {
                string t = x.Substring(1);
                if (!id.ContainsKey(t))
                {
                    id[t] = id.Count + 1;
                    val.Add(rnd.Next(0, 2) == 1);
                    clauses.Add(new List<int> ());
                }
                clauses[id[t]].Add((x[0] == '+' ? 1 : -1) * (i + 1));
                literals[i].Add((x[0] == '+' ? 1 : -1) * id[t]);
                if ((x[0] == '+') == val[id[t]])
                    sat[i]++;
            }

            if (sat[i] <= size[i] / 3)
                unsat.Add(i);
        }

        while (unsat.Count > 0)
        {
            double best_ratio = 1.1;
            List<int> clause_candidates = new List<int> ();
            foreach (int x in unsat)
            {
                double ratio = (double)sat[x] / size[x];
                if (ratio < best_ratio)
                {
                    clause_candidates = new List<int> () {x};
                    best_ratio = ratio;
                }
                else if (ratio == best_ratio)
                    clause_candidates.Add(x);
            }

            int clause = clause_candidates[rnd.Next(0, clause_candidates.Count)];

            int[] candidates = literals[clause].Where(x => !satisfied(x, val)).ToArray();
            int flipped = Math.Abs(candidates[rnd.Next(0, candidates.Length)]);
            val[flipped] = !val[flipped];

            foreach (int num in clauses[flipped])
            {
                bool trueNow = (num > 0) == val[flipped];
                int clauseId = Math.Abs(num) - 1;
                if (trueNow)
                {
                    if (sat[clauseId] == size[clauseId] / 3)
                        unsat.Remove(clauseId);
                    sat[clauseId]++;
                }
                else
                {
                    sat[clauseId]--;
                    if (sat[clauseId] == size[clauseId] / 3)
                        unsat.Add(clauseId);
                }
            }
        }

        foreach (string topping in id.Keys.Where(x => val[id[x]]))
            Console.WriteLine(topping);
    }
}
