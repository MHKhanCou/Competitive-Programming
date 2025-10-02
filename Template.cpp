// In the name of Allah, the most merciful, the most gracious
#include <bits/stdc++.h>
using namespace std;

 #include <ext/pb_ds/assoc_container.hpp>
 #include <ext/pb_ds/tree_policy.hpp>
 using namespace __gnu_pbds;
 template <class T> using ordered_set = tree<T, null_type,
          less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define ll long long
#define pb push_back
#define vl vector<ll>
#define mh ios::sync_with_stdio(false); cin.tie(0);
#define nl '\n'
#define cinv(v) for(auto &it:v)cin>>it;
#define coutv(v) for(auto it:v)cout<<it<<' ';cout<<nl;
#define srt(v) sort(v.begin(),v.end());
#define rsrt(v) sort(v.rbegin(),v.rend());
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define pii pair<int, int>
#define F first
#define S second
#define ld long double
#define no cout << "No\n"
#define yes cout << "Yes\n"
#define dbg(x) cerr << #x << " = " << x << '\n'

const ll N = 5e5 + 5;
const ll INF = LLONG_MAX;
const ll MOD = 1000000007;
const double PI = 2 * acos(0.0);

inline ll gcd(ll a, ll b) { return __gcd(a, b); }
inline ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

void precalc() {}

void solve()
{
    ll n;
    cin>>n;
    vl a(n);
    cinv(a);

    ll ans = 0;
    cout << ans << nl;

}
int main()
{
    mh
    precalc();
    int t = 1; cin>>t; while(t--)
    //int t;cin>>t;fr(i,1,t) cout<<"Case "<<i<<": ",solve();
    //ll t;scanf("%lld",&t);fr(i,1,t) printf("Case %lld: ",i),solve();
    solve();
    return 0;
}
