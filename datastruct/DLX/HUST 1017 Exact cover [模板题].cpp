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

const int N=20000;       // ����
const int E=200555;   //����
const int INF= 0x3f3f3f3f;
const long long  LINF= 0x3F3F3F3F3F3F3F3FLL;

/*
    ��ʼDLXģ�壬 forѭ��д���� ����TLE��
    Ϊ�˷�ֹ�ٷ����󣬹����ú� rp(A,i,j)

*/


struct DancingLinks
{
/*
    N ��ʾ�������� O ��ʾ�ڵ���
    U[],D[],L[],R[] ��������
    C[i],X[i] ��ʾԪ��i���ڵ���,��
    S[i] ��ʾ��i���»��ж��ٽڵ�
    H[i] ��ʾ��i�еĵ�һ���ڵ�
*/
    #define N 2005
    #define O 200000
    #define rp(A,i,j) for(int i=A[j];i!=j;i=A[i])
    int n, m, sz;
    int U[O],D[O],L[O],R[O], C[O], X[O];
    int S[N], H[N];
//----------
    int ans[N];
//----------
    void init(int _n, int _m)
    {
        mem(S,0);
        mem(H,-1);
        n= _n; m= _m;
        // ��ʼ��ÿ�е�ͷ
        rep(i,0,m)
        {
            U[i]= D[i]= i;
            L[i]= i-1;
            R[i]= i+1;
        }
        L[0]= m; R[m]= 0;
        sz= m+1;
        //-----

    }
    /*
        ��x�� ��y��Ԫ��
    */
    void build(int x, int y)
    {
        C[sz]= y, X[sz]= x, S[y]++;
        D[sz]= D[y];
        U[D[y]]= sz;
        D[y]= sz;
        U[sz]= y;
        if(H[x]==-1)    // ���е�һ��Ԫ��
            H[x]= L[sz]= R[sz]= sz;
        else
        {

            int t= H[x];
            R[sz]= t;
            R[L[t]]= sz;
            L[sz]= L[t];
            L[t]= sz;

        }
        sz++;
    }

    void remove(int y)
    {
        R[L[y]]= R[y];
        L[R[y]]= L[y];
        //for(int i=D[y];i!=y;i=D[i])
        rp(D,i,y)
        {
            //for(int j=R[i];j!=i;j=R[j])
            rp(R,j,i)
            {
                U[D[j]]= U[j];
                D[U[j]]= D[j];
                S[C[j]]--;
            }
        }

    }

    void resume(int y)
    {
        R[L[y]]= L[R[y]]= y;
        //for(int i=U[y];i!=y;i=U[i])
        rp(U,i,y)
        {
            //for(int j=L[i];j!=i;j=L[j])
            rp(L,j,i)
            {
                U[D[j]]= D[U[j]]= j;
                S[C[j]]++;
            }
        }
    }

    bool dfs(int k)
    {
        if(!R[0]) // �ҵ�����
        {
            // ���
            printf("%d", k);
            rep(i,0,k-1)
                printf(" %d", ans[i]);
            LN;
            return 1;
        }
        int c=0, tmp=N;
        rp(R,i,0)
            if(S[i]<tmp)
                tmp=S[c=i];
        remove(c);
        //for(int i=D[c];i!=c;i=D[i])
        rp(D,i,c)
        {
            //for(int j=R[i];j!=i;j=R[j])
            rp(R,j,i)
                remove(C[j]);
            ans[k]= X[i];
            if(dfs(k+1))    return 1;
            //for(int j=L[i];j!=i;j=L[j])
            rp(L,j,i)
                resume(C[j]);
        }
        resume(c);
        return 0;
    }


#undef N
#undef O
#undef rp(A,i,j)
};

DancingLinks dlx;
int n,m;

int main(){
    while(~scanf("%d%d", &n,&m))
    {
        dlx.init(n,m);
        rep(i,1,n)
        {
            int c;
            sf(c);
            while(c--)
            {
                int j;
                sf(j);
                dlx.build(i,j);
            }
        }
        if(!dlx.dfs(0))
            puts("NO");

    }

}
