#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>
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
            property< edge_reverse_t, Traits::edge_descriptor,
                property< edge_weight_t, int > > > > >
    Graph;
typedef property_map< Graph, edge_capacity_t >::type Cmap;
typedef property_map< Graph, edge_reverse_t >::type Rmap;
typedef property_map< Graph, edge_residual_capacity_t >::type Resmap;
typedef property_map< Graph, edge_weight_t >::type Wmap;
typedef graph_traits< Graph >::out_edge_iterator EdgeIt;

void addEdge(int from, int to, int c, int w, Cmap &cmap, Rmap &rmap, Wmap &wmap, Graph &G){
    auto e = add_edge(from, to, G).first;
    auto rev = add_edge(to, from, G).first;
    cmap[e] = c; cmap[rev] = 0;
    rmap[e] = rev; rmap[rev] = e;
    wmap[e] = w; wmap[rev] = -w;
}

void solve(){
    int n, s; cin >> n >> s;
    vc<int> init(s); for(int i=0; i<s; i++) cin >> init[i];
    map<pii, int> state; int idx = 0;
    Graph G(2*n + 2); int source = 2*n; int sink = source+1;
    Cmap cmap = get(edge_capacity, G);
    Rmap rmap = get(edge_reverse, G);
    Wmap wmap = get(edge_weight, G);
    Resmap resmap = get(edge_residual_capacity, G);
    vc<vc<pii>> g(s);
    for(int i=0; i<n; i++){
        int x, y, d, a, p; cin >> x >> y >> d >> a >> p; x--; y--;
        pii p1 = make_pair(x, d), p2 = make_pair(y, a);
        if(state.find(p1) == state.end()) {
            state[p1] = idx++;
            g[x].push_back(make_pair(d, idx-1));
        }
        if(state.find(p2) == state.end()){
            state[p2] = idx++;
            g[y].push_back(make_pair(a, idx-1));
        }
        int idx1 = state[p1], idx2 = state[p2];
        addEdge(idx1, idx2, 1, 100 *(a-d) - p, cmap, rmap, wmap, G);
    }
    for(int i=0; i<s; i++){
        vc<pii> cur = g[i];
        if(cur.size() == 0) continue;
        sort(cur.begin(), cur.end());
        addEdge(source, cur[0].second, init[i], 100 * cur[0].first, cmap, rmap, wmap, G);
        for(int j=0; j<cur.size()-1; j++){
            addEdge(cur[j].second, cur[j+1].second, 1000, 100 * (cur[j+1].first - cur[j].first), cmap, rmap, wmap, G);
        }
        addEdge(cur[cur.size()-1].second, sink, 1000, 100 * (100000 - cur[cur.size()-1].first), cmap, rmap, wmap, G);
    }
    successive_shortest_path_nonnegative_weights(G, source, sink);
    int flow = 0;
    EdgeIt it, itend;
    for(tie(it, itend) = out_edges(source, G); it != itend; it++){
        flow += cmap[*it] - resmap[*it];
    }
    int cost = flow * 100 * 100000 - find_flow_cost(G);
    cout << cost << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}