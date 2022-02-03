#include <bits/stdc++.h>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/adjacency_list.hpp>
using namespace std;
using namespace boost;
#define int long
#define vc vector
using pii = pair<int, int>;

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
    int l, p; cin >> l >> p;
    Graph G(l+2); int source=l, sink=l+1;
    Cmap cmap = get(edge_capacity, G);
    Rmap rmap = get(edge_reverse, G);
    vc<int> dif(l);
    for(int i=0; i<l; i++){
        int g, d; cin >> g >> d; dif[i] = g - d;
    }
    for(int i=0; i<p; i++){
        int f, t, c0, c1; cin >> f >> t >> c0 >> c1;
        addEdge(f, t, c1 - c0, cmap, rmap, G);
        dif[t] += c0; dif[f] -= c0;
    }
    int best = 0;
    for(int i=0; i<l; i++){
        if(dif[i] > 0) addEdge(source, i, dif[i], cmap, rmap, G);
        else {addEdge(i, sink, -dif[i], cmap, rmap, G); best += -dif[i];}
    }
    int flow = push_relabel_max_flow(G, source, sink);
    if(flow == best) cout << "yes\n";
    else cout << "no\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}
