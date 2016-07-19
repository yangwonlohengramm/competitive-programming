#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

// define x, y as real(), imag()
typedef complex<double> point;
#define x real()
#define y imag()

bool cmp(point a, point b) {
    if (a.x < b.x) return true;
    if (a.x - b.x < EPS && a.y < b.y) return true;
    return false;
}

struct compare_y {
    bool operator() (const point& lhs, const point& rhs) const{
        if (lhs.y < rhs.y) return true;
        else if (lhs.y == rhs.y && lhs.x < rhs.x) return true;
        return false;
    }
};

int main() {
    int n;
    while (scanf("%d", &n) && n != 0) {

        vector<point> coord;
        for (int i=0; i<n; ++i) {
            double xi, yi;
            scanf("%lf%lf", &xi, &yi);
            point t(xi, yi);
            coord.push_back(t);
        }
        sort(coord.begin(), coord.end(), cmp);

        double h = 10000000;
        set<point, compare_y> s;
        s.insert(coord[0]);
        for (int i=1; i<n; ++i) {

            for (auto pt:s) {
                if (abs(pt.x-coord[i].x)-EPS > h) { // bound by x
                    s.erase(pt);
                }
            }
            //printf("(%lf,%lf) len of s is %d\n", coord[i].x, coord[i].y, s.size());
            //printf("h is %lf\n", h);
            point t1 = coord[i]; t1.imag(t1.y - h - EPS);
            point t2 = coord[i]; t2.imag(t2.y + h - EPS);
            for (auto it = s.lower_bound(t1); it != s.upper_bound(t2); ++it) {
                //printf("    (%lf,%lf)\n", (*it).x, (*it).y);
                h = min(h, abs(*it-coord[i]));
            }
            //printf("new h is %lf\n\n", h);


            s.insert(coord[i]);
        }
        if (h + EPS >= 10000)
            printf("INFINITY\n");
        else
            printf("%.4lf\n", h);

    }
}
