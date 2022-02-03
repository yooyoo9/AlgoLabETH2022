#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Delaunay_triangulation_2.h>
using namespace std;
#define int long
#define vc vector

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<int, K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> DT;
typedef K::Point_2 P;
typedef K::FT FT;

void solve(){
    int n, m, r; cin >> n >> m >> r;
    vc<pair<P, int>> pts(n);
    for(int i=0; i<n; i++){
        int x, y; cin >> x >> y;
        pts[i] = make_pair(P(x, y), i);
    }
    DT trig; trig.insert(pts.begin(), pts.end());
    int nfaces = trig.number_of_faces() + 1;
    int idx = 1;
    for(auto face = trig.finite_faces_begin(); face != trig.finite_faces_end(); face++){
        face->info() = idx++;
    }
    vc<vc<pair<FT, int>>> g(nfaces);
    for(auto face = trig.finite_faces_begin(); face != trig.finite_faces_end(); face++){
        int idx = face->info();
        for(int i=0; i<3; i++){
            auto neigh = face->neighbor(i);
            auto v1 = face->vertex((i+1)%3);
            auto v2 = face->vertex((i+2)%3);
            int idx2;
            if(trig.is_infinite(neigh)) idx2 = 0;
            else idx2 = neigh->info();
            FT curd = CGAL::squared_distance(v1->point(), v2->point());
            g[idx].push_back(make_pair(curd, idx2));
            if(idx2==0) g[idx2].push_back(make_pair(curd, idx));
        }
        P takeoff = trig.dual(face);
        P nearest = face->vertex(0)->point();
        FT takeoffd = CGAL::squared_distance(takeoff, nearest);
        g[idx].push_back(make_pair(takeoffd, 0));
        g[0].push_back(make_pair(takeoffd, idx));
    }

    vc<FT> width(nfaces);
    priority_queue<pair<FT, int>> pq; pq.push(make_pair(FT(LONG_MAX) * FT(LONG_MAX), 0));
    while(!pq.empty()){
        FT curd = pq.top().first; int idx = pq.top().second; pq.pop();
        if(width[idx] != 0) continue;
        width[idx] = curd;
        for(auto neigh : g[idx]){
            if(width[neigh.second] != 0) continue;
            FT curw = min(curd, neigh.first);
            pq.push(make_pair(curw, neigh.second));
        }
    }
    for(int i=0; i<m; i++){
        int x, y, s; cin >> x >> y >>s;
        P p(x, y);
        FT curd = FT(r + s) * FT(r + s);
        P nearest = trig.nearest_vertex(p)->point();
        if(CGAL::squared_distance(p, nearest) < curd){cout << "n"; continue;}
        auto face = trig.locate(p);
        if(trig.is_infinite(face)) cout << "y";
        else if(width[face->info()] < 4*curd) cout << "n";
        else cout << "y";
    }
    cout << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}