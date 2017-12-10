#include<bits/stdc++.h>
using namespace std;
typedef long long int LL;
struct P{
    int v,c;
};
vector<P> s[100005];
int id[100005],val[100005],dis[100005],pa[100005][20],near[100005],tr[100005],dfsid;
int cmp(P a,P b){
    return a.c>b.c;
}
void dfs2(int u,int fa,int br){
    id[u]=++dfsid;
    tr[dfsid]=u;
    if(id[u]!=id[fa]+1) br=u;
    near[u]=br;
    sort(s[u].begin(),s[u].end(),cmp);
    for(int i=0;i<s[u].size();i++){
        int v=s[u][i].v;
        if(v==fa) continue;
        dfs2(v,u,br);
    }
}
int dfs(int u,int fa){
    int cnt=1;
    pa[u][0]=fa;
    dis[u]=dis[fa]+1;
    for(int i=0;i<s[u].size();i++){
        int v=s[u][i].v;
        if(v==fa) continue;
        int tmp=dfs(v,u);
        val[v]=s[u][i].c;
        s[u][i].c=tmp;
        cnt+=tmp;
    }
    return cnt;
}
int tree[400005],ans;
void build(int root,int l,int r){
    if(l==r){
        tree[root]=val[tr[l]];
        return;
    }
    int m=(l+r)/2;
    build(root*2,l,m);
    build(root*2+1,m+1,r);
    tree[root]=max(tree[root*2],tree[root*2+1]);
}
void pushdown(int root){
    tree[root*2]=min(tree[root*2],tree[root]);
    tree[root*2+1]=min(tree[root*2+1],tree[root]);
}
void add(int root,int l,int r,int L,int R,int val){
    if(r<L || l>R) return;
    if(L<=l && r<=R){
        tree[root]=min(tree[root],val);
    //printf("(%d,%d)--%d\n",l,r,tree[root]);
        return;
    }
    pushdown(root);
    int m=(l+r)/2;
    add(root*2,l,m,L,R,val);
    add(root*2+1,m+1,r,L,R,val);
    tree[root]=max(tree[root*2],tree[root*2+1]);
    //printf("(%d,%d)--%d\n",l,r,tree[root]);
}
void query(int root,int l,int r){
    if(l==r){
        ans+=val[tr[l]]-tree[root];
        return;
    }
    pushdown(root);
    int m=(l+r)/2;
    query(root*2,l,m);
    query(root*2+1,m+1,r);
}
int pt(int a,int b){
    if(dis[a]>dis[b]) swap(a,b);
    int d=dis[b]-dis[a];
    for(int i=18;i>=0;i--){
        if(d&(1<<i)){
            b=pa[b][i];
        }
    }
    for(int i=18;i>=0;i--){
        if(pa[a][i]!=pa[b][i]){
            a=pa[a][i];
            b=pa[b][i];
        }
    }
    if(a!=b) a=pa[a][0];
    return a;
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int n,m;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) s[i].clear();
        for(int i=1;i<n;i++){
            int x,y,z;
            scanf("%d%d%d",&x,&y,&z);
            s[x].push_back((P){y,z});
            s[y].push_back((P){x,z});
        }
        dfs(1,0);
        for(int i=1;i<=18;i++){
            for(int j=1;j<=n;j++){
                pa[j][i]=pa[pa[j][i-1]][i-1];
            }
        }
        dfsid=0;
        dfs2(1,0,0);
        ans=0;
        build(1,1,n);
        for(int i=n;i<=m;i++){
            int x,y,z;
            scanf("%d%d%d",&x,&y,&z);
            int c=pt(x,y);
            while(x!=c){
                int l,r=id[x];
                if(id[near[x]]<=id[c]) l=id[c]+1,x=c;
                else l=id[near[x]],x=pa[near[x]][0];
                add(1,1,n,l,r,z);
                //printf("(%d,%d)\n",l,r);
            }
            x=y;
            while(x!=c){
                int l,r=id[x];
                if(id[near[x]]<=id[c]) l=id[c]+1,x=c;
                else l=id[near[x]],x=pa[near[x]][0];
                add(1,1,n,l,r,z);
                //printf("(%d,%d)\n",l,r);
            }
        }
        query(1,1,n);
        printf("%d\n",ans);
        /*for(int i=1;i<=n;i++){
            printf("%d----%d %d\n",i,dis[i],near[i]);
        }*/
    }
}
