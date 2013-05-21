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
inline int dblcmp(double x) { return fabs(x)<EPS?0:x>0?1:-1; }
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

const int N= 100;       // ����
const int E=200555;   //����
const int INF= 0x3f3f3f3f;
const long long  LINF= 0x3F3F3F3F3F3F3F3FLL;

/*
    �ظ���������
    ������ ÿ����ÿ��״̬+��ѡ���� 3*n
    ������ ÿ����ÿ��״̬+ n����(��֤һ����ֻѡһ��) 3*n
    һ���� ���κ�״̬ ���ܻ����Լ���

    ------------------
    �����Ǹ����������޸Ĺ��ۺ����Ļ����ֵƫ��, �޸Ĺ��ۺ�����TLE��
    ȥ��hhţ�Ľ��ⱨ�棬ԭ������������ 3*n�У�ǰ2*n�����ظ����ǣ� ����n��Ӧ���Ǿ�ȷ���ǣ�hhţ���������û����������
    ��Ϊ��n���Ǿ�ȷ���ǣ����Ե���������ܱ� ���ۺ���������


    �����ҷ���һ�£� ����n�еľ�ȷ�����Ǳ�֤ÿ������ֻѡһ�Ρ�
    �����ܲ��ܲ���n�еľ�ȷ���ǣ� ����ֱ���жϵ�ǰ�����Ƿ��Ѿ���ʹ�ã�
    ���ǻ�ԭ�ɼ򵥵� 01����
    ����: 2*n�У� ÿ����ÿ��״̬
    ����: 2*n��   ÿ����ÿ��״̬(���ĳ����û��ĳ��״̬,��ͨ�� remove_chead()ɾ������)
    ֻ�� ����һ��������� used[]����ʾ ��i�����Ƿ��Ѿ���ѡ�ˣ��Ѿ�ѡ��Ļ����Ͳ�����ѡ�ˡ�dfs()�߼�¼���ж�

    Ȼ��Ȼ���ˡ�����ˬ���� (PS: �������ֺö���Ҳ����ô����....)


*/

bool sb[N][N];

struct DancingLinks
{
    #define NR 100
    #define NC 100
    #define O 20000
    #define rp(A,i,j) for(int i=A[j];i!=j;i=A[i])
    int sz;
    int U[O],D[O],L[O],R[O], C[O], X[O];
    int S[NC], H[NR];
//---------------
    int ans;
    int n;
    bool used[NR];
//---------------
    void init(int _n, int m)
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
        mem(used,0);
        ans= NR;
        n= _n;
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
            checkmin(ans, k);
            return;
        }

        int tmp= NR, c=0;
        rp(R,i,0)
        {
            if(S[i]<tmp)
                tmp= S[c=i];
        }
        rp(D,i,c)
        {
            int t= (X[i]-1)/2;
            if(used[t])    // ���ʹ�ù��� �� continue;
                continue;
            used[t]= 1;
            remove(i);
            rp(R,j,i)  remove(j);
            dfs(k+1);
            rp(L,j,i)  resume(j);
            resume(i);
            used[t]= 0;
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
        //---------
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

    void remove_chead(int c)
    {
        R[L[c]]= R[c];
        L[R[c]]= L[c];
        remove(c);
    }

    #undef NR
    #undef NC
    #undef O
    #undef rp(A,i,j)
};

DancingLinks dlx;
int n, m;

int main(){
    int nca, ica=0;
    sf(nca);
    while(nca--)
    {
        sf(n);
        printf("Case %d: ", ++ica);
        dlx.init(n, 2*n);
        rep(i,0,n-1)    // ��i����
        {
            sf(m);
            rep(j,0,m-1)    // ��j��״̬
            {
                int k;
                sf(k);
                rep(t,0,k-1)
                {
                    int x, y;
                    sf(x); sf(y);   // �ܸ���� x��y״̬
                    dlx.build(i*2+j +1, x*2+y +1);
                }
                // ���ܸ���Լ� ����״̬
                dlx.build(i*2+j+1, i*2+0+1);
                if(m==2)
                    dlx.build(i*2+j+1, i*2+1+1);
            }
            if(m==1)    // ��Ҫ����һ��ɾ��
            {
                dlx.remove_chead(i*2+1+1);
            }
        }

        dlx.dfs(0);
        printf("%d\n", dlx.ans);

    }


}

