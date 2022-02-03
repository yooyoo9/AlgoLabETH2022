#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
using namespace std;
using namespace boost;
#define int long
#define vc vector
#define all(x) x.begin(), x.end()

typedef adjacency_list< vecS, vecS, undirectedS > Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex;

void solve(){
    int n, c, f; cin >> n >> c >> f;
    map<int, set<string>> chara;
    for(int i=0; i<n; i++){
        set<string> cur;
        for(int j=0; j<c; j++) {string x; cin >> x; cur.insert(x);}
        chara[i] = cur;
    }
    Graph G(n);
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            vc<string> cur;
            set_intersection(all(chara[i]), all(chara[j]), back_inserter(cur));
            if( (int)(cur.size()) > f) add_edge(i, j, G);
        }
    }
    vc<Vertex> mate(n);
    checked_edmonds_maximum_cardinality_matching(G, &mate[0]);
    int res = matching_size(G, &mate[0]);
    if(2*res != n) cout << "optimal\n";
    else cout << "not optimal\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}