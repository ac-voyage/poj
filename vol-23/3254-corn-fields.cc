/**
 * PKU 3254, Corn Fields
 * by Abret <m@abreto.net>.
 **/
#include <cstdio>
#include <vector>

using namespace std;
typedef vector<int> vi;
typedef vi::iterator vii;

#define MAXS    (12)

struct __mystates
{
    vi s;
    bool valid(int i)
    {
        return !( i & (i >> 1) );
    }
    __mystates(void)
    {
        for(int i = 0;i < (1 << MAXS);i++)
            if ( valid(i) )
            {
                s.push_back(i);
            }
    }
    vii begin(void) { return s.begin(); }
    vii end(void) { return s.end(); }
    int operator[](const unsigned &pos) const { return s[pos]; }
}states;

const int mod = 100000000;

int M, N;
int dp[16][1 << MAXS];

int main(void)
{
    int i, j;
    scanf("%d%d", &M, &N);
    int limit = 1 << N;
    dp[0][0] = 1;
    for (i = 1;i <= M;i++)
    {
        int line_s = 0;
        for (j = 0;j < N;j++)
        {
            int f;
            scanf("%d", &f);
            line_s = (line_s << 1) | (0 == f);
        }
        for (vii it = states.begin();it != states.end();it++)
        {
            int cur = *it;
            if (cur >= limit) break;
            if (cur & line_s) continue;
            for (vii jt = states.begin();jt != states.end();jt++)
            {
                int prev = *jt;
                if (prev >= limit) break;
                if (cur & prev) continue;
                dp[i][cur] = (dp[i][cur] + dp[i-1][prev]) % mod;
            }
        }
    }
    int ans = 0;
    for (vii it = states.begin();it != states.end();it++) ans = (ans + dp[M][*it]) % mod;
    printf("%d\n", ans);
    return 0;
}
