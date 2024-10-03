
vector<int> S(N), T(N), FT(2*N);
ll timer = 1;


vector<vector<int>> g(N);

void dfs(ll x,ll par)
{
    S[x] = timer;
    FT[timer] = x;
    timer++;
    for(auto &child: g[x])
    {
        if(child!=par) {
            dfs(child,x);
        }
    }
    T[x] = timer;
    FT[timer] = x;
    timer++;
}
