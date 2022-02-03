#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
using namespace std;
using namespace boost;
#define int long
#define vc vector
#define f first
#define s second

typedef adjacency_list_traits<vecS, vecS, undirectedS> Traits;
typedef adjacency_list<vecS, vecS, undirectedS, 
    property<vertex_distance_t, int>, property<edge_weight_t, int>> Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef property_map<Graph, edge_weight_t>::type Wmap;

void solve(){
    int n, m; cin >> n >> m;
    Graph G(n);
    Wmap wmap = get(edge_weight, G);
    for(int i=0; i<m; i++){
        int a, b, w; cin >> a >> b >> w;
        Edge e = add_edge(a, b, G).f;
        wmap[e] = w;
    }
    vc<Edge> spanning_tree;
    kruskal_minimum_spanning_tree(G, back_inserter(spanning_tree));
    int ans = 0;
    for(Edge e : spanning_tree) ans += wmap[e];

    vc<Vertex> p(n);
    vc<int> d(n);
    dijkstra_shortest_paths(G, 0, predecessor_map(make_iterator_property_map(p.begin(), get(vertex_index, G)))
        .distance_map(make_iterator_property_map(d.begin(), get(vertex_index, G))));
    int ans1 = 0;
    for(int x : d) ans1 = max(ans1, x);
    cout << ans << " " << ans1 << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}
