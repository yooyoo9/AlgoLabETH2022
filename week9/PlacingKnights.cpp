#include <bits/stdc++.h>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/adjacency_list.hpp>
using namespace std;
using namespace boost;
#define int long
#define vc vector
#define f first
#define s second
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
typedef property_map< Graph, edge_residual_capacity_t >::type Resmap;
typedef graph_traits<Graph>::out_edge_iterator EdgeIt;
typedef graph_traits<Graph>::in_edge_iterator InEdgeIt;

void addEdge(int from, int to, int c, Cmap &cmap, Rmap &rmap, Graph &G){
    auto e = add_edge(from, to, G).first;
    auto rev = add_edge(to, from, G).first;
    cmap[e] = c; cmap[rev] = 0;
    rmap[e] = rev; rmap[rev] = e;
}

void solve(){
    int n; cin >> n;
    vc<vc<int>> present(n, vc<int>(n));
    for(int i=0; i<n; i++) for(int j=0; j<n; j++) cin >> present[i][j];
    Graph G(n*n + 2); int source = n*n; int sink = n*n+1;
    Cmap cmap = get(edge_capacity, G);
    Rmap rmap = get(edge_reverse, G);
    Resmap resmap = get(edge_residual_capacity, G);

    vc<pii> pos(8); 
    pos[0] = {-1, -2};
    pos[1] = {-1, 2};
    pos[2] = {1, -2};
    pos[3] = {1, 2};
    pos[4] = {-2, -1};
    pos[5] = {-2, 1};
    pos[6] = {2, -1};
    pos[7] = {2, 1};

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(!present[i][j]) continue;
            if((i+j)%2){
                for(pii cur : pos){
                    int ni = i+cur.f, nj = j+cur.s;
                    if(ni<0 || nj<0 || ni>=n || nj>=n) continue;
                    if(!present[ni][nj]) continue;
                    addEdge(i*n+j, ni*n+nj, 1, cmap, rmap, G);
                }
                addEdge(source, i*n+j, 1, cmap, rmap, G);
            } else addEdge(i*n+j, sink, 1, cmap, rmap, G);
        }
    }
    push_relabel_max_flow(G, source, sink);
    int ans = 0;
    vc<int> vis(n*n+2); vis[source] = 1;
    std::queue<int> q; q.push(source);
    EdgeIt it, itend;
    while(!q.empty()){
        int cur = q.front(); q.pop();
        for(tie(it, itend) = out_edges(cur, G); it != itend; it++){
            int neigh = target(*it, G);
            if(!vis[neigh] && resmap[*it] != 0){
                q.push(neigh); vis[neigh] = 1;
            }
        }
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(!present[i][j]) continue;
            if((i+j)%2 && vis[i*n+j]) ans++;
            else if((i+j)%2==0 && !vis[i*n+j]) ans++;
        }
    }
    cout << ans << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}
