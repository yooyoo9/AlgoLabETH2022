#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
using namespace std;
using namespace boost;
#define int long
#define vc vector

typedef adjacency_list< listS, vecS, directedS, no_property,
        property< edge_weight_t, int > >
        graph_t;
typedef graph_traits< graph_t >::vertex_descriptor vertex_descriptor;
typedef std::pair< int, int > Edge;
typedef adjacency_list< vecS, vecS, undirectedS > Graph;

void solve(){
    int n, m, a, s, c, d; cin >> n >> m >> a >> s >> c >> d;
    graph_t g(n);
    property_map< graph_t, edge_weight_t >::type weightmap
        = get(edge_weight, g);
    for(int i=0; i<m; i++){
        int x, y, z; char w; cin >> w >> x >> y >> z;
        auto e = add_edge(x, y, g).first;
        weightmap[e] = z;
        if(w == 'L'){
            auto rev = add_edge(y, x, g).first;
            weightmap[rev] = z;
        }
    }
   
    vc<int> posa(a); for(int i=0; i<a; i++) cin >> posa[i];
    vc<int> poss(s); for(int i=0; i<s; i++) cin >> poss[i];
    vc<vc<int>> dist(a, vc<int>(s));
    for(int i=0; i<a; i++){
        vc<int> curd(n);
        dijkstra_shortest_paths(g, posa[i],
            distance_map(boost::make_iterator_property_map(
                curd.begin(), get(boost::vertex_index, g))));
        for(int j=0; j<s; j++){
            dist[i][j] = curd[poss[j]];
        }
    }

    int l=d-1, r=LONG_MAX;
    while(l + 1 != r){
        int mid = l + (r-l)/2;
        Graph G(a + c*s);
        for(int i=0; i<a; i++){
            for(int j=0; j<s; j++){
                if(dist[i][j] == LONG_MAX) continue;
                if(dist[i][j] + d > mid) continue;
                add_edge(i, a+j, G);
                if(c==1 || dist[i][j] + 2*d > mid) continue;
                add_edge(i, a+s+j, G);
            }
        }
        vc<graph_traits<Graph>::vertex_descriptor> mate(a+c*s);
        checked_edmonds_maximum_cardinality_matching(G, &mate[0]);
        int cur = matching_size(G, &mate[0]);
        if(cur == a) r = mid;
        else l = mid;
    }
    cout << r << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}