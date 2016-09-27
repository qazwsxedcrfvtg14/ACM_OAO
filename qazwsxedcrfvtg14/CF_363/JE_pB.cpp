//#include<bits/stdc++.h>
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<string>
#include<queue>
#include<map>
#define f first
#define s second
using namespace std;
typedef pair<double,double>par;
int ar[200005];
int in[200005];
int main(){
    int n;
    scanf("%d",&n);
    int rot=-1;
    for(int i=0;i<n;i++){
        scanf("%d",&ar[i]),ar[i]--,in[ar[i]]++;
        if(ar[i]==i)
            rot=i;
        }
    queue<int>qu;
    for(int i=0;i<n;i++)
        if(!in[i])qu.push(i);
    while(!qu.empty()){
        int now=qu.front();
        qu.pop();
        in[ar[now]]--;
        if(!in[ar[now]])
            qu.push(ar[now]);
        }
    int ans=0;
    for(int i=0;i<n;i++){
        if(in[i]&&i!=rot){
            ans++;
            if(rot==-1){
                rot=i;
                int now=ar[i];
                while(now!=i)
                    in[now]--,now=ar[now];
                in[i]=0;
                ar[i]=i;
                }
            else{
                int now=ar[i];
                while(now!=i)
                    in[now]--,now=ar[now];
                in[i]--;
                ar[i]=rot;
                }
            }
        }
    printf("%d\n",ans);
    for(int i=0;i<n;i++){
        if(i)putchar(' ');
        printf("%d",ar[i]+1);
        }
    puts("");
    }