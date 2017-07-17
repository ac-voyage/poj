/* PKU JudgeOnline. Problem 3461 - Oulipo, by Abreto<m@abreto.net>. */
#include <stdio.h>
#include <string.h>

#define MAXW    10002
#define MAXT    1000002
char W[MAXW];   /* pattern */
char T[MAXT];
int pi[MAXW];

void compute(void)
{
    int i = 0, k = 0;
    int m = strlen(W+1);
    pi[1] = 0;
    for(i = 2;i <= m;i++)
    {
        while(k && W[k+1]!=W[i])
            k = pi[k];
        if(W[k+1] == W[i])
            k++;
        pi[i] = k;
    }
}
int kmp(void)
{
    int i = 0, q = 0;
    int ret = 0;
    int n = strlen(T+1), m = strlen(W+1);
    compute();
    for(i = 1;i <= n;++i)
    {
        while(q && W[q+1]!=T[i])
            q = pi[q];
        if( W[q+1]==T[i])
            q++;
        if(q == m)
        {
            ret++;
            q = pi[q];
        }
    }
    return ret;
}

int main(void)
{
    int N = 0;
    scanf("%d", &N);
    while(N--)
    {
        scanf("%s", W+1);
        scanf("%s", T+1);
        printf("%d\n", kmp());
    }
    return 0;
}
