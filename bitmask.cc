#include<iostream>
#include<bitset>
#include<cstdio>
using namespace std;
int hashx[9],hashy[9],hashb[9];
char ch[10][10];
/********
 * this function is to judge which 9*9 block grid(i,j) locates 
 * *****/
inline int blk(int i,int j){
    int x = i / 3, y = j / 3;
    return x * 3 + y;
}
bool flag;
/********
 * this recursive function find solution from grid(0,0) to grid(8,8)
 * *****/
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
        /*****
         * mask stands for which digits can be choose in this grid
         * ****/
        for(int i = 0; i < 9; i++) if(1 << i & mask) {
                /*******
                 hashx stands for whitch digit can be choose in line x.
                 you can add "cout << (bitset<9>) hashx <<endl;" to understand it
                 * *****/
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
    freopen("./output.txt","w",stdout);
    #endif
    char str[100];
    for(; ~scanf("%s",str) && str[0] != 'e';){
        for(int i = 0; i < 9; i++)
            for(int j = 0; j < 9; j++)
                    ch[i][j] = str[i*9+j] =='.' ? '0' : str[i*9+j];
        memset(hashx,-1,sizeof(hashx));
        memset(hashy,-1,sizeof(hashy));
        memset(hashb,-1,sizeof(hashy));
        int x;
        for(int i = 0; i < 9; i++)
            for(int j = 0; j < 9; j++) if(x = (ch[i][j]-'0')){
                x --;
                // bitmask is a important programming skills
                hashx[i] ^= 1<<x;
                hashy[j] ^= 1<<x;
                hashb[blk(i,j)] ^= 1<<x;
            }
        flag = 0;
        dfs(0,0);
        puts("");
    }
}
