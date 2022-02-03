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

void addEdge(int from, int to, int c, Cmap &cmap, Rmap &rmap, Graph &G){
    auto e = add_edge(from, to, G).f;
    auto rev = add_edge(to, from, G).f;
    cmap[e] = c; cmap[rev] = 0;
    rmap[e] = rev; rmap[rev] = e;
}

void solve(){
    int h, w; cin >> h >> w; 
    Graph G(26*26 + 26 + 2); int N = 26*26;
    Cmap cmap = get(edge_capacity, G);
    Rmap rmap = get(edge_reverse, G);
    int source = 26*26 + 26; int sink = source + 1;
    string str; cin >> str; 
    vc<int> needed(26);
    for(char x : str) needed[x - 'A']++;
    for(int i=0; i<26; i++){
        addEdge(i+N, sink, needed[i], cmap, rmap, G);
    }

    vc<string> front(h);
    vc<int> pairs(N);
    for(int i=0; i<h; i++) cin >> front[i];
    for(int i=0; i<h; i++){
        for(int j=0; j<w; j++){
            char x; cin >> x;
            int n1 = x - 'A';
            int n2 = front[i][w-1-j] - 'A';
            int idx = min(n1, n2) * 26 + max(n1, n2);
            pairs[idx]++;
        }
    }
    for(int i=0; i<N; i++){
        addEdge(source, i, pairs[i], cmap, rmap, G);
        int l1 = i%26; int l2 = i/26;
        if(l1 == l2){
            addEdge(i, N+l1, pairs[i], cmap, rmap, G);
        } else {
            addEdge(i, N+l1, pairs[i], cmap, rmap, G);
            addEdge(i, N+l2, pairs[i], cmap, rmap, G);
        }
    }
    int flow = push_relabel_max_flow(G, source, sink);
    if(flow == (int) str.length()) cout << "Yes\n";
    else cout << "No\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}
