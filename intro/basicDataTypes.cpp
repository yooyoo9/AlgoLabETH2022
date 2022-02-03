#include <bits/stdc++.h>
using namespace std;
#define vc vector
#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
const int mod = 1000000007;
using pii = pair<int, int>;

float round_up(float a){
  return round(a * 100) / 100;
}

signed main(){
  ios_base::sync_with_stdio(false); cin.tie(0);
  int T; cin >> T;
  for(int t=0; t<T; t++){
    int a; long long b; string c; double d;
    cin >> a >> b >> c >> d;
    cout << a << " " << b << " " << c << " ";
    cout << setprecision(3) << round_up(d) << "\n";
  }
  return 0;
}
