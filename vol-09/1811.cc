/* Prime Test, by Abreto<m@abreto.net>. */
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <algorithm>

using namespace std;

/* Miller-Rabin Prime Test, by Abreto<m@abreto.net>. */

namespace miller_rabin {

typedef long long int ll;

ll gcd(ll m, ll n) { return n ? gcd(n, m % n) : m; }

inline ll add(const ll a, const ll b, const ll mod)
{
    ll z = a + b;
    if (z >= mod) z -= mod;
    return z;
}
inline ll mul(ll a, ll b, const ll mod)
{
    ll z = 0;
    if (a >= mod) a %= mod;
    if (b >= mod) b %= mod;
    while (b)
    {
        if (1 & b) z = add(z, a, mod);
        a = add(a, a, mod);
        b >>= 1;
    }
    return z;
}

ll qow(ll a, ll x, ll mod)
{
    ll ret = 1ll;
    while (x)
    {
        if (1 & x) ret = mul(ret, a, mod);
        a = mul(a, a, mod);
        x >>= 1;
    }
    return ret;
}

const int K = 5;
const int p[] = {
    2, 3, 7, 61, 24251
};
const ll strong = 46856248255981ll;
/* 46 856 248 255 981 in (0, 1e16) */

bool mr(ll n, int k)
{
    ll d = n - 1;
    int s = 0;
    while (d > 1 && 0 == (d & 1))
    {
        s++;
        d >>= 1;
    }
    for (int i = 0; i < k; i++)
    {
        ll a = (i < K) ? p[i] : (1 + rand() % (n - 1));
        ll x = qow(a, d, n);
        for (int j = 0; j < s; j++)
        {
            ll xp = mul(x, x, n);
            if (1 == xp && x != 1 && x != n-1) return false;
            x = xp;
        }
        if (x != 1) return false;
    }
    return true;
}

/* 2,3,5,7,11,13 */
const int pre[] = {3, 5, 7, 11, 13};
bool test(ll n, int k = 5)
{
    if (2 == n) return true;
    if (0 == (n & 1)) return false;
    if (strong == n) return false;
    for (int i = 0; i < 5; i++)
    {
        if (n == pre[i]) return true;
        if (n == n / pre[i] * pre[i])
            return false;
    }
    return mr(n, k);
}

}

/* Pollard's rho, by Abreto<m@abreto.net>. */

namespace pollards_rho {

typedef long long int ll;

inline ll add(const ll a, const ll b, ll mod)
{
    ll z = a + b;
    if (z >= mod) z -= mod;
    return z;
}
inline ll mul(ll a, ll b, ll mod)
{
    ll z = 0ll;
    if (a >= mod) a -= a / mod * mod;
    if (b >= mod) b -= b / mod * mod;
    while (b)
    {
        if (1 & b) z = add(z, a, mod);
        a = add(a, a, mod);
        b >>= 1;
    }
    return z;
}

ll gcd(ll m, ll n) { return (0 == n) ? m : gcd(n, m % n); }

ll find(ll n, int c = -1)
{
    ll x = rand() % n;
    ll y = x, k = 2;
    for (int i = 2; ; i++)
    {
        x = add(mul(x, x, n), (n + c) % n, n);
        ll d = gcd( llabs(y - x) , n );
        if (1 != d && n != d) return d;
        if (y == x) return n;
        if (i == k)
        {
            y = x;
            k <<= 1;
        }
    }
}

/** usage:
 * void find(ll n, int c = 107)
 * {
 *   if (1 == n) return;
 *   if ( miller-rabin(n) )
 *   {
 *     n is a prime;
 *     return;
 *   }
 *   ll p = n, k = c;
 *   while (p >= n) p = pollards_rho(p, k--);
 *   find(p, c);
 *   find(n/p, c);
 * }
 **/

}

typedef long long int ll;

ll dfs(ll n)
{
    assert(n > 1);
    // printf("goint to %lld\n", n);
    if (miller_rabin::test(n)) return n;
    ll p = n, k = 107;
    while (p == n) p = pollards_rho::find(p, k--);
    return min( dfs(p) , dfs(n / p) );
}

void proc(void)
{
    ll N;
    scanf("%lld", &N);
    bool is_p = miller_rabin::test(N);
    if (is_p) puts("Prime");
    else printf("%lld\n", dfs(N));
}

int main(void)
{
    int T;
    scanf("%d", &T);
    while (T--) proc();
    return 0;
}
