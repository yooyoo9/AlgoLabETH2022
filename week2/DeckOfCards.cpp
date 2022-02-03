#include <bits/stdc++.h>
using namespace std;
#define int long
#define vc vector

void solve(){
    int n, k; cin >> n >> k;
    vc<int> a(n+1); 
    for(int i=1; i<=n; i++){
        cin >> a[i]; a[i] += a[i-1];
    }
    int ansi, ansj, nb=LONG_MAX;
    for(int i=0; i<n; i++){
        int l=i, r=n+1;
        while(l+1 != r){
            int mid = l + (r-l)/2;
            if(a[mid] - a[i] > k) r = mid;
            else l = mid;
        }
        while(l > i+1 && a[l] == a[l-1]) l--;
        if(l != i && k - (a[l] - a[i]) < nb){
            ansi = i; ansj = l-1; nb = k - (a[l] - a[i]);
        }
        if(r != n+1 && (a[r] - a[i]) - k < nb){
            ansi = i; ansj = r-1; nb = (a[r] - a[i]) - k;
        }
    }
    cout << ansi << " " << ansj << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}