#include <bits/stdc++.h>

#define rp(j, l, n) for(decltype(n) j = l; j < n; j++)
#define ll long long
#define pb push_back
#define us unsigned
#define vi vector<ll>
#define vvi vector<vi>
#define vpi vector<pair<ll, ll>>
#define pi pair<ll, ll>
#define si set<ll>
#define msi multiset<ll>
#define what_is(x) cerr << #x << " is " << x <<" ";
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define fac_init(n){fac[0]=fac[1]=inv[1]=fi[0]=fi[1]=1;rp(i,2,n){fac[i]=1ll*fac[i-1]*i%mod;inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;fi[i]=1ll*fi[i-1]*inv[i]%mod;}}
#define inp(v, n) rp(i, 0, n)cin>>v[i];
#define out(v, n) rp(i, 0, n)cerr<<v[i]<<" "; cerr<<endl;
const ll INF = 1e18;

using namespace std;
struct Graph
{
    ll n;
    vector<vector<ll>> ng;
    function<void(ll, ll)> fs_recur_func = [](ll u, ll v){return;};
    function<void(ll)> fs_func = [](ll u){return;};
    function<bool(ll)> fs_break = [](ll u){return false;};
    Graph(ll n) : n(n), ng(vector<vector<ll>>(n)){}
    void input(ll m)
    {
        rp(i, 0, m)
        {
            ll u, v; cin>>u>>v;
            u--; v--;
            ng[v].pb(u);
        }
    }
    void input_dir(ll m)
    {
        rp(i, 0, m)
        {
            ll u, v; cin>>u>>v;
            u--; v--;
            ng[u].pb(v);
        }
    }
    void dfs(ll root)
    {
        vector<ll> src = {root};
        set<ll> srched;
        while(!src.empty())
        {
            ll node = src.back();
            src.pop_back(); srched.insert(node);
            fs_func(node);
            if(fs_break(node))break;
            for(auto ngg : ng[node])if(!srched.count(ngg))
            {
                src.pb(ngg); fs_recur_func(node, ngg);  srched.insert(ngg);
            }
        }
    }
    void bfs(ll root)
    {
        deque<ll> src = {root};
        set<ll> srched;
        while(!src.empty())
        {
            ll node = src.front();
            src.pop_front(); srched.insert(node);
            fs_func(node);
            if(fs_break(node))break;
            for(auto ngg : ng[node])if(!srched.count(ngg))
            {
                src.pb(ngg); fs_recur_func(node, ngg); srched.insert(ngg);
            }
        }
    }
    ll dist(ll u, ll v)
    {
        vector<ll> d(n, -1); d[u] = 0;
        fs_recur_func = [&d](ll x, ll y){d[y] = d[x] + 1;};
        fs_break = [v](ll x){return x == v;};
        bfs(u);
        fs_recur_func = [](ll u, ll v){return;}; fs_break = [](ll u){return false;};
        return d[v];
    }
    vector<ll> dist_vals(ll u)
    {
        vector<ll> d(n, -1); d[u] = 0;
        fs_recur_func = [&d](ll x, ll y){d[y] = d[x] + 1;};
        bfs(u);
        fs_recur_func = [](ll u, ll v){return;};
        return d;
    }
};
int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int TestCases;
    cin>>TestCases;

    while (TestCases--)
    {
        // Your code here
        ll n, m; cin>>n>>m;
        Graph G(n); G.input(m);
        rp(i, 1, n)G.ng[i].pb(i - 1);
        if(m == 0){rp(i, 1, n)cout<<1;cout<<endl;continue;}
        vector<ll> uni(n + 1,0);
        vector<ll> f(n, INF);
        f[0] = 0; ;
        rp(i, 1, n)
        {
            for(auto ngg : G.ng[i])
            {
                f[i] = min(f[i], f[ngg] + 1);
                if(ngg + 1 <= i - f[ngg] - 1){uni[ngg + 1]++; uni[i - f[ngg] - 1]--;}
            }
        }
        rp(i, 1, n)uni[i] += uni[i-1];
        rp(i, 0, n-1)
        {
            if(uni[i] == 0)cout<<1;
            else cout<<0;
        }
        cout<<endl;
    }
    return 0;
}