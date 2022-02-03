#include <bits/stdc++.h>
using namespace std;
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
    string a, b; cin >> a >> b;
    cout << a.length() << " " << b.length() << "\n";
    cout << a << b << "\n";
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    char c = a[0]; a[0] = b[0]; b[0] = c;
    cout << a << " " << b << "\n";
  }
  return 0;
}
