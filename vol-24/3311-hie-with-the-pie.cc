/**
 * PKU 3311, Hie with the Pie,
 * by Abreto<m@abreto.net>. */
#include <cstdio>
#include <algorithm>

using namespace std;

#define MAXN    16
#define inf     (0x3fffffff)

int n;
int g[MAXN][MAXN];
int dp[MAXN][1 << MAXN];

void proc(void)
{
    int i, j, k;
    for(i = 0;i <= n;i++)
        for(j = 0;j <= n;j++)
            scanf("%d", &(g[i][j]));
    for(k = 0;k <= n;k++)
        for(i = 0;i <= n;i++)
            for(j = 0;j <= n;j++)
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
    for ( int s = 0 ; s < (1 << n) ; ++s )
    {
        for (i = 1;i <= n;i++)
        {
            if ( 0 == (s & (1 << (i - 1))) ) continue;
            if ( s == (1 << (i - 1)) )
            {
                dp[i][s] = g[0][i];
                continue;
            }
            dp[i][s] = inf;
            for (j = 1;j <= n;j++)
            {
                if (i == j) continue;
                if (0 == (s & (1 << (j-1)))) continue;
                dp[i][s] = min(dp[i][s], dp[j][s ^ (1 << (i-1))] + g[j][i]);
            }
        }
    }
    int ans = inf;
    for (i = 1;i <= n;i++)
        ans = min(ans, dp[i][(1 << n) - 1] + g[i][0]);
    printf("%d\n", ans);
}

int main(void)
{
    while ( EOF != scanf("%d", &n) && n ) proc();
    return 0;
}
