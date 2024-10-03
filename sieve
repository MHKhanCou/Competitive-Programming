const ll N = 1e5+9;
vector<ll> prime, p(N);
void sieve()
{
    p[1] = 1;
    ll s = 0;
    for(int i=2; i<N; i++)
    {
        if(p[i]==0) {
          prime.push_back(i);
          s++;
        }
        for(int j=0; j<s && i*prime[j]<N; j++)
        {
            p[i*prime[j]] = 1;
            if(i%prime[j]==0) break;
        }
    }
}
