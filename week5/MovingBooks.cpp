#include <bits/stdc++.h>
using namespace std;
#define int long
#define vc vector
#define all(x) x.begin(), x.end()

void solve(){
    int n, m; cin >> n >> m;
    vc<int> a(n); for(int i=0; i<n; i++) cin >> a[i];
    vc<int> b(m); for(int i=0; i<m; i++) cin >> b[i];
    sort(all(a)); reverse(all(a));
    sort(all(b)); reverse(all(b));
    if(b[0] > a[0]){cout << "impossible\n"; return;}
    
    int l = 0, r = m;
    while(l+1 != r){
        int mid = l + (r-l)/2;
        if(mid * n < m){l=mid; continue;}
        int pos = 1;
        for(int i=0; i<n; i++){
            if(i*mid >= m) break;
            for(int j=i*mid; j<(i+1)*mid && j<m; j++){
                if(a[i] < b[j]){pos = 0; break;}
            }
            if(!pos) break;
        }
        if(pos) r = mid;
        else l = mid;
    }
    cout << 3*r - 1 << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}