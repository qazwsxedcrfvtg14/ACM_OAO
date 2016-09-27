#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

vector<int> v[200001];

int clk = 0;
int in[200001], out[200001];

int p[200001][20];

void DFS(int O)
{
    in[O] = ++clk;
    for (int t : v[O]) p[t][0] = O, DFS(t);
    out[O] = ++clk;
}

bool is_anc(int x, int y)
{
    return in[x] <= in[y] && out[y] <= out[x];
}

int dis(int x, int y)
{
    int ans = 0;
    int t;

    t = x;
    for (int i = 19; i >= 0; i--)
    {
        if ( !is_anc(p[t][i], y) )
            ans += (1<<i), t = p[t][i];

        if ( i == 0 && !is_anc(t, y) ) ans++;
    }

    swap(x, y);

    t = x;
    for (int i = 19; i >= 0; i--)
    {
        if ( !is_anc(p[t][i], y) )
            ans += (1<<i), t = p[t][i];

        if ( i == 0 && !is_anc(t, y) ) ans++;
    }

    return ans;
}

int main()
{
    int N;
    scanf("%d", &N);
    p[1][0] = 1;

    for (int Ni = 2; Ni <= N; Ni++)
    {
        scanf("%d", &p[Ni][0]);
        v[p[Ni][0] ].push_back(Ni);
    }

    DFS(1);

    for (int i = 1; i < 20; i++)
        for (int Ni = 1; Ni <= N; Ni++)
            p[Ni][i] = p[p[Ni][i-1] ][i-1];

    int u = 1, v = 1;

    for (int Ni = 2; Ni <= N; Ni++)
    {
        if ( dis(1, Ni) > dis(1, u) )
        {
            if ( dis(Ni, u) > dis(Ni, v) ) v = u;
            u = Ni;
        }
        else if ( dis(u, Ni) > dis(u, v) ) v = Ni;


        printf("%d", dis(u, v));

        if ( Ni != N ) putchar(' ');
        else putchar('\n');
    }
}
