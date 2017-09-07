#include <bits/stdc++.h>
struct Element
{
    int sum, bi;
    Element (int s, int bi) : sum (s), bi (bi) {}
    bool operator < (const Element &b) const
    {
        return sum > b.sum;
    }
};
const int MAXN = 100000 + 7;
int n, data[2][MAXN];
inline void Merge (int *a, int *b, int *c)
{
    std::priority_queue<Element> qs;
    for (int i = 0; i < n; i++) qs.push (Element (a[i] + b[0], 0));
    for (int i = 0; i < n; i++)
    {
        Element e = qs.top ();
        qs.pop ();
        c[i] = e.sum;
        if (e.bi + 1 < n) qs.push (Element (e.sum - b[e.bi] + b[e.bi + 1], e.bi + 1));
    }
}
int main ()
{
    while (scanf ("%d", &n) == 1)
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < n; j++)
            {
                scanf ("%d", &data[i][j]);
            }
            std::sort (data[i], data[i] + n);
        }
        for (int i = 1; i < 2; i++) Merge (data[0], data[i], data[0]);
        for (int i = 0; i < n; i++) printf ("%d%c", data[0][i], " \n"[i == n - 1]);
    }
    return 0;
}
