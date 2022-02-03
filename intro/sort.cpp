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

signed main(){
  ios_base::sync_with_stdio(false); cin.tie(0);
  int T; cin >> T;
  for(int t=0; t<T; t++){
    int n; cin >> n;
    if(n==0) continue;
    vc<int> a(n); for(int i=0; i<n; i++) cin >> a[i];
    int x; cin >> x;
    sort(all(a));
    if(x) reverse(all(a));
    for(int cur : a) cout << cur << " ";
    cout << "\n";
  }
  return 0;
}
