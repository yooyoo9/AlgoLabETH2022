#include <bits/stdc++.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
using namespace std;
#define int long
#define vc vector
#define f first
#define s second
using pii = pair<int, int>;

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Lp;
typedef CGAL::Quadratic_program_solution<ET> Sol;

double ceil_to_double(const CGAL::Quotient<ET> &x){
    double a = ceil(CGAL::to_double(x));
    while(a < x) a+=1;
    while(a-1 >= x) a-=1;
    return a;
}

void solve(){
    int n, m, h, w; cin >> n >> m >> h >> w;
    vc<pii> a(n); for(int i=0; i<n; i++) cin >> a[i].f >> a[i].s;
    vc<pii> b(m); for(int i=0; i<m; i++) cin >> b[i].f >> b[i].s;
    Lp lp(CGAL::SMALLER, true, 1, false, 0);
    int idx = 0;
    for(int i=0; i<n; i++){
        auto cura = a[i];
        int dx = LONG_MAX, dy = LONG_MAX;
        for(auto curb : b){
            int curdx = abs(cura.f - curb.f);
            int curdy = abs(cura.s - curb.s);
            if(curdx * h >= curdy * w) dx = min(dx, curdx);
            else dy = min(dy, curdy);
        }
        if(dx != LONG_MAX){
            lp.set_a(i, idx, w); lp.set_b(idx, 2*dx-w); idx++;
        } 
        if(dy != LONG_MAX) {
            lp.set_a(i, idx, h); lp.set_b(idx, 2*dy-h); idx++;
        }
    }
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            auto cura = a[i], curb = a[j];
            int dx = abs(cura.f - curb.f);
            int dy = abs(cura.s - curb.s);
            if(dx * h >= dy * w){
                lp.set_a(i, idx, w); lp.set_a(j, idx, w); lp.set_b(idx, 2*dx); idx++;
            } else {
                lp.set_a(i, idx, h); lp.set_a(j, idx, h); lp.set_b(idx, 2*dy); idx++;
            }
        }
    }
    for(int i=0; i<n; i++) lp.set_c(i, -2*(h+w));
    Sol res = CGAL::solve_linear_program(lp, ET());
    cout << ceil_to_double(-res.objective_value()) << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    cout << fixed << setprecision(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}