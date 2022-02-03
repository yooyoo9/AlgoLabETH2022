#include <bits/stdc++.h>
using namespace std;
#define int long long
#define vc vector
#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
const int mod = 1000000007;
using pii = pair<int, int>;

int n, m;
vc<vc<int>> g;
vc<int> dist;

signed main(){
  ios_base::sync_with_stdio(false); cin.tie(0);
  int T; cin >> T;
  for(int t=0; t<T; t++){
    int v; cin >> n >> m >> v;
    if(n==0) continue;
    g = vc<vc<int>>(n);
    for(int i=0; i<m; i++){
      int a, b; cin >> a >> b;
      g[a].pb(b); g[b].pb(a);
    }
    dist = vc<int>(n, -1);
    queue<int> q; q.push(v); dist[v] = 0;
    while(q.size()){
      int cur = q.front(); q.pop();
      int d = dist[cur] + 1;
      for(int neigh : g[cur]){
	if(dist[neigh] == -1){
	  dist[neigh] = d; q.push(neigh);
	}
      }
    }
    for(int d : dist) cout << d << " ";
    cout << "\n";
  }
  return 0;
}
