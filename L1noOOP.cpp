#include <algorithm>
#include <stack>
#include <queue>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Input macros
#define s(n)                        scanf("%d",&n)
#define sc(n)                       scanf("%c",&n)
#define sl(n)                       scanf("%lld",&n)
#define sf(n)                       scanf("%lf",&n)
#define ss(n)                       scanf("%s",n)
// Useful constants
#define INF                         INT_MAX
#define EPS                         1e-9
#define INFB						1000000000
// Useful hardware instructions
#define bitcount                    __builtin_popcount
#define gcd                         __gcd
// Useful container manipulation / traversal macros
#define fr(i,a,b)               for(int i=a;i<b;i++)
#define foreach(v, c)               for( typeof( (c).begin()) v = (c).begin();  v != (c).end(); ++v)
#define all(a)                      a.begin(), a.end()
#define in(a,b)                     ( (b).find(a) != (b).end())
#define pb                          push_back
#define fill(a,v)                    memset(a, v, sizeof a)
#define sz(a)                       ((int)(a.size()))
#define mp                          make_pair
// Some common useful functions
#define maX(a,b)                     ( (a) > (b) ? (a) : (b))
#define miN(a,b)                     ( (a) < (b) ? (a) : (b))
#define checkbit(n,b)                ( (n >> b) & 1)
#define DREP(a)                      sort(all(a)); a.erase(unique(all(a)),a.end())
#define INDEX(arr,ind)               (lower_bound(all(arr),ind)-arr.begin())

using namespace std;

// Structures //
typedef pair<int,int> ii;
typedef vector<int> vi;							 
typedef vector<ii> vii;							 


int n,i,j,k,sum,sumt[1001],size,v;
int w[1001];
char str[4],lol;
vector< stack<int> > tabela;
bool bol=true;

int main(){
	queue<int> galpao;
	v = 0;
	while(bol){
		if(v == 0)scanf("%d",&n);
		sum = i = 0;
		//printf(" n = %d\n",n);
		memset(w,0,sizeof(w));
		memset(sumt,0,sizeof(sumt));
		while(!galpao.empty())galpao.pop();
		tabela.assign(n,stack<int>());
		//printf(" n = %d\n%d",n,i);
		while(i<n){
			s(w[i]);
			//printf("%d",w[i]);
			i++;
		}
		//printf("%d %d\n",i,n);
		v++;
		while(true){
			//printf("capacidade d 4 = %d\n",w[i]);
			if(scanf(" %s",str) == EOF){
				bol = false;
				break;
			}
			
			size = galpao.size();
			//printf("tamanho galpao = %d\n",size);
			if(!strcmp(str,"ADD")){
				scanf("%d",&k);
				galpao.push(k);
				sum+=k;
				size = galpao.size();
				printf("%d %d\n",size,sum);
			}
			else if(!strcmp(str,"DEL")){
				scanf("%d",&k);
				if(!tabela[k].empty()){
					sumt[k] -= tabela[k].top();
					tabela[k].pop();	
				}
				size = tabela[k].size();
				printf("%d %d\n",k,size);
			}
		
			else if(!strcmp(str,"LOA")){
				scanf("%d",&k);
				//printf("cap restante = %d\n",w[k]);
				if(!galpao.empty()){
					while(galpao.front() <= (w[k] - sumt[k]) && !galpao.empty()){
						int temp = galpao.front();
						tabela[k].push(temp);
						sumt[k] += temp;
						sum -= temp;
						galpao.pop();
					}
				}
				size = tabela[k].size();
				printf("%d %d\n",k,size);
			}
		
			else if(!strcmp(str,"INF")){
				scanf("%d",&k);
				size = tabela[k].size();
				printf("%d %d %d\n",k,size,sumt[k]);			
			}
			else{
				//printf("%s\n",str);
				n = atoi(str);
				break;
			}
	}		
		printf("\n");
		//scanf("%c",&lol);
	}	
	return 0;
}



