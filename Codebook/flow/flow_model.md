- Maximum flow with lower/upper bound from $s$ to $t$
	1. For each edge $(x, y, l, u)$, connect $x\to y$ with compacity $u - l$. 
	2. For each node $u$, denote $d[u]$ as the differience between the sum of incoming lower bounds and the sum of outgoing lower bounds. If $d[u] > 0$, connect $S\to u$ with compacity $d[u]$, otherwise connect $u\to T$ with compacity $-d[u]$.
	3. connect $t\to s$ with compacity $\infty$.
	4. Let $k$ be the sum of all $in[u] > 0$. If $Maxflow(S, T) \neq k$, there's no solution.
	5. Otherwise, $Maxflow(s, t)$ is the maxflow from $s$ to $t$.
	6. Furthermore, let $ff$ be the flow on $t\to s$. remove this edge and run $f = Maxflow(t, s)$. $ff - f$ is theminimum flow from $s$ to $t$.
