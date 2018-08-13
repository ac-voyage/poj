/**
 * PKU 1185 - 炮兵阵地
 * by Abreto<m@abreto.net>.
 **/
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define MAXS    (10)

struct abstates
{
    vector<int> s;  // maxsize: 60
    vector<int> cnt;
    int size;
    inline bool valid(int x)
    {
        return !( (x & (x >> 1)) || (x & (x >> 2)) );
    }
    int ab_count(int x)
    {
        int ret = 0;
        while (x)
        {
            ret++;
            x &= (x - 1);
        }
        return ret;
    }
    abstates(void)
    {
        for(int i = 0;i < (1<<MAXS);++i)
            if( valid(i) )
            {
                s.push_back(i);
                cnt.push_back(ab_count(i));
            }
        size = s.size();
    }
    vector<int>::iterator begin(void) { return s.begin(); }
    vector<int>::iterator end(void) { return s.end(); }
    int operator[](const unsigned &pos) const { return s[pos]; }
}states;

int N, M;
char line[16];
int gird[128];
int beforedp[64][64];
int dp[128][64][64];

int main(void)
{
    int i, j;
    scanf("%d%d", &N, &M);
    for(i = 0;i < N;i++)
    {
        scanf("%s", line);
        for(j = 0;j < M;j++)
        {
            gird[i] <<= 1;
            gird[i] |= ('H' == line[j]);
        }
    }
    int limit = (1 << M);
    int ans = 0;
    for(i = 0;i < N;i++)
    {
        for(int a = 0;a < states.size;a++)
        {
            int cur = states[a];
            int delta = states.cnt[a];
            if (cur >= limit) break;
            if (cur & gird[i]) continue;
            for(int b = 0;b < states.size;b++)
            {
                int prev = states[b];
                if (prev >= limit) break;
                if (cur & prev) continue;
                for(int c = 0;c < states.size;c++)
                {
                    int pprev = states[c];
                    if (pprev >= limit) break;
                    if (cur & pprev) continue;
                    dp[i][a][b] = max(dp[i][a][b], dp[i-1][b][c] + delta);
                }
                ans = max(ans, dp[i][a][b]);
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
