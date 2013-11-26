#include<iostream>
#include<cstring>
#include<bitset>
#include<algorithm>
#include<vector>
#include<bitset>
#include<cstdio>
using namespace std;
int hashx[9],hashy[9],hashb[9];
char ch[10][10];
inline int blk(int i,int j){
    int x = i / 3, y = j / 3;
    return x * 3 + y;
}
struct Node{
    int x,y,v;
    Node(int _x,int _y,int _v):x(_x),y(_y),v(_v){}
    bool operator < (const Node& A) const {
        return v < A.v;
    }
};
// in this program , we remain the skills used in "bitmask.cc"
inline int count(int mask){
    return bitset<9>(mask).count();
}
bool chk(int &x,int &y){
    vector<Node> vec;
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)if(ch[i][j] == '0'){
            vec.push_back(Node(i,j,count(hashx[i] & hashy[j] & hashb[blk(i,j)])));
        }
    // you can google it when you don't understand some system function
    sort(vec.begin(),vec.end());
    if(vec.size() == 0) {x = y = -1; return 1;}
    else {
        if(vec[0].v==0) return 0;
        else {
            x = vec[0].x,y=vec[0].y;
            return 1;
        }
    }
}
bool dfs(){
    int x,y;
    // everytime we choose a grid that has least possible choose 
    if(!chk(x,y)) return 0;
    if(x == -1) {
        for(int i = 0; i < 9; i++)
            printf("%s",ch[i]);
        return 1;
    }
    int b = blk(x,y);
    int mask = hashx[x] & hashy[y] & hashb[b];
    bool flag = 0;
    for(int i = 8; i >=0; i--) if(1 << i & mask) {
        hashx[x] ^= 1<<i;
        hashy[y] ^= 1<<i;
        hashb[b] ^= 1<<i;
        ch[x][y] = '0' + i + 1;
        flag |= dfs();
        if(flag) return flag;
        hashx[x] ^= 1<<i;
        hashy[y] ^= 1<<i;
        hashb[b] ^= 1<<i;
    }
    ch[x][y] = '0';
    return flag;
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
                hashx[i] ^= 1<<x;
                hashy[j] ^= 1<<x;
                hashb[blk(i,j)] ^= 1<<x;
            }
        dfs();
        puts("");
    }
}
