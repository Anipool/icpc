#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <queue>
#include <map>
#include <set>
#include <bitset>
#include <stack>
#include <deque>
using namespace std;
#define BUG1 puts("BUG11\n")
#define BUG2 puts("BUG22\n")
#define rep(i,a,b) for(int (i)=(a);(i)<=(b);(i)++)
#define rp(i,a) for(int i=0;i<a;i++)
#define mem(a,x) memset(a,x,sizeof(a))
#define FD(i,a,b) for(int i=a;i>=b;i--)
#define STOP  system("pause")
#define PP printf(" ")
#define SET(x,y) memset(x,y,sizeof(x))
#define LN printf("\n");
#define du freopen("in.txt","r",stdin)
#define chu freopen("out.txt","w",stdout)
#define EPS 1e-8

int dblcmp(double x)   {return fabs(x)<EPS?0:x>0?1:-1;}
inline bool insize(int c,int l,int r){if (c>=l&&c<=r) return true; return false;}
template<class T> inline T sqr(T x){return x*x;}
template<class T> inline void checkmin(T &a,T b)    {if(a == -1 || a > b)a = b;}
template<class T> inline void checkmax(T &a,T b)    {if(a < b)    a = b;}
typedef long long   LL;

const int N= 20;       // 点数
const int H_SIZE= 10007;
const int S_SIZE= 1000010;

/*
    从左下角 走到右下角， 每个格子当且只能走一次。

    左下角和右下角 必须走。 且只能有一个插头
    和 hdu3377 基本上一样， 别忘了处理 n=1,m=1的情况。

*/

struct HASHMAP
{
    int head[H_SIZE], nt[S_SIZE], nv;
    LL f[S_SIZE], sta[S_SIZE];
    void init()
    {
        memset(head, -1, sizeof(head));
        nv=0;
    }
    void add(LL st, int h, LL ans)
    {
        f[nv]= ans;
        sta[nv]= st;
        nt[nv]= head[h];
        head[h]= nv++;
    }
    void push(LL st, LL ans)
    {
        int h= st%H_SIZE;
        for(int i=head[h];~i;i=nt[i])
        {
            if(st==sta[i])
            {
                f[i]+= ans;
                return;
            }
        }
        add(st, h, ans);
    }
};

HASHMAP hm[2];
int code[N], n, m, tmp[N], g[N][N], val[N][N];

void decode(int *code, int , LL st)
{
    for(int i=m;i>=0;i--)
    {
        code[i]= st&7;
        st>>= 3;
    }
}
void shift(int *code, int m)
{
    for(int i=m;i>=1;i--)
        code[i]= code[i-1];
    code[0]= 0;
}
LL encode(int *code, int m)
{
    LL st= 0;
    int cnt= 1;
    memset(tmp, -1,sizeof(tmp));
    tmp[0]= 0;

    for(int i=0;i<=m;i++)
    {
        if(tmp[code[i]]==-1)    tmp[code[i]]= cnt++;
        code[i]= tmp[code[i]];
        st<<= 3;
        st|= code[i];
    }
    return st;
}

void init()
{
    char str[N];
    memset(g,0,sizeof(g));
    for(int i=1;i<=n;i++)
    {
        scanf("%s", str);
        for(int j=0;j<m;j++)
        {
            g[i][j+1]= str[j]=='.'?1:0;
        }
    }

    if( g[n][1]&& g[n][m])
        g[n][1]= g[n][m]= 2;

}

void dp_Blank(int i, int j, int cur)
{
    for(int k=0;k<hm[cur].nv;k++)
    {
        decode(code, m, hm[cur].sta[k]);
        int left= code[j-1], up= code[j];

        if(left && up)  // 两个插头， 不可能出现在 左上角
        {
            if(g[i][j]==2)    continue;
            if(left==up)
            {
                continue; // 不能形成环
            }
            else    // 合并不同的连通块
            {
                code[j]= code[j-1]= 0;
                for(int t=0;t<=m;t++)
                    if(code[t]==up)
                    {
                        code[t]= left;
                        break;
                    }
                if(j==m)
                    shift(code, m);
                hm[cur^1].push(encode(code,m), hm[cur].f[k]);
            }
        }
        else if(left || up)
        {
            if(g[i][j]==2)    // 只可能之右下角
            {
                code[j]= code[j-1]= 0;
                if(j==m)
                    shift(code, m);
                hm[cur^1].push(encode(code,m), hm[cur].f[k]);
            }
            else    // 其他情况
            {
                int t= left?left:up;
                if(g[i][j+1])
                {
                    code[j]= t; code[j-1]= 0;
                    hm[cur^1].push(encode(code,m), hm[cur].f[k]);
                }
                if(g[i+1][j])
                {
                    code[j]= 0; code[j-1]= t;
                    if(j==m)
                        shift(code, m);
                    hm[cur^1].push(encode(code,m), hm[cur].f[k]);
                }
            }
        }
        else // 两个插头都没有
        {
            if(g[i][j]==2)    // 左上角
            {
                if(g[i][j+1])
                {
                    code[j-1]= 0; code[j]= 13;
                    hm[cur^1].push(encode(code,m), hm[cur].f[k]);
                }
                if(g[i+1][j])
                {
                    code[j-1]= 13; code[j]= 0;
                    if(j==m)
                        shift(code,m);
                    hm[cur^1].push(encode(code,m), hm[cur].f[k]);
                }
            }
            else    // 普通格子
            {
                if(g[i+1][j]&& g[i][j+1])
                {
                    code[j]= code[j-1]= 13;
                    hm[cur^1].push(encode(code,m), hm[cur].f[k]);
                }
            }
        }

    }


}

void dp_Block(int i, int j, int cur)
{
    for(int k=0;k<hm[cur].nv;k++)
    {
        decode(code,m, hm[cur].sta[k]);
        code[j]= code[j-1]= 0;
        if(j==m)
            shift(code, m);
        hm[cur^1].push(encode(code,m), hm[cur].f[k]);
    }
}

void solve()
{
    int cur= 0;
    hm[cur].init();
    hm[cur].push(0,1);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            hm[cur^1].init();
            if(g[i][j])
                dp_Blank(i,j,cur);
            else
                dp_Block(i,j,cur);
            cur^= 1;
        }
    LL ans=0;
    for(int k=0;k<hm[cur].nv;k++)
        ans+= hm[cur].f[k];
    cout<<ans<<endl;
}

int main(){

    while(~scanf("%d%d", &n,&m))
    {
        if(!n && !m)    break;
        init();
        if(n==1 && m==1) //!! 特殊处理 不能忘。。
        {
            if(g[1][1])
                puts("1");
            else
                puts("0");
            continue;
        }
        solve();
    }


}
