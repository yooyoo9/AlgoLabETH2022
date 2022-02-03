#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>
using namespace std;
using namespace boost;
#define int long
#define vc vector

typedef adjacency_list_traits< vecS, vecS, directedS > Traits;
typedef adjacency_list< listS, vecS, directedS,
    property< vertex_name_t, std::string >,
    property< edge_capacity_t, long,
        property< edge_residual_capacity_t, long,
            property< edge_reverse_t, Traits::edge_descriptor,
                property< edge_weight_t, int> > > > >
    Graph;
typedef property_map< Graph, edge_capacity_t >::type Cmap;
typedef property_map< Graph, edge_reverse_t >::type Rmap;
typedef property_map< Graph, edge_residual_capacity_t >::type Resmap;
typedef property_map< Graph, edge_weight_t >::type Wmap;
typedef graph_traits<Graph>::out_edge_iterator EdgeIt;
typedef graph_traits<Graph>::edge_descriptor Edge;

void addEdge(int from, int to, int c, int w, Cmap &cmap, Rmap &rmap, Wmap &wmap, Graph &G){
    auto e = add_edge(from, to, G).first;
    auto rev = add_edge(to, from, G).first;
    cmap[e] = c; cmap[rev] = 0;
    rmap[e] = rev; rmap[rev] = e;
    wmap[e] = w; wmap[rev] = -w;
}

void solve(){
    int n, m, s; cin >> n >> m >> s;
    Graph G(n+m+s+2); int source = n+m+s; int sink = source+1;
    Cmap cmap = get(edge_capacity, G);
    Rmap rmap = get(edge_reverse, G);
    Wmap wmap = get(edge_weight, G);
    Resmap resmap = get(edge_residual_capacity, G);
    for(int i=0; i<s; i++){
        int c; cin >> c;
        addEdge(source, i, c, 0, cmap, rmap, wmap, G);
    }
    for(int i=0; i<m; i++){
        int cur; cin >> cur; addEdge(cur-1, s+i, 1, 0, cmap, rmap, wmap, G);
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            int cur; cin>>cur;
            addEdge(s+j, s+m+i, 1, 100-cur, cmap, rmap, wmap, G);
        }
        addEdge(s+m+i, sink, 1, 0, cmap, rmap, wmap, G);
    }
    successive_shortest_path_nonnegative_weights(G, source, sink);
    int flow = 0;
    EdgeIt it, itend;
    for(tie(it, itend) = out_edges(source, G); it != itend; it++){
        flow += cmap[*it] - resmap[*it];
    }
    int profit = 100 * flow - find_flow_cost(G);
    cout << flow << " " << profit << "\n";
}


signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}
