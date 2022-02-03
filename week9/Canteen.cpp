#include <bits/stdc++.h>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>
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
                property< edge_reverse_t, Traits::edge_descriptor, 
                    property< edge_weight_t, int > > > > >
        Graph;
typedef property_map< Graph, edge_capacity_t >::type Cmap;
typedef property_map< Graph, edge_reverse_t >::type Rmap;
typedef property_map< Graph, edge_residual_capacity_t >::type Resmap;
typedef property_map< Graph, edge_weight_t >::type Wmap;
typedef graph_traits< Graph >::out_edge_iterator OutEdgeIt;

void addEdge(int from, int to, int c, int w, Cmap &cmap, Rmap &rmap, Wmap &wmap, Graph &G){
    auto e = add_edge(from, to, G).first;
    auto rev = add_edge(to, from, G).first;
    cmap[e] = c; cmap[rev] = 0;
    rmap[e] = rev; rmap[rev] = e;
    wmap[e] = w; wmap[rev] = -w;
}

void solve(){
    int n; cin >> n;
    Graph G(n+2); int source=n; int sink = n+1;
    Cmap cmap = get(edge_capacity, G);
    Rmap rmap = get(edge_reverse, G);
    Resmap resmap = get(edge_residual_capacity, G);
    Wmap wmap = get(edge_weight, G);
    for(int i=0; i<n; i++){
        int a, c; cin >> a >> c;
        addEdge(source, i, a, c, cmap, rmap, wmap, G);
    }
    int sum = 0;
    for(int i=0; i<n; i++){
        int s, p; cin >> s >> p; sum += s;
        addEdge(i, sink, s, 20-p, cmap, rmap, wmap, G);
    }
    for(int i=0; i<n-1; i++){
        int v, e; cin >> v >> e;
        addEdge(i, i+1, v, e, cmap, rmap, wmap, G);
    }
    successive_shortest_path_nonnegative_weights(G, source, sink);
    int flow=0;
    OutEdgeIt it, itend;
    for(tie(it, itend) = out_edges(source, G); it != itend; it++){
        flow += cmap[*it] - resmap[*it];
    }
    int cost = find_flow_cost(G) - 20 * flow;
    if(flow == sum) cout << "possible ";
    else cout << "impossible ";
    cout << flow << " " << -cost << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}