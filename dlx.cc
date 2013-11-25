#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int sz = 9;
const int MAXN = sz * sz * 4 + 4 * sz * sz * sz + 100;
int L[MAXN], R[MAXN], U[MAXN], D[MAXN], cnt[MAXN], belong[MAXN];
pair<int,int> value[MAXN];
inline int blk(int i,int j){
    return i / 3 * 3 + j / 3;
}
char str[1005];
int ans[1005];
void op(){for(int i = 0; i < sz * sz; i++)printf("%d",ans[i]);puts("");}
void add(int u,int v,int R[],int L[]){
    R[v] = R[u];
    L[v] = u;

    L[R[u]] = v;
    R[u] = v;
}
void del(int u){
    cout<<"del:\n";
    R[L[u]] = R[u];
    L[R[u]] = L[u];
    for(int v = U[u]; v != u; v = U[v])
        for(int k = L[v]; k != v; k = L[k]){
            U[D[k]] = U[k];
            D[U[k]] = D[k];
            cnt[belong[k]] --;
        }
}
void res(int u){
    cout<<"res:\n";
    L[R[u]] = u;
    R[L[u]] = u;
    for(int v = D[u]; v != u; v = D[v])
        for(int k = R[v]; k != v; k = R[k]){
            U[D[k]] = k;
            D[U[k]] = k;
            cnt[belong[k]] ++;
        }
}
bool dfs(){
    if(0 == L[0]){
        op();
        return 1;
    }
    int s = -1, mn = 1e9;
    for(int u = R[0]; u; u = R[u]){
        if(0 == cnt[u]) return 0;
        if(cnt[u] < mn){
            mn = cnt[u];
            s = u;
        }
    }
    // should delete row s
    del(s);
    for(int u = D[s]; u != s; u = D[u]){
        //select u
        
        cout<<value[u].first/sz<<" "<<value[u].first %sz<<" "<<value[u].second<<endl;
        ans[value[u].first] = value[u].second;
        for(int v = R[u]; v != u; v = R[v]) {
            int row = belong[v];
            del(row);
        }
        if(dfs()) return 1;
        for(int v = L[u]; v != u; v = L[v]) {
            int row = belong[v];
            res(row);
        }
    }
    res(s);
    return 0;
}
int main(){
    #ifdef input 
    freopen("./sample/text.txt","r",stdin);
    #endif
    for(;~scanf("%s",str) && strcmp(str,"end");){
        L[0] = R[0] = 0;
        int len = sz * sz * 4;
        for(int i = 1; i <= len; i++) {
            add(i-1,i,R,L);
            U[i] = D[i] = i;
            cnt[i] = 0;
        }
        for(int i = 0; i < sz; i++)
            for(int j = 0; j < sz; j++){
                int pos = i * sz + j + 1;
                int v = str[pos - 1] - '0';
                if(v <= 9 && v >= 1); else v = 0;
                for(int p = 1; p <= 9; p++) if(v == 0 || v == p){
                    int x = sz * sz + i * sz + p;
                    int y = 2 * sz * sz + j * sz + p;
                    int b = 3 * sz * sz + blk(i,j) * sz + p;
                    int vec[4] = {pos,x,y,b};
                    L[len+1] = R[len+1] = len+1;
                    for(int i = 0; i < 4; i++){
                        ++len;
                        belong[len] = vec[i];
                        add(vec[i],len,U,D);
                        if(i)add(len-1,len,R,L);
                        cnt[vec[i]] ++;
                        value[len] = make_pair(pos-1,p);
                    }
                }
            }
        dfs();
    }
}
