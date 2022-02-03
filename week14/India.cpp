#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>
using namespace std;
using namespace boost;
#define int long
#define vc vector
#define f first

typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
    property<edge_capacity_t, int,
        property<edge_residual_capacity_t, int,
            property<edge_reverse_t, Traits::edge_descriptor,
                property<edge_weight_t, int>>>>> Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::out_edge_iterator OutEdgeIt;
typedef property_map<Graph, edge_capacity_t>::type Cmap;
typedef property_map<Graph, edge_reverse_t>::type Rmap;
typedef property_map<Graph, edge_residual_capacity_t>::type Resmap;
typedef property_map<Graph, edge_weight_t>::type Wmap;

void addEdge(int from, int to, int c, int w, Cmap &cmap, Rmap &rmap, Wmap &wmap, Graph &G){
    Edge e = add_edge(from, to, G).f;
    Edge rev = add_edge(to, from, G).f;
    cmap[e] = c; cmap[rev] = 0;
    rmap[e] = rev; rmap[rev] = e;
    wmap[e] = w; wmap[rev] = -w;
}

void solve(){
    int c, g, b, k, a; cin >> c >> g >> b >> k >> a;
    int l=0;
    vc<vc<int>> edges(g, vc<int>(4));
    for(int i=0; i<g; i++){
        for(int j=0; j<4; j++) cin >> edges[i][j];
    }
    Graph G(c + 2);
    Cmap cmap = get(edge_capacity, G);
    Rmap rmap = get(edge_reverse, G);
    Wmap wmap = get(edge_weight, G);
    int source = c; int sink = source+1;
    for(vc<int> e : edges){
        addEdge(e[0], e[1], e[3], e[2], cmap, rmap, wmap, G);
    }
    addEdge(source, k, LONG_MAX, 0, cmap, rmap, wmap, G);
    addEdge(a, sink, LONG_MAX, 0, cmap, rmap, wmap, G);
    int r = push_relabel_max_flow(G, source, sink) + 1;
    while(l + 1 != r){
        int mid = l + (r-l)/2;
        Graph G(c + 2);
        Cmap cmap = get(edge_capacity, G);
        Rmap rmap = get(edge_reverse, G);
        Wmap wmap = get(edge_weight, G);
        int source = c; int sink = source+1;
        for(vc<int> e : edges){
            addEdge(e[0], e[1], e[3], e[2], cmap, rmap, wmap, G);
        }
        addEdge(source, k, mid, 0, cmap, rmap, wmap, G);
        addEdge(a, sink, mid, 0, cmap, rmap, wmap, G);
        successive_shortest_path_nonnegative_weights(G, source, sink);
        int cur = find_flow_cost(G);
        if(cur > b) r = mid;
        else l = mid;
    }
    cout << l << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}