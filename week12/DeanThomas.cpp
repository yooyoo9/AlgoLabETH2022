#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
using namespace std;
#define int long
#define vc vector
#define pb push_back
#define all(x) x.begin(), x.end()
#define f first
#define s second
using pii = pair<int, int>;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> DT;
typedef DT::Face_handle Face;
typedef K::Point_2 P;
typedef K::FT FT;

void solve(){
    int n, m, d; cin >> n >> m >> d;
    vc<P> pts(n);
    for(int i=0; i<n; i++){int x, y; cin >> x >> y; pts[i] = P(x, y);}
    
    DT trig; trig.insert(all(pts));
    int nf = trig.number_of_faces() + 1;
    map<Face, int> idx; int curidx = 1;
    vc<vc<pair<int, FT>>> g(nf);
    for(auto face = trig.finite_faces_begin(); face != trig.finite_faces_end(); face++){
        if(idx.find(face) == idx.end()) idx[face] = curidx++;
        int idx1 = idx[face];
        for(int i=0; i<3; i++){
            Face neigh = face->neighbor((i+2)%3);
            P p1 = face->vertex(i)->point();
            P p2 = face->vertex((i+1)%3)->point();
            int idx2;
            if(trig.is_infinite(neigh)) idx2=0;
            else{
                if(idx.find(neigh) == idx.end()) idx[neigh] = curidx++;
                idx2 = idx[neigh];
            }
            FT curd = CGAL::squared_distance(p1, p2);
            g[idx1].pb(make_pair(idx2, curd));
            if(idx2 == 0) g[idx2].pb(make_pair(idx1, curd));
        }
        FT night = CGAL::squared_distance(trig.dual(face), face->vertex(0)->point());
        g[idx1].pb(make_pair(0, night));
        g[0].pb(make_pair(idx1, night));
    }

    vc<FT> dist(nf, -1);
    priority_queue<pair<FT, int>> pq; pq.push(make_pair(FT(LONG_MAX) * FT(LONG_MAX), 0));
    while(!pq.empty()){
        pair<FT, int> cur = pq.top(); pq.pop();
        if(dist[cur.s] != -1) continue;
        dist[cur.s] = cur.f;
        for(auto neigh : g[cur.s]){
            if(dist[neigh.f] != -1) continue;
            FT curd = min(neigh.s, cur.f);
            pq.push(make_pair(curd, neigh.f));
        }
    }

    for(int i=0; i<m; i++){
        int x, y, rad; cin >> x >> y >> rad;
        P cur(x, y);
        P nearest = trig.nearest_vertex(cur)->point();
        FT curd = FT(d+rad) * FT(d+rad);
        int ans = 1;
        if(CGAL::squared_distance(cur, nearest) < curd) ans = 0;
        else{
            Face curf = trig.locate(cur);
            if(trig.is_infinite(curf)) ans = 1;
            else if(dist[idx[curf]] < 4 * curd) ans = 0;
        }
        if(ans) cout << "y";
        else cout << "n";
    }
    cout << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}