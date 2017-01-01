#include<bits/stdc++.h>
using namespace std;
#define N 20005
vector<int> s[N],scc[N];
stack<int> sta;
int dfs_cnt=0,pre[N]={0},sccno[N]={0},scc_cnt=0,is[N]={0},add[N]={0};
int dfs(int u){
    int lowu,lowv,i;
    lowu=pre[u]=++dfs_cnt;
    sta.push(u);
    for(i=0;i<s[u].size();i++){
        int v=s[u][i];
        if(pre[v]==0){
            lowv=dfs(v);
            lowu=min(lowu,lowv);
        }
        else if(pre[v]<pre[u] && sccno[v]==0){
            lowu=min(lowu,pre[v]);
        }
    }
    if(lowu==pre[u]){
        ++scc_cnt;
        while(sta.size()){
            int x=sta.top();
            sta.pop();
            sccno[x]=scc_cnt;
            scc[scc_cnt].push_back(x);
            if(x==u) break;
        }
    }
    return lowu;
}
int main(){
    int n,m,i,j,x,y,z;
    scanf("%d%d",&n,&m);
    for(i=0;i<m;i++){
        scanf("%d%d%d",&x,&y,&z);
        if(z==1){
            s[y].push_back(x+n);
            s[x+n].push_back(y);
        }
        else{
            s[y].push_back(x);
            s[x+n].push_back(y+n);
        }
    }
    for(i=1;i<=n;i++){
        if(pre[i]==0){
            dfs(i);
        }
    }
    for(i=1;i<=scc_cnt;i++){
        int tmp=0;
        for(j=0;j<scc[i].size();j++){
            int u=scc[i][j];
            if(u>n) u-=n;
            if(is[u]==0){
                tmp++;
                is[u]=1;
            }
        }
        for(j=0;j<scc[i].size();j++){
            int u=scc[i][j];
            if(u>n) u-=n;
            is[u]=0;
        }
        add[i]=tmp;
    }
    for(i=1;i<=n;i++){
        printf("%d\n",add[sccno[i]]-1);
    }
}
