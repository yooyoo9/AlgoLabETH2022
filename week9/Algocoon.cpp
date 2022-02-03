#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
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
typedef property_map< Graph, edge_capacity_t >::type Cmap;
typedef property_map< Graph, edge_reverse_t >::type Rmap;
typedef property_map< Graph, edge_residual_capacity_t >::type Resmap;
typedef graph_traits< Graph >::out_edge_iterator OutEdgeIt;

void addEdge(int from, int to, int c, Cmap &cmap, Rmap &rmap, Graph &G){
    auto e = add_edge(from, to, G).first;
    auto rev = add_edge(to, from, G).first;
    cmap[e] = c; cmap[rev] = 0;
    rmap[e] = rev; rmap[rev] = e;
}

void solve(){
    int n, m; cin >> n >> m;
    Graph G(n);
    Cmap cmap = get(edge_capacity, G);
    Rmap rmap = get(edge_reverse, G);
    for(int i=0; i<m; i++){
        int a, b, c; cin >> a >> b >> c;
        addEdge(a, b, c, cmap, rmap, G);
    }
    
    int cost = LONG_MAX;
    OutEdgeIt it, itend;
    for(int i=0; i<n; i++){
        cost = min(cost, push_relabel_max_flow(G, i, (i+1)%n));
    }
    cout << cost << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}