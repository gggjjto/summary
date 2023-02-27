# dp学习

## 1.Cheapest Palindrome

题意：有一个字符串要求通过最小的价值形成一个回文串。

`input`:

第一行：N（字符数量），M（字符串长度）

第二行：字符串

n+2：一个字符的add和delete的价值

```
3 4
abcb
a 1000 1100
b 350 700
c 200 800
```

`output`:

```
900
```

思路：在回文串中add和delete是一样的，代表一个字符的价值是min(add,delete)。

在`i`到`j`的字符串中要形成回文取决于`(i+1,j)`和`（i,j-1)`.

`s[i]==s[j]`时`dp[i][j]=dp[i+1][j-1]`

`s[i]!=s[j]`时`dp[i][j]=min(dp[i+1][j]+v[s[i]],dp[i][j-1]+v[s[j]])`

code：

```c++
#include<iostream>
#include<map>
#include<algorithm>
#include<cmath>
using namespace std;
int a[2001][2001];
int main()
{
	int n,m; cin>>n>>m;
	string s; cin>>s;
	map<char,int> p;
	for(int i=1;i<=n;i++)
	{
		char c;
		int mx,mi;
		cin>>c>>mx>>mi;
		p[c]=min(mx,mi);
	}
	for(int j=1;j<m;j++)
	{
		for(int i=j-1;i>=0;i--)
		{
			if(s[i]==s[j]){
				a[i][j]=a[i+1][j-1];
			}
			else
			{
				a[i][j]=min(a[i+1][j]+p[s[i]],a[i][j-1]+p[s[j]]);
			}
		}
	}
	cout<<a[0][m-1]<<'\n';
}
```

## 2.Coins

题意：有n个硬币，求可以得到多少1-m之间的数。

`iuput`:

第一行：n，m

第二行：前n个数表示硬币的面值，后n个数依次表示硬币的数量。

```
3 10
1 2 4 2 1 1
2 5
1 4 2 1
0 0
```

`output`：

```
8
4
```

思路：多重dp，n个数可以组成的数有多少种，

如果`a[i]`本身可以形成`j`，则`dp[j]=c[i]`（等于a[i]的数量）

要每个数可以形成的`j`进行判断,如果`（j-a[i])`存在则`a[i]`可以形成`j`,并且`a[j]<j`。

code:

```c++
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int n,m,a[110],c[110];
int dp[100010];

void solve() {
	memset(dp,-1,sizeof(dp));
	dp[0]=0;
	for(int i=1; i<=n; i++) {
		for(int j=0; j<=m; j++) {
			if(dp[j]>=0) {
				dp[j]=c[i];
			} else {
				if(j<a[i]||dp[j-a[i]]<=0)
					dp[j]=-1;
				else
					dp[j]=dp[j-a[i]]-1;
			}
		}
	}
}

int main() {
	while(cin>>n>>m,n||m) {
		memset(a,0,sizeof(a));
		memset(c,0,sizeof(c));
		for(int i=1; i<=n; i++) cin>>a[i];
		for(int i=1; i<=n; i++) cin>>c[i];
		solve();
		int ans=0;
		for(int i=1; i<=m; i++) {
			if(dp[i]>=0) {
				ans++;
			}
		}
		cout<<ans<<'\n';
	}
}
```



