#include <bits/stdc++.h>
#include <CGAL/Gmpz.h>
#include <CGAL/QP_functions.h>
#include <CGAL/QP_models.h>
using namespace std;
#define int long
#define vc vector

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> LP;
typedef CGAL::Quadratic_program_solution<ET> Sol;

double floor_to_double(const CGAL::Quotient<ET> &x){
    double a = floor(CGAL::to_double(x));
    while(a > x) a-=1;
    while(a + 1 <= x) a+=1;
    return a;
}

void solve(){
    int xx, yy, n; cin >> xx >> yy >> n;
    LP lp(CGAL::SMALLER, false, 0, false, 0);
    int x = 0, y = 1, ans = 2, idx=0;
    for(int i=0; i<n; i++){
        int a, b, c, v; cin >> a >> b >> c >> v;
        // ax + by + c / sqrt(a2+b2) / v >= ans
        int norm = sqrt(a*a + b*b);
        int cst = a * xx + b*yy + c;
        if(cst >= 0){
          lp.set_a(x, idx, -a);
          lp.set_a(y, idx, -b);
          lp.set_b(idx, c);
        } else {
          lp.set_a(x, idx, a);
          lp.set_a(y, idx, b);
          lp.set_b(idx, -c);
        }
        lp.set_a(ans, idx, norm * v);
        idx++;

        // (axx + byy + c) * (ax + by + c) >= 0
        if(cst >= 0){
          lp.set_a(x, idx, -a);
          lp.set_a(y, idx, -b);
          lp.set_b(idx, c);
        } else{
          lp.set_a(x, idx, a);
          lp.set_a(y, idx, b);
          lp.set_b(idx, -c);
        }
        idx++;
    }
    lp.set_c(ans, -1);
    Sol res = CGAL::solve_linear_program(lp, ET());
    auto sol = -res.objective_value();
    cout << floor_to_double(sol) << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    cout << fixed << setprecision(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}