#include <bits/stdc++.h>
using namespace std;
#define int long
#define vc vector
using pii = pair<int, int>;

int N = 5*5*5;
pair<pii, pii> notinit = make_pair(make_pair(-1, -1), make_pair(-1, -1));
vc<vc<vc<pair<pii, pii>>>> next_states(2, vc<vc<pair<pii, pii>>>(5000*N, vc<pair<pii, pii>>(4, notinit)));

int cnt_occ(tuple<int, int, int> cur){
    set<int> dif;
    vc<int> a(3); a[0] = get<0>(cur); a[1] = get<1>(cur); a[2] = get<2>(cur);
    for(int x : a){
        if(x != 0) dif.insert(x);
    }
    return dif.size();
}

int encode(int q, tuple<int, int, int> a, tuple<int, int, int> b){
    int encb = get<0>(b)*25+ get<1>(b)*5 + get<2>(b);
    int enca = get<0>(a)*25+ get<1>(a)*5 + get<2>(a);
    return q*N*N + enca*N + encb;
}

tuple<int, tuple<int, int, int>, tuple<int, int, int>> decode(int x){
    int encb = x%N; x/=N; int enca = x%N; x/=N; int q = x;
    auto a = make_tuple(enca/25, (enca/5)%5, enca%5);
    auto b = make_tuple(encb/25, (encb/5)%5, encb%5);
    return make_tuple(q, a, b);
}

int recurse(int cur, int state, int m, int n, vc<int> &f, map<pii, int> &dp){
    if(cur == n) return 0;
    if(dp.find(make_pair(cur, state)) != dp.end()) return dp[make_pair(cur, state)];
     pair<pii, pii> curs;
    if(next_states[m-2][state][f[cur]-1] == notinit){
        auto curt = decode(state);
        int difq = get<0>(curt); auto a = get<1>(curt), b = get<2>(curt);
        tuple<int, int, int> na, nb;
        if(m==3){
            na = make_tuple(get<1>(a), get<2>(a), f[cur]);
            nb = make_tuple(get<1>(b), get<2>(b), f[cur]);
        } else {
            na = make_tuple(0, get<2>(a), f[cur]);
            nb = make_tuple(0, get<2>(b), f[cur]);
        }
        int s1, s2;
        int ea = cnt_occ(na) * 1000 - (1 << (difq + 1));
        s1 = encode(difq+1, na, b);
        int eb;
        if(difq == 0){
            eb = cnt_occ(nb) * 1000 - (1 << 1);
            s2 = encode(1, nb, a);
        }else{
            eb = cnt_occ(nb) * 1000 - (1 << (difq - 1));
            s2 = encode(difq-1, a, nb);
        }
        curs = make_pair(make_pair(s1, ea), make_pair(s2, eb));
        next_states[m-2][state][f[cur]-1] = curs;
    } else {
        curs = next_states[m-2][state][f[cur]-1];
    }
    int s1 = curs.first.first, s2 = curs.second.first, e1 = curs.first.second, e2 = curs.second.second;
    int ans = 0;
    if(e1 >= 0) ans = recurse(cur+1, s1, m, n, f, dp) + e1;
    if(e2 >= 0) ans = max(ans, recurse(cur+1, s2, m, n, f, dp) + e2);
    dp[make_pair(cur, state)] = ans;
    return ans;
}

void solve(){
    int n, k, m; cin >> n >> k >> m;
    vc<int> f(n); for(int i=0; i<n; i++){cin >> f[i]; f[i]++;}
    map<pii, int> dp;
    int ans = recurse(0, 0, m, n, f, dp);
    cout << ans << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}