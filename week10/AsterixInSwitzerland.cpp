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
typedef property_map< Graph, edge_capacity_t >::type Cmap;
typedef property_map< Graph, edge_reverse_t >::type Rmap;

void addEdge(int from, int to, int c, Cmap &cmap, Rmap &rmap, Graph &G){
    auto e = add_edge(from, to, G).first;
    auto rev = add_edge(to, from, G).first;
    cmap[e] = c; cmap[rev] = 0;
    rmap[e] = rev; rmap[rev] = e;
}

void solve(){
    int n, m; cin >> n >> m;
    Graph G(n + 2); int source = n; int sink = source + 1;
    Cmap cmap = get(edge_capacity, G);
    Rmap rmap = get(edge_reverse, G);
    int sum = 0;
    for(int i=0; i<n; i++){
        int b; cin >> b;
        if(b > 0){ sum += b; addEdge(source, i, b, cmap, rmap, G);}
        else addEdge(i, sink, -b, cmap, rmap, G);
    }
    for(int i=0; i<m; i++){
        int x, y, d; cin >> x >> y >> d;
        addEdge(x, y, d, cmap, rmap, G);
    }
    int flow = push_relabel_max_flow(G, source, sink);
    if(flow == sum){
        cout << "no\n";
    } else cout << "yes\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}