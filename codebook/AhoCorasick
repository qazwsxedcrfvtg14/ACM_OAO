
#pragma GCC optimize ("O3")
#include<bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;
const int maxnode=1000000+5;

namespace AhoCorasick {
    //const int maxnode=10000005;
    const int SIGMA_SIZE=26;
    struct Node {
        Node *fail, *ch[SIGMA_SIZE];
        int cnt, end;
    } mem[maxnode], *root;

    struct AhoCorasick {
        int size;
        void init() {
            memset(mem, 0, sizeof(Node) * (size + 1));
            root = &mem[0];
            size = 0;
        }
        int idx(char c) {
            return c - 'a';
        }
        Node* insert(char* s) {
            Node* now = root;
            for(int i = 0; s[i]; i++) {
                int c = idx(s[i]);
                if(!now->ch[c])
                    now->ch[c] = &mem[++size];
                now = now->ch[c];
            }
            now->end = 1;
            return now;
        }
        void getFail() {
            queue<Node*> que;
            que.push(root);
            while (que.size()) {
                Node* now = que.front();
                que.pop();
                for (int i = 0; i < SIGMA_SIZE; i++) {
                    if (!now->ch[i]) continue;
                    Node* next = now->ch[i];
                    Node* fail = now->fail;
                    while (fail && !fail->ch[i])
                        fail = fail->fail;
                    next->fail = fail ? fail->ch[i] : root;
                    que.push(next);
                }
            }
        }
        vector<pair<int, Node*>> arr;
        void dfs(Node* root, int dis) {
            if (!root) return;
            arr.push_back({-dis, root});
            for (int i = 0; i < SIGMA_SIZE; i++) {
                Node* next = root->ch[i];
                dfs(next, dis + 1);
            }
        }
        void match(char* s) {
            Node* now = root;
            for (int i = 0; s[i]; i++) {
                int c = idx(s[i]);
                while (now && !now->ch[c])
                    now = now->fail;
                now = now ? now->ch[c] : root;
                now->cnt++;
            }
            // match count
            arr.clear();
            dfs(root, 0);
            sort(arr.begin(), arr.end());
            for (auto pr: arr) {
                if (pr.second->fail)
                    pr.second->fail->cnt += pr.second->cnt;
            }
        }
    };
}

AhoCorasick::AhoCorasick AC;
AhoCorasick::Node *treeNode[155];

char s[maxnode];
char arr[155][75];

int main() {
    int n;
    while(scanf("%d", &n) != EOF && n) {
        AC.init();
        for (int i = 0; i < n; i++) {
            scanf("%s", arr[i]);
            treeNode[i] = AC.insert(arr[i]);
        }
        AC.getFail();
        scanf("%s", s);
        AC.match(s);
        int ans = -1;
        for (int i = 0; i < n; i++) {
            ans = max(ans, treeNode[i]->cnt);
        }
        printf("%d\n", ans);
        for (int i = 0; i < n; i++) {
            if (ans == treeNode[i]->cnt)
                puts(arr[i]);
        }
    }
}
