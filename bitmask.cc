#include<iostream>
#include<bitset>
#include<cstdio>
using namespace std;
int hashx[9],hashy[9],hashb[9];
char ch[10][10];
inline int blk(int i,int j){
    int x = i / 3, y = j / 3;
    return x * 3 + y;
}
bool flag;
void dfs(int x,int y){
    if(flag) return;
    if(y == 9) {
        y = 0; x ++;
    }
    if(x == 9) {
        flag = 1;
        for(int i = 0; i < 9; i++)
            puts(ch[i]);
        return ;
    }
    int v = ch[x][y] - '0';
    if(v) dfs(x,y+1);
    else {
        int b = blk(x,y);
        int mask = hashx[x] & hashy[y] & hashb[b];
        for(int i = 0; i < 9; i++) if(1 << i & mask) {
            hashx[x] ^= 1<<i;
            hashy[y] ^= 1<<i;
            hashb[b] ^= 1<<i;
            ch[x][y] = '0' + i + 1;
            dfs(x,y+1);
            hashx[x] ^= 1<<i;
            hashy[y] ^= 1<<i;
            hashb[b] ^= 1<<i;
        }
        ch[x][y] = '0';
    }
}
int main(){
    int tst;
    #ifdef input 
    freopen("./sample/text.txt","r",stdin);
    #endif
    cin >> tst;
    for(int casNum = 1; casNum <= tst; casNum++){
        for(int i = 0; i < 9; i++)
            cin >> ch[i];
        memset(hashx,-1,sizeof(hashx));
        memset(hashy,-1,sizeof(hashy));
        memset(hashb,-1,sizeof(hashy));
        int x;
        for(int i = 0; i < 9; i++)
            for(int j = 0; j < 9; j++) if(x = (ch[i][j]-'0')){
                x --;
                hashx[i] ^= 1<<x;
                hashy[j] ^= 1<<x;
                hashb[blk(i,j)] ^= 1<<x;
            }
        flag = 0;
        printf("Scenario #%d:\n",casNum);
        dfs(0,0);
        puts("");
    }
}
