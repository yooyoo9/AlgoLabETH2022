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
    set<int> s;
    for(int i=0; i<q; i++){
      int a,b; cin >> a >> b;
      if(a == 0) s.insert(b);
      else s.erase(b);
    }
    if(s.size()==0){
      cout << "Empty\n";
    }else{
      set<int>::iterator it = s.begin();
      cout << *it++;
      for(; it != s.end(); it++){
	cout << " " << *it;
      }
      cout << "\n";
    }
  }
  return 0;
}
