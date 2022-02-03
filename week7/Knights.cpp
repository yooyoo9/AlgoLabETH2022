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
typedef graph_traits< Graph >::edge_descriptor Edge;
typedef property_map< Graph, edge_capacity_t >::type Cmap;
typedef property_map< Graph, edge_reverse_t >::type Rmap;

void addEdge(int from, int to, int c, Cmap &cmap, Rmap &rmap, Graph &G){
    Edge e = add_edge(from, to, G).first;
    Edge rev = add_edge(to, from, G).first;
    cmap[e] = c; cmap[rev] = 0;
    rmap[e] = rev; rmap[rev] = e;
}

void solve(){
    int m, n, k, c; cin >> m >> n >> k >> c;
    Graph G(n*m*2 + 2);
    Cmap cmap = get(edge_capacity, G);
    Rmap rmap = get(edge_reverse, G);
    int source = n*m*2; int sink = source + 1;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if( (i==0 && j==0) || (i==n-1 && j==m-1) || (i==0 && j==m-1) || (i==n-1 && j==0)) addEdge(n*m + i*m+j, sink, 2, cmap, rmap, G);
            else if(i==0 || j==0 || i==n-1 || j==m-1) addEdge(n*m + i*m+j, sink, 1, cmap, rmap, G);

            for(int xi=-1; xi<2; xi++){
                for(int xj=-1; xj<2; xj++){
                    if(xi*xj != 0 || (xi==0 && xj==0)) continue;
                    int ni = i+xi, nj = j +xj;
                    if(ni<0 || ni>=n || nj<0 || nj>=m) continue;
                    addEdge(n*m + ni*m+nj, i*m+j, 1, cmap, rmap, G);
                }
            }

            addEdge(i*m+j, n*m + i*m+j, c, cmap, rmap, G);
        }
    }
    for(int i=0; i<k; i++){
        int x, y; cin >> x >> y; addEdge(source, y*m+x, 1, cmap, rmap, G);
    }
    int flow = push_relabel_max_flow(G, source, sink);
    cout << flow << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}