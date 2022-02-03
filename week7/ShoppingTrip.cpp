#include <bits/stdc++.h>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/adjacency_list.hpp>
using namespace std;
using namespace boost;
#define int long
#define vc vector

typedef adjacency_list_traits< vecS, vecS, directedS > Traits;
typedef adjacency_list< listS, vecS, directedS,
        property< vertex_name_t, std::string >,
        property< edge_capacity_t, long,
            property< edge_residual_capacity_t, long,
                property< edge_reverse_t, Traits::edge_descriptor > > > >
        Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef property_map< Graph, edge_capacity_t >::type Cmap;
typedef property_map< Graph, edge_reverse_t >::type Rmap;
typedef property_map< Graph, edge_residual_capacity_t >::type Resmap;

void addEdge(int from, int to, int c, Cmap &cmap, Rmap &rmap, Graph &G){
    Edge e = add_edge(from, to, G).first;
    Edge rev = add_edge(to, from, G).first;
    cmap[e] = c; cmap[rev] = 0;
    rmap[e] = rev; rmap[rev] = e;
}

void solve(){
    int n, m, s; cin >> n >> m >> s;
    Graph G(n + 2);
    Cmap cmap = get(edge_capacity, G);
    Rmap rmap = get(edge_reverse, G);
    int source = n; int sink = source+1;
    vc<int> store(n);
    for(int i=0; i<s; i++){
        int cur; cin >> cur; store[cur]++;
    }
    for(int i=0; i<n; i++){
        if(!store[i]) continue;
        addEdge(i, sink, store[i], cmap, rmap, G);
    }
    for(int i=0; i<m; i++){
        int x, y; cin >> x >> y;
        addEdge(x, y, 1, cmap, rmap, G);
        addEdge(y, x, 1, cmap, rmap, G);
    }
    addEdge(source, 0, s, cmap, rmap, G);
    int flow = push_relabel_max_flow(G, source, sink);
    if(flow == s) cout << "yes\n";
    else cout << "no\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}