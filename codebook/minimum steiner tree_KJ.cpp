//NTUJ 0529
#include<bits/stdc++.h>
using namespace std;
char s[100];
map<string,int> ma;
vector<int> pt;
int inf = 1000000000;
int dis[35][35],dp[35][300],mask[5],n,m,ans;
void dfs(int u){
    if(u==4){
        int tmp=0;
        for(int i=0;i<4;i++){
            int big=inf;
            for(int j=0;j<n;j++){
                for(int k=0;k<256;k++){
                    big=min(big,dp[j][k|mask[i]]);
                }
            }
            tmp+=big;
        }
        ans=min(ans,tmp);
        return;
    }
    for(int i=0;i<4;i++){
        int pre=mask[i];
        mask[i]|=(1<<(u*2));
        mask[i]|=(1<<(u*2+1));
        dfs(u+1);
        mask[i]=pre;
    }
}
int main(){
    while(scanf("%d%d",&n,&m)!=EOF && n+m){
        ma.clear();
        pt.clear();
        for(int i=0;i<n;i++){
            scanf("%s",s);
            ma[string(s)]=i;
            for(int j=0;j<n;j++){
                dis[i][j]=inf;
            }
            dis[i][i]=0;
        }
        for(int i=0;i<m;i++){
            int x,y,z;
            scanf("%s",s);
            x=ma[string(s)];
            scanf("%s",s);
            y=ma[string(s)];
            scanf("%d",&z);
            dis[x][y]=min(dis[x][y],z);
            dis[y][x]=dis[x][y];
        }
        for(int k=0;k<n;k++)
        for(int i=0;i<n;i++)
        for(int j=0;j<n;j++){
            if(dis[i][k]+dis[k][j]<dis[i][j]){
                dis[i][j]=dis[i][k]+dis[k][j];
            }
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<256;j++){
                dp[i][j]=inf;
            }
        }
        for(int i=0;i<8;i++){
            scanf("%s",s);
            int x=ma[string(s)];
            pt.push_back(x);
            for(int j=0;j<n;j++){
                dp[j][1<<i]=dis[j][x];
            }
        }
        for(int i=0;i<256;i++){
            if((i&(i-1))==0) continue;
            for(int j=0;j<n;j++){
                for(int k=0;k<i;k++){
                    if((k&i)!=k) continue;
                    dp[j][i]=min(dp[j][i],dp[j][i-k]+dp[j][k]);
                }
            }
            int vi[35]={0};
            for(int j=0;j<n;j++){
                int maxx=inf,pp;
                for(int k=0;k<n;k++){
                    if(vi[k]) continue;
                    if(dp[k][i]<maxx){
                        maxx=dp[k][i];
                        pp=k;
                    }
                }
                vi[pp]=1;
                for(int k=0;k<n;k++){
                    dp[pp][i]=min(dp[pp][i],dp[k][i]+dis[pp][k]);
                }
            }
        }
        ans=inf;
        dfs(0);
        printf("%d\n",ans);
    }
}
