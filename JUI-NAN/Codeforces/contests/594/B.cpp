#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

int n, R, v;

int main()
{
    scanf("%d %d %d", &n, &R, &v);

    for (int ni = 0; ni < n; ni++)
    {
        int s, f;
        scanf("%d %d", &s, &f);

        double y = (f-s)/2.0/R;

        double l = 0, r = y+1;
        for (int i = 0; i < 60; i++)
        {
            double mid = (l+r)/2;

            if ( mid+abs(sin(mid) ) < y ) l = mid;
            else r = mid;
        }

        printf("%.9f\n", l*2*R/v);
    }
}
