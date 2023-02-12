import java.util.Random;
import java.util.LinkedList;
import java.util.TreeMap;
import java.util.ArrayList;
import java.util.StringTokenizer;
import java.io.BufferedReader;
import java.io.BufferedOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.io.OutputStream;


public class pizza_pa {
	public static void main(String args[]) {
		new pizza_pa().solve();
	}

	Random rnd;
	Kattio io;

	public pizza_pa() {
		rnd = new Random();
		io = new Kattio(System.in, System.out);
	}

	int val[], satlits[];
	ArrayList<Integer> clauses[], occ[][];	
	LinkedList<Integer> unsat;

	int abs(int v) { return v < 0 ? -v : v; }

	int unsatvar(int C) {
		while (true) {
			int v = clauses[C].get(rnd.nextInt(clauses[C].size()));
			if (v*val[abs(v)] < 0) {
				return abs(v);
			}
		}
	}

	void flip(int v) {
		val[v] = -val[v];
		for (int C: occ[(1+val[v])/2][v]) {
			++satlits[C];
		}
		for (int C: occ[(1-val[v])/2][v]) {
			--satlits[C];
			if (3*satlits[C] <= clauses[C].size() &&
				3*(satlits[C]+1) > clauses[C].size())
				unsat.add(C);
		}
	}

	ArrayList<String> topname;
	TreeMap<String,Integer> topidx;

	int get_topping() {
		String str = io.getWord();
		int sgn = str.charAt(0) == '+' ? 1 : -1;
		String top = str.substring(1);
		if (!topidx.containsKey(top)) {
			topidx.put(top, topidx.size()+1);
			topname.add(top);
		}
		return sgn*topidx.get(top);
	}


	void solve() {
		topname = new ArrayList<String>();
		topidx = new TreeMap<String, Integer>();
		int N = io.getInt();
		
		satlits = new int[N];
		clauses = new ArrayList[N];

		val = new int[300];
		unsat = new LinkedList<Integer>();

		occ = new ArrayList[2][300];
		for (int i = 0; i < 2; ++i)
			for (int j = 0; j< 300; ++j)
				occ[i][j] = new ArrayList<Integer>();

		for (int i = 0; i < N; ++i) {
			int w = io.getInt();
			satlits[i] = 0;
			clauses[i] = new ArrayList<Integer>();
			for (int j = 0; j < w; ++j) {
				int wish = get_topping();
				clauses[i].add(wish);
				if (wish > 0) {
					occ[1][wish].add(i);
				} else {
					++satlits[i];
					occ[0][-wish].add(i);
				}
			}
			if (3*satlits[i] <= clauses[i].size()) unsat.add(i);
		}
		
		for (int i = 1; i <= topname.size(); ++i) val[i] = -1;
		
		while (!unsat.isEmpty()) {
			int C = unsat.poll();
			while (3*satlits[C] <= clauses[C].size())
				flip(unsatvar(C));
		}
		
		for (int i = 1; i <= topname.size(); ++i)
			if (val[i] > 0)
				io.printf("%s\n", topname.get(i-1));
		io.flush();
	}
}



/** Simple yet moderately fast I/O routines.
 *
 * Example usage:
 *
 * Kattio io = new Kattio(System.in, System.out);
 *
 * while (io.hasMoreTokens()) {
 *    int n = io.getInt();
 *    double d = io.getDouble();
 *    double ans = d*n;
 *
 *    io.println("Answer: " + ans);
 * }
 *
 * io.close();
 *
 *
 * Some notes:
 *
 * - When done, you should always do io.close() or io.flush() on the
 *   Kattio-instance, otherwise, you may lose output.
 *
 * - The getInt(), getDouble(), and getLong() methods will throw an
 *   exception if there is no more data in the input, so it is generally
 *   a good idea to use hasMoreTokens() to check for end-of-file.
 *
 * @author: Kattis
 */


class Kattio extends PrintWriter {
    public Kattio(InputStream i) {
	super(new BufferedOutputStream(System.out));
	r = new BufferedReader(new InputStreamReader(i));
    }
    public Kattio(InputStream i, OutputStream o) {
	super(new BufferedOutputStream(o));
	r = new BufferedReader(new InputStreamReader(i));
    }

    public boolean hasMoreTokens() {
	return peekToken() != null;
    }

    public int getInt() {
	return Integer.parseInt(nextToken());
    }

    public double getDouble() { 
	return Double.parseDouble(nextToken());
    }

    public long getLong() {
	return Long.parseLong(nextToken());
    }

    public String getWord() {
	return nextToken();
    }



    private BufferedReader r;
    private String line;
    private StringTokenizer st;
    private String token;

    private String peekToken() {
	if (token == null) 
	    try {
		while (st == null || !st.hasMoreTokens()) {
		    line = r.readLine();
		    if (line == null) return null;
		    st = new StringTokenizer(line);
		}
		token = st.nextToken();
	    } catch (IOException e) { }
	return token;
    }

    private String nextToken() {
	String ans = peekToken();
	token = null;
	return ans;
    }
}

