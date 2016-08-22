//NTUJ 0936
#include<bits/stdc++.h>
using namespace std;
//Directed_MST
const int N=305;
const int inf=0x3fffffff;
struct edge{
    int u,v,w;
};
int dis[N],pre[N],num[N],vis[N];
edge edg[N*N];
int Directed_MST(int s,int n,int m){
    int ans=0;
    while(true){
        for(int i=0;i<n;i++) dis[i]=inf;
        for(int i=0;i<m;i++){
            int u=edg[i].u;
            int v=edg[i].v;
            if(edg[i].w<dis[v]){
                pre[v]=u;
                dis[v]=edg[i].w;
            }
        }
        for(int i=0;i<n;i++){
            if(i==s) continue;
            if(dis[i]==inf) return -1;
        }
        int cnt=0;
        memset(num,-1,sizeof(num));
        memset(vis,-1,sizeof(vis));
        dis[s]=0;
        for(int i=0;i<n;i++){
            ans+=dis[i];
            int v=i;
            while(vis[v]==-1 && v!=s){
                vis[v]=i;
                v=pre[v];
            }
            if(v!=s && vis[v]==i){
                for(int u=pre[v];u!=v;u=pre[u])
                    num[u]=cnt;
                num[v]=cnt++;
            }
        }
        if(!cnt) break;
        for(int i=0;i<n;i++){
            if(num[i]!=-1) continue;
            num[i]=cnt++;
        }
        for(int i=0;i<m;i++){
            int &u=edg[i].u;
            int &v=edg[i].v;
            edg[i].w-=dis[v];
            u=num[u];
            v=num[v];
            if(u==v) edg[i--]=edg[--m];
        }
        n=cnt;
        s=num[s];
    }
    return ans;
}
//end
int ma[N][N];
int main(){
    int n,k,m;
    while(scanf("%d%d%d",&n,&m,&k)!=EOF){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                ma[i][j]=inf;
            }
            ma[i][i]=0;
        }
        for(int i=0;i<m;i++){
            int a,b,c;
            scanf("%d%d%d",&a,&b,&c);
            ma[a][b]=min(ma[a][b],c);
        }
        for(int k=0;k<n;k++)
        for(int i=0;i<n;i++)
        for(int j=0;j<n;j++){
            if(ma[i][j]>ma[i][k]+ma[k][j]){
                ma[i][j]=ma[i][k]+ma[k][j];
            }
        }
        int cnt=0;
        for(int i=0;i<k;i++)
        for(int j=0;j<k;j++){
            if(i!=j && ma[i][j]!=inf){
                edg[cnt++]={i,j,ma[i][j]};
            }
        }
        int ans=Directed_MST(0,k,cnt);
        if(ans==-1) puts("sad..");
        else printf("%d\n",ans);
    }
}
