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
typedef property_map< Graph, edge_residual_capacity_t >::type Resmap;
typedef graph_traits<Graph>::out_edge_iterator EdgeIt;

void addEdge(int from, int to, int c, Cmap &cmap, Rmap &rmap, Graph &G){
  auto e = add_edge(from, to, G).first;
  auto rev = add_edge(to, from, G).first;
  cmap[e] = c; cmap[rev] = 0;
  rmap[e] = rev; rmap[rev] = e;
}

void solve(){
  int n, m, s, d; cin >> n >> m >> s >> d;
  Graph G(2*n + 2); int source = 2*n, sink = 2*n+1;
  Cmap cmap = get(edge_capacity, G);
  Rmap rmap = get(edge_reverse, G);
  Resmap resmap = get(edge_residual_capacity, G);
  for(int i=0; i<n; i++){
    addEdge(2*i, 2*i+1, 1, cmap, rmap, G);
  }
  for(int i=0; i<m; i++){
    int x, y; cin >> x >> y; addEdge(2*x+1, 2*y, 1, cmap, rmap, G);
  }
  for(int i=0; i<s; i++){
    int cur; cin >> cur; addEdge(source, 2*cur, 1, cmap, rmap, G);
  }
  for(int i=0; i<d; i++){
    int cur; cin >> cur; addEdge(2*cur+1, sink, 1, cmap, rmap, G);
  }
  int flow = push_relabel_max_flow(G, source, sink);
  cout << flow << "\n";
}

signed main(){
  ios_base::sync_with_stdio(false); cin.tie(0);
  int t; cin >> t; while(t--) solve();
  return 0;
}