//#include<bits/stdc++.h>
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<string>
#include<map>
#define f first
#define s second
using namespace std;
typedef pair<double,double>par;
int dp[105][3];
int main(){
    int n;
    scanf("%d",&n);
    // 0 res
    // 1 sup
    // 2 con
    for(int i=0;i<n;i++){
        int x;
        scanf("%d",&x);
        dp[i+1][0]=min(dp[i][0],min(dp[i][1],dp[i][2]))+1;
        if(x==2||x==3)
            dp[i+1][1]=min(dp[i][0],dp[i][2]);
        else
            dp[i+1][1]=99999999;
        if(x==1||x==3)
            dp[i+1][2]=min(dp[i][0],dp[i][1]);
        else
            dp[i+1][2]=99999999;
        }
    printf("%d\n",min(dp[n][0],min(dp[n][1],dp[n][2])));
    }