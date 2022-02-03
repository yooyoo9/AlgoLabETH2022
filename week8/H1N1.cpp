#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Delaunay_triangulation_2.h>
using namespace std;
#define int long
#define vc vector
using pii = pair<int, int>;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> DT;
typedef DT::Vertex_handle Vertex;
typedef DT::Face_handle Face;
typedef DT::Finite_faces_iterator FaceIt;
typedef DT::Edge Edge;
typedef K::Point_2 P;

int solve(){
    int n; cin >> n;
    if(!n) return 1;
    vc<pair<P, int>> pts(n);
    for(int i=0; i<n; i++){
        int x, y; cin >> x >> y;
        pts[i].first = P(x, y); pts[i].second = i;
    }
    DT trig; trig.insert(pts.begin(), pts.end());
    
    int nface = trig.number_of_faces() + 1;
    map<Face, int> fmap; int fidx=1;
    vc<vc<pii>> g(nface);
    for(FaceIt face=trig.finite_faces_begin(); face != trig.finite_faces_end(); face++){
        if(fmap.find(face) == fmap.end()){fmap[face] = fidx++;}
        int curidx = fmap[face];
        for(int i=0; i<3; i++){
            Face neigh = face->neighbor(i);
            P p1 = face->vertex((i+1)%3)->point();
            P p2 = face->vertex((i+2)%3)->point();
            int curd = CGAL::squared_distance(p1, p2);
            int neighidx;
            if(trig.is_infinite(neigh)) neighidx=0;
            else{
                if(fmap.find(neigh) == fmap.end()){fmap[neigh] = fidx++;}
                neighidx = fmap[neigh];
            }
            g[curidx].push_back(make_pair(neighidx, curd));
            if(neighidx==0) g[neighidx].push_back(make_pair(curidx, curd));
        }
    }
    vc<int> width(nface, -1);
    priority_queue<pii> pq; pq.push(make_pair(LONG_MAX, 0));
    while(!pq.empty()){
        pii curp = pq.top(); pq.pop();
        if(width[curp.second] != -1) continue;
        width[curp.second] = curp.first;
        for(pii neigh : g[curp.second]){
            if(width[neigh.first] != -1) continue;
            int curw = min(curp.first, neigh.second);
            pq.push(make_pair(curw, neigh.first));
        }
    }
    int m; cin >> m;
    for(int i=0; i<m; i++){
        int x, y, d; cin >> x >> y >> d;
        P cur(x, y);
        P nearest = trig.nearest_vertex(cur)->point();
        if(CGAL::squared_distance(cur, nearest) < d){cout << "n"; continue;}
        Face curf = trig.locate(cur);
        if(trig.is_infinite(curf)) cout << "y";
        else if(width[fmap[curf]] < 4*d) cout << "n";
        else cout << "y";
    }
    cout << "\n";
    return 0;
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    while(1){if(solve()) break;}
    return 0;
}