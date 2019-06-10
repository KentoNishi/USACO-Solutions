#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
typedef long long LL;

int N;
double x;
struct Point
{
    LL x, y;
    int segindex;
};
struct Segment
{
    Point p, q;
    int index;
};

bool operator<(Point p1, Point p2) { return p1.x == p2.x ? p1.y < p2.y : p1.x < p2.x; }

// Intersection testing (here, using a standard "cross product" trick)
int sign(LL x)
{
    if (x == 0)
        return 0;
    else
        return x < 0 ? -1 : +1;
}
int operator*(Point p1, Point p2) { return sign(p1.x * p2.y - p1.y * p2.x); }
Point operator-(Point p1, Point p2)
{
    Point p = {p1.x - p2.x, p1.y - p2.y};
    return p;
}
bool isect(Segment &s1, Segment &s2)
{
    Point &p1 = s1.p, &q1 = s1.q, &p2 = s2.p, &q2 = s2.q;
    return ((q2 - p1) * (q1 - p1)) * ((q1 - p1) * (p2 - p1)) >= 0 && ((q1 - p2) * (q2 - p2)) * ((q2 - p2) * (p1 - p2)) >= 0;
}

// What is the y coordinate of segment s when evaluated at x?
double eval(Segment s)
{
    if (s.p.x == s.q.x)
        return s.p.y;
    return s.p.y + (s.q.y - s.p.y) * (x - s.p.x) / (s.q.x - s.p.x);
}
bool operator<(Segment s1, Segment s2) { return s1.index != s2.index && eval(s1) < eval(s2); }
bool operator==(Segment s1, Segment s2) { return s1.index == s2.index; }

int main(void)
{
    ifstream fin("cowjump.in");
    vector<Segment> S;
    vector<Point> P;

    fin >> N;
    for (int i = 0; i < N; i++)
    {
        Segment s;
        fin >> s.p.x >> s.p.y >> s.q.x >> s.q.y;
        s.index = s.p.segindex = s.q.segindex = i;
        S.push_back(s);
        P.push_back(s.p);
        P.push_back(s.q);
    }
    sort(P.begin(), P.end());

    set<Segment> active;
    int ans1, ans2; // sweep across scene to locate just one intersecting pair...
    for (int i = 0; i < N * 2; i++)
    {
        ans1 = P[i].segindex;
        x = P[i].x;
        auto it = active.find(S[ans1]);
        if (it != active.end())
        {
            // segment already there -- we've reached its final endpoint.  check intersection with the
            // pair of segments that becomes adjacent when this one is deleted.
            auto after = it, before = it;
            after++;
            if (before != active.begin() && after != active.end())
            {
                before--;
                if (isect(S[before->index], S[after->index]))
                {
                    ans1 = before->index;
                    ans2 = after->index;
                    break;
                }
            }
            active.erase(it);
        }
        else
        {
            // new segment to add to active set.
            // check for intersections with only the segments directly above and below (if any)
            auto it = active.lower_bound(S[ans1]);
            if (it != active.end() && isect(S[it->index], S[ans1]))
            {
                ans2 = it->index;
                break;
            }
            if (it != active.begin())
            {
                it--;
                if (isect(S[it->index], S[ans1]))
                {
                    ans2 = it->index;
                    break;
                }
            }
            active.insert(S[ans1]);
        }
    }

    if (ans1 > ans2)
        swap(ans1, ans2);
    int ans2_count = 0;
    for (int i = 0; i < N; i++)
        if (S[i].index != ans2 && isect(S[i], S[ans2]))
            ans2_count++;

    ofstream fout("cowjump.out");
    fout << (ans2_count > 1 ? ans2 + 1 : ans1 + 1) << "\n";
    return 0;
}