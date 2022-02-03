#include <bits/stdc++.h>
#include <boost/graph/biconnected_components.hpp>
#include <boost/graph/adjacency_list.hpp>
using namespace std;
using namespace boost;
#define int long
#define vc vector
using pii = pair<int, int>;

struct edge_component_t
{
    enum
    {
        num = 555
    };
    typedef edge_property_tag kind;
} edge_component;

typedef adjacency_list< vecS, vecS, undirectedS, no_property,
        property< edge_component_t, std::size_t > > Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex;

void solve(){
    int n, m; cin >> n >> m;
    Graph G(n);
    vc<pii> edges(m);
    for(int i=0; i<m; i++){
        int x, y; cin >> x >> y;
        edges[i] = make_pair(x, y);
        add_edge(x, y, G);
    }
    property_map<Graph, edge_component_t >::type component
        = get(edge_component, G);
    size_t num_comps = biconnected_components(G, component);
    vc<vc<pii>> res(num_comps);
    graph_traits<Graph>::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = boost::edges(G); ei != ei_end; ++ei){
        int a = source(*ei, G);
        int b = target(*ei, G);
        int idx = component[*ei];
        res[idx].push_back(make_pair(min(a, b), max(a, b)));
    }
    vc<pii> ans;
    for(auto cur : res){
        if(cur.size() != 1) continue;
        ans.push_back(cur[0]);
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << "\n";
    for(pii cur : ans) cout << cur.first << " " << cur.second << "\n";
}


signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}