#include <ctime>
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cmath>
#include <map>
#include <set>
#include <bitset>
#include <stack>
#include <deque>
#include <assert.h>

using namespace std;
#define BUG1 puts("BUG11\n")
#define BUG2 puts("BUG22\n")
#define rep(i,a,b) for(int (i)=(a);(i)<=(b);(i)++)
#define rp(i,a) for(int i=0;i<a;i++)
#define FD(i,a,b) for(int i=a;i>=b;i--)
#define STOP  system("pause")
#define PP printf(" ")
#define mem(x,y) memset(x,y,sizeof(x))
#define LN printf("\n");
#define du freopen("in.txt","r",stdin)
#define chu freopen("out.txt","w",stdout)
#define EPS 1e-8

#define FI first
#define SE second
#define PB push_back
#define MP make_pair


typedef long long LL;
inline bool insize(int c,int l,int r){if (c>=l&&c<=r) return true; return false;}
template<class T> inline void checkmin(T &a,T b)	{if(a == -1 || a > b)a = b;}
template<class T> inline void checkmax(T &a,T b)	{if(a < b)	a = b;}
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int ,int> II;

int dx[] = {0,1,0,-1};//up Right down Left
int dy[] = {1,0,-1,0};
template<class T> inline void sf(T& x)
{
    char c;
    int mul = 1;
    while((c = getchar()) != EOF)
    {
        if(c == '-')mul = -1;
        if(c >= '0' && c <= '9')
        {
            x = c-'0';
            break;
        }
    }
    if(c == EOF){x = EOF;return;}
    while(c = getchar())
    {
        if(c >= '0' && c <= '9')
        {
            x = (x<<1)+(x<<3)+(c-'0');
        }
        else break;
    }
    x *= mul;
}

const int N= 20;       // ����
const int E=200555;   //����
const int INF= 0x3f3f3f3f;
const long long  LINF= 0x3F3F3F3F3F3F3F3FLL;

/*
    �ظ����ǣ� ÿ�����һ�У� ÿ��������һ�С�
    ����: 2*n*(n+1)   <= 60
    ����: 1^2+2^2+..+n^2<=65

    ��һ�µó�, ���ڱ߳�Ϊ1��С������(i,j)�������ϱ߻����Ϊk=(i-1)*(2*n+1)+j, �����·ֱ�Ϊ k+n,k+n+1,k+2*n+1. (��i�е�j��)
    Ȼ��ö��ÿ��С�����θ��������

    ע���һ���ǣ�
        �ظ�����remove()�ǲ�����ͷ������ɾȥ��ǰ�еġ�
    �ҵķ������ȼ��� 2*n*(n+1)�У���ö�ٵ��������εı��Ѿ��б�ɾȥ���ˣ���Ҫ������ɾȥ���С�
    ��remove()�� ����Ҫ����ͷ������ɾȥ���У� ������һ������ remove_chead();

*/

struct Square
{
    int u,d,l,r;
    Square(){}
    void set(int i, int j, int n)
    {
        u= (i-1)*(2*n+1)+j;
        l= u+n;
        r= u+n+1;
        d= u+2*n+1;
    }
    void pt()
    {
        printf("U=%d  L= %d  R= %d  D= %d\n", u,l,r,d);
    }
};

struct DancingLinks
{
    #define NR 70
    #define NC 70
    #define O 5000
    #define rp(A,i,j) for(int i=A[j];i!=j;i=A[i])
    int sz;
    int U[O],D[O],L[O],R[O], C[O], X[O];
    int S[NC], H[NR];
//---------------
    int ans;
//---------------
    void init(int m)
    {
        mem(H,-1);
        mem(S,0);
        rep(i,0,m)
        {
            U[i]= D[i]= i;
            L[i]= i-1;
            R[i]= i+1;
        }
        L[0]= m, R[m]= 0;
        sz= m+1;
        //-----
        ans= NR;
    }

    void remove(int c)
    {
        rp(D,i,c)
        {
            L[R[i]]= L[i];
            R[L[i]]= R[i];
            S[C[i]]--;
        }
    }
    void resume(int c)
    {
        rp(U,i,c)
        {
            L[R[i]]= R[L[i]]= i;
            S[C[i]]++;
        }
    }
    void dfs(int k)
    {
        if(k+Hash()>=ans)   return;
        if(!R[0])
        {
            ans= k;
            return;
        }

        int tmp= NR, c=0;
        rp(R,i,0)
        {
            //if(S[i]==0) return;     // ??
            if(S[i]<tmp)
                tmp= S[c=i];
        }
        rp(D,i,c)
        {
            remove(i);
            rp(R,j,i)  remove(j);
            dfs(k+1);
            rp(L,j,i)  resume(j);
            resume(i);
        }

    }
    int Hash()
    {
        int ret= 0;
        bool hash[NC]= {0};
        rp(R,c,0)
        {
            if(!hash[c])
            {
                hash[c]= 1;
                ret++;
                rp(D,i,c)
                    rp(R,j,i)
                        hash[C[j]]= 1;
            }
        }
        return ret;
    }
    void build(int r, int c)
    {
        S[c]++; C[sz]=c;X[sz]=r;
        D[sz]= D[c];
        U[D[c]]= sz;
        D[c]= sz;
        U[sz]= c;
        if(H[r]==-1)
            H[r]= L[sz]= R[sz]= sz;
        else
        {
            int h= H[r];
            R[L[h]]= sz;
            L[sz]= L[h];
            R[sz]= h;
            L[h]= sz;
        }
        sz++;
    }

    void remove_chead(int c)    // ����head������ɾ��head
    {
        R[L[c]]= R[c];
        L[R[c]]= L[c];
    }

    #undef NR
    #undef NC
    #undef O
    #undef rp(A,i,j)
};


DancingLinks dlx;
int n,m;
Square sq[30];
bool delv[70];  // delv[i]��ʾ��i�����ɾ����
VI vis;   // ��ʾ�ĸ������������ö�ٵ������εı�

int main(){

    int nca;
    sf(nca);
    while(nca--)
    {
        sf(n);
        mem(delv,0);
        for(sf(m);m;m--)
        {
            int x;
            sf(x);
            delv[x]= 1;
        }
        int cnt= 0;
        rep(i,1,n) rep(j,1,n)
            sq[++cnt].set(i,j,n);
        int numc=0, numr=2*n*(n+1), cntc=0;
        rep(i,1,n)
            numc+= i*i;
        dlx.init(numc); // �����θ���


        rep(len,1,n)    // ö�������α߳�
        {
            rep(x,1,n-len+1) rep(y,1,n-len+1) // ö�����Ͻǵ�
            {
                int xx= x+len-1, yy= y+len-1; // ���½ǵ� (x,y) -> (xx,yy)
                cntc++;     // ��ʾ��ǰ���ĸ�������

                //printf("i= %d  (%d,%d), (%d,%d)\n", cntc, x,y,xx,yy);

                vis.clear();
                rep(i,x,xx) rep(j,y,yy)
                {
                    int t= (i-1)*n+j;
                    if(i==x)        vis.push_back(sq[t].u);
                    if(i==xx)  vis.push_back(sq[t].d);
                    if(j==y)        vis.push_back(sq[t].l);
                    if(j==yy)  vis.push_back(sq[t].r);
                }
//                rep(i,0,vis.size()-1)
//                    printf("%d ", vis[i]);
//                LN;

                // Ȼ����� ���������ϵı��Ƿ��б�ɾȥ��
                bool flag= 0;
                rep(i,0,vis.size()-1)
                    if(delv[vis[i]])
                    {
                        flag= 1;
                        break;
                    }
                if(flag)    // ��ʾ�Ѿ��б߱�ɾ��, ��ɾ����Ӧ����������
                {
                    // �ظ����ǵ�remove()�ǲ�ɾ����ͷ��
                    dlx.remove_chead(cntc);
                    dlx.remove(cntc);
                    //puts("DEL");
                }
                else    // ���� ���м���ȥ
                {
                    rep(i,0,vis.size()-1)
                        dlx.build(vis[i], cntc);
                }

            }

        }
        dlx.dfs(0);
        printf("%d\n", dlx.ans);

    }

}

