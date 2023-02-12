/* This is an example solution to the "Intercept" problem from KTH Challenge 2013, held on April 13,
 * 2014.
 *
 * The solution is provided as-is, is not documented, and may be generally difficult to read.
 *
 * This work by KTH CSC (http://www.csc.kth.se/) is licensed under a Creative Commons
 * Attribution-Share Alike 2.5 Sweden License
 * (http://creativecommons.org/licenses/by-sa/2.5/se/deed.en).  You are free to redistribute it as
 * you like as long as this license information is not removed.
 */
//Solution by Erik Aas
package main

import (
	"container/heap"
	"fmt"
	"bufio"
	"os"
	"strings"
	"strconv"
)

type edge struct {
	u, v int
	w int64
}

var E [][]edge
var inf64 int64
var inf int

type item struct {
	name int	
	dist int64
	index int
}

type pqueue []*item

func (q pqueue) Len() int { return len(q) }

func (q pqueue) Less(i, j int) bool {
	return q[i].dist < q[j].dist
}

func (q pqueue) Swap(i, j int) {
	q[i], q[j] = q[j], q[i]
	q[i].index, q[j].index = i, j
}

func (q *pqueue) Push(x interface{}) {
	n := len(*q)
	i := x.(*item)
	i.index = n
	*q = append(*q, i)
}

func (q *pqueue) Pop() interface{} {
	old := *q
	n := len(old)
	i := old[n-1]
	i.index = -1
	*q = old[0 : n-1]
	return i
}

func (q *pqueue) update(i *item, dist int64) {
	heap.Remove(q, i.index)
	i.dist = dist
	heap.Push(q, i)
}

func dijkstra(N,M,S,T int, arr []int64) {
	nodes := make([]*item,N)
	q := &pqueue{}
	heap.Init(q)
	for i := 0; i < N; i++ {
		var D int64
		if(i == S) { D = 0 } else { D = inf64 }
		nodes[i] = &item {name: i,dist: D ,}
		heap.Push(q, nodes[i])
	}
	heap.Push(q,&item{name:inf,dist:inf64,})
	for true {
		current := heap.Pop(q).(*item)
		if(current.dist == inf64) { break }
		arr[current.name]=current.dist
		for i := 0; i < len(E[current.name]); i++ {
			e := E[current.name][i]
			if(e.v == current.name) {
				if(nodes[current.name].dist + e.w < nodes[e.u].dist) {
					q.update(nodes[e.u], nodes[current.name].dist + e.w)
				}
			}
		}
	}
}

func main() {
	inf   = 2000000000
	inf64 = 1000000000000000000
	var N, M int
	fmt.Scanf("%d%d", &N, &M)
	E = make([][]edge,N)

	rdr := bufio.NewReader(os.Stdin)
	for i := 0; i < M; i++ {
		var A,B int
		var D int
		str, _ := rdr.ReadString('\n')
		arr := strings.Split(str, " ")
		A, _ = strconv.Atoi(arr[0])
		B, _ = strconv.Atoi(arr[1])
		D, _ = strconv.Atoi(strings.TrimSpace(arr[2]))
		E[A] = append(E[A], edge{A,B,int64(D)})
		E[B] = append(E[B], edge{A,B,int64(D)})
	}
	var S, T int
	str, _ := rdr.ReadString('\n')
	arr := strings.Split(str, " ")
	S, _ = strconv.Atoi(arr[0])
	T, _ = strconv.Atoi(strings.TrimSpace(arr[1]))
	if(S == T) {
		fmt.Println(S)
		return
	}
	from_t := make([]int64,N)

	// For each node, calculate the distance from t.
	dijkstra(N,M,T,S,from_t[0:])

	// For each possible (and interesting) distance from s, is there a unique node at this distance and do all arc used in shortest paths go through this node? 
	res := make([]int,0)
	net := &pqueue{}
	heap.Init(net)
	heap.Push(net,&item{name:S,dist:-from_t[S],})
	heap.Push(net,&item{name:inf,dist:inf64,})
	scan := make([]bool, N)
	for i := 0; i < N; i++ { scan[i] = false;	}
	n_net := 1
	scan[S] = true
	for true {
		head := heap.Pop(net).(*item)
		n_net--;
		if head.name == T {
			goto fin
		}
		level := make([]int, 1)
		level[0] = head.name
		for true {
			tmp := heap.Pop(net).(*item)
			if tmp.name == T {
				goto fin
			}
			n_net--
			if(tmp.dist == head.dist) {
				level = append(level, tmp.name)
			} else {
				heap.Push(net, tmp)
				n_net++
				break
			}
		}
		if(n_net == 0 && len(level) == 1) {
			res = append(res, level[0])
		}
		for i := 0; i < len(level); i++ {
			u := level[i]
			for j := 0; j < len(E[u]); j++ {
				e := E[u][j]
				v := E[u][j].v
				if(e.u == u && (from_t[u] - e.w == from_t[v]) && !scan[v]) {
					heap.Push(net,&item{name:v,dist:-from_t[v],})
					n_net++
					scan[v] = true
				}
			}
		}	
	}
	fin:
	for i:=0;i<len(res);i++ {
		fmt.Print(res[i]," ")
	}
	fmt.Println(T)
}

