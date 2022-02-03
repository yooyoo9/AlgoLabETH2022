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
vc<int> vis, left_node;
int timestep;

void dfs(int cur){
  vis[cur] = timestep++;
  for(int neigh : g[cur]){
    if(vis[neigh] == -1) dfs(neigh);
  }
  left_node[cur] = timestep++;
  return;
}

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
    for(int i=0; i<m; i++) sort(g[i].begin(), g[i].end());
    timestep=0; vis = vc<int>(n, -1); left_node = vc<int>(n, -1);
    dfs(v);
    for(int arr : vis) cout << arr << " ";
    cout << "\n";
    for(int dep : left_node) cout << dep << " ";
    cout << "\n";
  }
  return 0;
}
