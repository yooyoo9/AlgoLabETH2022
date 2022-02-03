#include <bits/stdc++.h>
#include <CGAL/Gmpz.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
using namespace std;
#define int long
#define vc vector
#define f first
#define s second
using pii = pair<int, int>;

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> LP;
typedef CGAL::Quadratic_program_solution<ET> Sol;

double ceil_to_double(const CGAL::Quotient<ET> &x){
    double a = ceil(CGAL::to_double(x));
    if(a < x) a += 1;
    if(a-1 >= x) a-=1;
    return a;
}

void solve(){
    int n, m, sum; cin >> n >> m >> sum;
    vc<pii> nn(n), mm(m);
    for(int i=0; i<n; i++) cin >> nn[i].f >> nn[i].s;
    for(int i=0; i<m; i++) cin >> mm[i].f >> mm[i].s;
    LP lp(CGAL::SMALLER, false, 0, false, 0);
    int a=0, b=1, c=2, l=3; int idx=0;
    for(int i=0; i<n; i++){
        lp.set_a(a, idx, -nn[i].s);
        lp.set_a(c, idx, -1);
        lp.set_b(idx, -nn[i].f);
        idx++;
    }
    for(int i=0; i<m; i++){
        lp.set_a(a, idx, mm[i].s);
        lp.set_a(c, idx, 1);
        lp.set_b(idx, mm[i].f);
        idx++;
    }
    Sol res = CGAL::solve_linear_program(lp, ET());
    if(res.is_infeasible()){cout << "Yuck!\n"; return;}
    
    if(sum != -1){
        int snx=0, sny=0, smx=0, smy=0;
        for(auto cur : nn){snx += cur.f; sny += cur.s;}
        for(auto cur : mm){smx += cur.f; smy += cur.s;}
        lp.set_a(a, idx, sny - smy);
        lp.set_a(c, idx, n - m);
        lp.set_b(idx, sum + snx - smx);
        idx++;
        res = CGAL::solve_linear_program(lp, ET());
        if(res.is_infeasible()){cout << "Bankrupt!\n"; return;}
    }

    for(auto cur : nn){
        lp.set_a(a, idx, cur.f); lp.set_a(b, idx, -1); lp.set_a(l, idx, -1); lp.set_b(idx, -cur.s); idx++;
        lp.set_a(a, idx, -cur.f); lp.set_a(b, idx, 1); lp.set_a(l, idx, -1); lp.set_b(idx, cur.s); idx++;
    }
    for(auto cur : mm){
        lp.set_a(a, idx, cur.f); lp.set_a(b, idx, -1); lp.set_a(l, idx, -1); lp.set_b(idx, -cur.s); idx++;
        lp.set_a(a, idx, -cur.f); lp.set_a(b, idx, 1); lp.set_a(l, idx, -1); lp.set_b(idx, cur.s); idx++;
    }
    lp.set_c(l, 1);
    res = CGAL::solve_linear_program(lp, ET());
    cout << ceil_to_double(res.objective_value()) << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    cout << fixed << setprecision(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}