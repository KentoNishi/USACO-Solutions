#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<pair<int, int>> vpi;

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define trav(a, x) for (auto &a : x)

#define pb push_back
#define rsz resize
#define sz(x) int(x.size())
#define all(x) begin(x), end(x)
#define f first
#define s second

void setIO(string name) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen((name + ".in").c_str(), "r", stdin);
    freopen((name + ".out").c_str(), "w", stdout);
}

int N, L;
vi w, x, d;

void init() {
    setIO("meetings");
    cin >> N >> L;
    w.rsz(N), x.rsz(N), d.rsz(N);
    F0R(i, N)
    cin >> w[i] >> x[i] >> d[i];
    vi inds(N);
    iota(all(inds), 0);
    sort(all(inds), [](int a, int b) { return x[a] < x[b]; });
    // sort cows by their positions on the number line
    vi W, X, D;
    trav(t, inds) {
        W.pb(w[t]);
        X.pb(x[t]);
        D.pb(d[t]);
    }
    // sort the weights, positions, and velocities in order
    // of location on the number line
    swap(w, W), swap(x, X), swap(d, D);
    // set the sorted arrays
    // w=weights, x=positions, d=velocities
}

int getTime() {
    vi lef, rig;
    F0R(i, N) {
        if (d[i] == -1)
            lef.pb(x[i]);
        else
            rig.pb(x[i]);
    }
    // separate vectors for right and left
    // vectors of positions
    vpi v;
    F0R(i, sz(lef)) {
        v.pb({lef[i], w[i]});
    }
    F0R(i, sz(rig)) {
        v.pb({L - rig[i], w[sz(lef) + i]});
    }
    // <(distance to travel,weight)>
    sort(all(v));
    // sort by distance to travel
    int tot = 0;
    // sum of weights
    trav(t, v) tot += t.s;
    trav(t, v) {
        tot -= 2 * t.s;
        if (tot <= 0)
            return t.f;
        // if half the weights have moved
        // return the time it took
    }
}

int main() {
    init();
    int t = getTime();
    // time needed for half the weights
    // to be removed from the line
    queue<int> rig;
    // a queue of cows moving right
    int ans = 0;
    F0R(i, N) {
        // for each cow
        if (d[i] == -1) {
            // if the current cow is going to the left
            while (sz(rig) && rig.front() + 2 * t < x[i]){
                // loop over every cow that is too far to collide
                // with within time t
                rig.pop();
            }
            // add the number of collisions that will occur
            ans += sz(rig);
        } else{
            // if the cow is going to the right
            rig.push(x[i]);
        }
    }
    cout << ans << "\n";
}