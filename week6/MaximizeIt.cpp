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
    while(a+1 <= x) a+=1;
    return a;
}

double ceil_to_double(const CGAL::Quotient<ET> &x){
    double a = ceil(CGAL::to_double(x));
    while(a < x) a+=1;
    while(a-1 >= x) a-=1;
    return a;
}

int solve(){
    int p, a, b; cin >> p;
    if(!p) return 1;
    cin >> a >> b;
    Sol res;
    if(p==1){
        LP lp(CGAL::SMALLER, true, 0, false, 0);
        int idx = 0;
        int x=0, y=1;
        lp.set_a(x, idx, 1); lp.set_a(y, idx, 1); lp.set_b(idx, 4); idx++;
        lp.set_a(x, idx, 4); lp.set_a(y, idx, 2); lp.set_b(idx, a*b); idx++;
        lp.set_a(x, idx, -1); lp.set_a(y, idx, 1); lp.set_b(idx, 1);
        lp.set_c(y, -b); lp.set_c(x, a);
        res = CGAL::solve_linear_program(lp, ET());
    } else {
        LP lp(CGAL::LARGER, false, 0, true, 0);
        int idx = 0;
        int x=0, y=1, z=2;
        lp.set_a(x, idx, 1); lp.set_a(y, idx, 1); lp.set_b(idx, -4); idx++;
        lp.set_a(x, idx, 4); lp.set_a(y, idx, 2); lp.set_a(z, idx, 1); lp.set_b(idx, -a*b); idx++;
        lp.set_a(x, idx, -1); lp.set_a(y, idx, 1); lp.set_b(idx, -1);
        lp.set_c(x, a); lp.set_c(y, b); lp.set_c(z, 1);
        res = CGAL::solve_linear_program(lp, ET());
    }
    if(res.is_infeasible()) cout << "no\n";
    else if(res.is_unbounded()) cout << "unbounded\n";
    else{
        CGAL::Quotient<ET> s = res.objective_value();
        if(p==1){s *= -1; cout << floor_to_double(s) << "\n";}
        else cout << ceil_to_double(s) << "\n";
    }
    return 0;
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    cout << fixed << setprecision(0);
    while(true){
        if(solve()) break;
    }
    return 0;
}