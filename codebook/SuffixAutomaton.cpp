// CF 235 C
#include<bits/stdc++.h>
using namespace std;
#define MAXNODE 2000005
#define SIGMA 26
struct node{
    node *fail,*ch[SIGMA];
    int len,cnt,vis;
    node() {fail=0;len=cnt=vis=0;memset(ch,0,sizeof ch);}
}mem[MAXNODE], *root, *last;

int str_cnt;

struct SuffixAutomaton{
    int size;
    inline int idx(char c){return c-'a';}
    inline void init(){
        size = 0;
        root = last = &mem[0];
    }
    // main SAM
    inline void add(char c){
        c = idx(c);
        node *pre = last;
        node *now = &mem[++size];
        now->len = pre->len+1;
        while(pre && !pre->ch[c]){
            pre->ch[c] = now;
            pre = pre->fail;
        }
        if(!pre) now->fail = root;
        else{
            node *q = pre->ch[c];
            if(q->len == pre->len+1) now->fail = q;
            else
            {
                node *nq = &mem[++size];
                nq->len = pre->len+1;
                memcpy(nq->ch, q->ch, sizeof(q->ch));
                nq->fail = q->fail;
                q->fail = now->fail = nq;
                while(pre && pre->ch[c] == q){
                    pre->ch[c] = nq;
                    pre=pre->fail;
                }
            }
        }
        last = now;
    }
    // solve problem
    int C[MAXNODE], ord[MAXNODE];
    void build_cnt(char* s,int n){
        for(int i = 0; i <= size; i++) C[mem[i].len]++;
        for(int i = 1; i <= size; i++) C[i] += C[i-1];
        for(int i = 0; i <= size; i++) ord[--C[mem[i].len]] = i;
        node* now = root;
        for(int i = 0; i < n; i++){
            int c = idx(s[i]);
            now = now->ch[c];
            now->cnt = 1;
        }
        for(int i = size; i >= 0; i--){
            now = &mem[ord[i]];
            if(now->fail) now->fail->cnt += now->cnt;
        }
    }

    int solve(char* s){
        str_cnt++;
        int n = strlen(s), cnt = 0, ans = 0;
        node* now = root;
        for(int i = 0; i < n-1; i++){
            int c = idx(s[i]);
            if(now->ch[c]) cnt++, now = now->ch[c];
            else{
                while(now && !now->ch[c]) now = now->fail;
                if(!now) cnt=0, now=root;
                else cnt = now->len+1, now = now->ch[c];
            }
            while(cnt >= n/2 && now->fail && now->fail->len >= n/2){
                cnt = now->fail->len;
                now = now->fail;
            }
            if(cnt >= n/2 && now->vis != str_cnt){
                ans += now->cnt;
                now->vis = str_cnt;
            }
        }
        return ans;
    }
}SAM;

char s[MAXNODE];
int main(){
    SAM.init();
    scanf("%s",s);
    int n=strlen(s);
    for(int i=0;i<n;i++){
        SAM.add(s[i]);
    }
    SAM.build_cnt(s,n);
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%s",s);
        n=strlen(s);
        for(int i=n;i<n*2;i++) s[i]=s[i-n];
        s[n*2]=0;
        printf("%d\n",SAM.solve(s));
    }
}
