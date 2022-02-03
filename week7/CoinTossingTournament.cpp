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
    Graph G(n+m+2); int source = n+m; int sink = source+1;
    Cmap cmap = get(edge_capacity, G);
    Rmap rmap = get(edge_reverse, G);
    vc<int> val(n, 0);
    for(int i=0; i<m; i++){
        int a, b, c; cin >> a >> b >> c;
        if(c==0){
            addEdge(source, i, 1, cmap, rmap, G);
            addEdge(i, a+m, 1, cmap, rmap, G); 
            addEdge(i, b+m, 1, cmap, rmap, G);
        } else if(c==1) val[a]++;
        else val[b]++;
    }
    int opt = 0; int pos = 1; int tot = 0;
    for(int i=0; i<n; i++){
        int cur; cin >> cur; tot += cur;
        if(cur < val[i]) pos = 0;
        addEdge(m+i, sink, cur - val[i], cmap, rmap, G);
        opt += cur - val[i];
    }
    if(!pos || tot != m){cout << "no\n"; return;}
    int flow = push_relabel_max_flow(G, source, sink);
    if(flow == opt) cout << "yes\n";
    else cout << "no\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}