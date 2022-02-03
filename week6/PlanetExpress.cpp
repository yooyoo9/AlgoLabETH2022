#include <bits/stdc++.h>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
using namespace std;
using namespace boost;
#define int long
#define vc vector
#define pb push_back
#define f first
#define s second
using pii = pair<int, int>;

typedef adjacency_list< vecS, vecS, directedS, no_property, property<edge_weight_t, int>> Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef property_map<Graph, edge_weight_t >::type Wmap;

void solve(){
    int n, m, k, t; cin >> n >> m >> k >> t;
    Graph G(2*n);
    Wmap wmap = get(edge_weight, G);
    vc<int> tel(t); 
    for(int i=0; i<t; i++) cin >> tel[i];
    for(int i=0; i<m; i++){
        int x, y, c; cin >> x >> y >> c;
        Edge e = add_edge(y, x, G).f;
        wmap[e] = c;
    }
    vc<int> comp(2*n);
    int num = strong_components(G, make_iterator_property_map(comp.begin(), get(vertex_index, G)));
    vc<int> compn(num);
    for(int i=0; i<t; i++) compn[comp[tel[i]]]++;
    for(int i=0; i<t; i++){
        Edge e = add_edge(tel[i], n+comp[tel[i]], G).f;
        Edge rev = add_edge(n+comp[tel[i]], tel[i], G).f;
        wmap[e] = compn[comp[tel[i]]] - 1;
        wmap[rev] = 0;
    }
    vc<int> d(2*n);
    dijkstra_shortest_paths(G, n-1,
        distance_map(boost::make_iterator_property_map(
                d.begin(), get(boost::vertex_index, G))));
    int ans = LONG_MAX;
    for(int i=0; i<k; i++) ans = min(ans, d[i]);
    if(ans > 1e6) cout << "no\n";
    else cout << ans << "\n"; 
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}