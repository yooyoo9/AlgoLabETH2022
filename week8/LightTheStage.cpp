#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
using namespace std;
#define int long
#define vc vector
#define f first
#define s second
using pii = pair<int, int>;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> DT;
typedef DT::Vertex_handle Vertex;
typedef DT::Face_handle Face;
typedef K::Point_2 P;

void solve(){
    int m, n; cin >> m >> n;
    vc<pair<P, pii>> a(m);
    for(int i=0; i<m; i++){
        int x, y, r; cin >> x >> y >> r;
        a[i].f = P(x,y); a[i].s = make_pair(i, r);
    }
    int h; cin >> h;
    vc<pair<P, int>> b(n);
    for(int i=0; i<n; i++){
        int x, y; cin >> x >> y; 
        b[i].f = P(x,y); b[i].s = i;
    }
    int l=-1, r=n;
    vc<int> ans(m); for(int i=0; i<m; i++) ans[i] = i;
    while(l+1 != r){
        int mid = l + (r-l)/2;
        DT trig; trig.insert(b.begin(), b.begin()+mid+1);
        int survived = false;
        for(auto cur : a){
            P nearest = trig.nearest_vertex(cur.f)->point();
            if(CGAL::squared_distance(nearest, cur.f) >= (h+cur.s.s)*(h+cur.s.s)){survived = true; break;}
        }
        if(survived) l = mid;
        else r = mid;
    }
    if(l==-1) for(int i=0; i<m; i++) cout << i << " ";
    else{
      DT trig; trig.insert(b.begin(), b.begin()+l+1);
      for(auto cur : a){
          P nearest = trig.nearest_vertex(cur.f)->point();
          if(CGAL::squared_distance(nearest, cur.f) >= (h+cur.s.s)*(h+cur.s.s)) cout << cur.s.f << " ";
      }
    }
    cout << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}