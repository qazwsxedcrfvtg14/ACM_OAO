#include <iostream>
#include <cstdio>
#include <set>

using namespace std;

int main()
{
    int N;
    scanf("%d", &N);

    if ( N&1 ) printf("%d\n", (N-1)/2);
    else
    {
        int i = 2;
        while ( i*2 <= N ) i *= 2;
        printf("%d\n", (N-i)/2);
    }
}
