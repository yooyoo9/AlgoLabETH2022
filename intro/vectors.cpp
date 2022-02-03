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
    vc<int> ar(n); for(int i=0; i<n; i++) cin >> ar[i];
    int d; cin >> d;
    ar.erase(ar.begin() + d);
    int a, b; cin >> a >> b;
    ar.erase(ar.begin() + a, ar.begin() + b + 1);
    if(ar.size() == 0) cout << "Empty\n";
    else {
      cout << ar[0];
      for(int i=1; i<ar.size(); i++){
	cout << " " << ar[i];
      }
      cout << "\n";
    }
  }
  return 0;
}
