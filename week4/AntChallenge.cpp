#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
using namespace std;
using namespace boost;
#define int long
#define vc vector
#define pb push_back
using pii = pair<int, int>;

typedef adjacency_list_traits<vecS, vecS, undirectedS> Traits;
typedef adjacency_list<vecS, vecS, undirectedS, 
    property< vertex_distance_t, int >, property< edge_weight_t, int > >
        Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef property_map< Graph, edge_weight_t >::type Wmap;
typedef property_map< Graph, vertex_distance_t >::type Dmap;

void solve(){
    int n, e, s, a, b; cin >> n >> e >> s >> a >> b;
    map<Edge, vc<int>> edges;
    map<Edge, int> nedges;
    Graph G(n);
    Wmap wmap = get(edge_weight, G);
    Dmap dmap = get(vertex_distance, G);
    for(int i=0; i<e; i++){
        int x, y; cin >> x >> y;
        Edge cure = add_edge(x, y, G).first;
        vc<int> cur(s);
        for(int j=0; j<s; j++) cin >> cur[j];
        edges[cure] = cur;
        nedges[cure] = 1e6;
    }
    
    for(int i=0; i<s; i++){
        int curh; cin >> curh;
        for(auto cur : edges) wmap[cur.first] = (cur.second)[i];
        std::vector< Edge > spanning_tree;
        kruskal_minimum_spanning_tree(G, std::back_inserter(spanning_tree));
        for(Edge cure : spanning_tree){
            nedges[cure] = min(nedges[cure], edges[cure][i]);
        }
    }
    for(auto cur : nedges){
        if(cur.second == 1e6) remove_edge(cur.first, G);
        wmap[cur.first] = cur.second;
    }
    
    vc< int > d(n); vc< Vertex > pp(n);
    dijkstra_shortest_paths(G, a,
        predecessor_map(make_iterator_property_map(
                            pp.begin(), get(vertex_index, G)))
            .distance_map(boost::make_iterator_property_map(
                d.begin(), get(boost::vertex_index, G))));
    cout << d[b] << endl;
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}