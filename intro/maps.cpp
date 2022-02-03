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
    int q; cin >> q;
    map<string, vc<int>> s;
    for(int i=0; i<q; i++){
      int a; string b; cin >> a >> b;
      if(a == 0) s.erase(b);
      else{
	if( s.find(b) == s.end()){
	  vc<int> ar(1); ar[0] = a; s.insert(pair<string, vc<int>>(b, ar));
	}else{
	  s[b].pb(a);
	}
      }
    }
    string ss; cin >> ss;
    vc<int> ar = s[ss]; sort(ar.begin(), ar.end());
    if(ar.size()==0){
      cout << "Empty\n";
    }else{
      cout << ar[0];
      for(int i=1; i<ar.size(); i++){
	cout << " " << ar[i];
      }
      cout << "\n";
    }
  }
  return 0;
}
