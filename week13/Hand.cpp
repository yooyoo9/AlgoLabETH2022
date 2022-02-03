#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Delaunay_triangulation_2.h>
using namespace std;
#define int long
#define vc vector
#define pb push_back
#define f first
#define s second
#define all(x) x.begin(), x.end()
using pii = pair<int, int>;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> DT;
typedef K::Point_2 P;
typedef DT::Face_handle Face;
typedef DT::Vertex_handle Vertex;

int find(int cur, vc<int> &cmp){
    int rep = cur;
    while(cmp[rep] != rep) rep = cmp[rep];
    return rep;
}

void solve(){
    int n, k, a, b; cin >> n >> k >> a >> b;
    vc<pair<P, int>> pts(n);
    for(int i=0; i<n; i++){
        int x, y; cin >> x >> y; 
        pts[i].f = P(x, y); pts[i].s = i;
    }
    if(n == 2){
        int d = CGAL::squared_distance(pts[0].f, pts[1].f);
        int ans;
        if(b > d) ans = 1;
        else ans = 2 / k;
        cout << d << " " << ans << "\n";
        return;
    }
    DT trig; trig.insert(all(pts));
    vc<pair<Vertex, Vertex>> edges;
    for(auto face = trig.finite_faces_begin(); face != trig.finite_faces_end(); face++){
        for(int i=0; i<3; i++){
            Vertex v1 = face->vertex(i);
            Vertex v2 = face->vertex((i+1)%3);
            edges.pb(make_pair(v1, v2));
        }
    }
    sort(all(edges), [](pair<Vertex, Vertex> &lhs, pair<Vertex, Vertex> &rhs){
        int d1 = CGAL::squared_distance(lhs.f->point(), lhs.s->point());
        int d2 = CGAL::squared_distance(rhs.f->point(), rhs.s->point());
        return d1 < d2;
    });
    int ansf, anss; 
    int cur = n / k;
    vc<int> ar(5); ar[1] = n;
    int foundf=0, founds=0;
    vc<int> rep(n); for(int i=0; i<n; i++) rep[i] = i;
    vc<int> nb(n, 1);
    for(auto curp : edges){
        int d = CGAL::squared_distance(curp.f->point(), curp.s->point());
        // cout << d << " " << b << " " << cur << endl;
        if(!founds && d >= b){
            anss = cur; founds = 1;
        }
        int idx1 = curp.f->info(), idx2 = curp.s->info();
        int rep1 = find(idx1, rep), rep2 = find(idx2, rep);
        if(rep1 == rep2) continue;
        rep[rep1] = rep2;
        if(nb[rep1] >= 4) ar[4]--;
        else ar[nb[rep1]]--;
        if(nb[rep2] >= 4) ar[4]--;
        else ar[nb[rep2]]--;
        nb[rep2] += nb[rep1];
        if(nb[rep2] >= 4) ar[4]++;
        else ar[nb[rep2]]++;

        if(k==4){
            cur = ar[4] + ar[2]/2 + min(ar[3], ar[1]);
            int left2 = ar[2]%2;
            int left13 = abs(ar[3] - ar[1]);
            if(ar[1] > ar[3]){
                if(left2 && left13>=2){left13-=2; cur++;}
                cur += left13/4;
            } else if(ar[3] > ar[1]) {
                cur += (left13 + left2)/2;
            }
        } else if(k==3){
            cur = ar[4] + ar[3] + min(ar[2], ar[1]);
            int left = abs(ar[2] - ar[1]);
            if(ar[2] > ar[1]) cur += left / 2;
            else cur += left / 3;
        } else if(k==2){
            cur = ar[4] + ar[3] + ar[2] + ar[1] / 2;
        } else cur = ar[4] + ar[3] + ar[2] + ar[1];

        if(!foundf && cur < a){
            ansf = d; foundf = 1;
        }
        if(foundf && founds) break;
    }
    if(!founds) anss = cur;
    cout << ansf << " " << anss << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}