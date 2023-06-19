#include<bits/stdc++.h>
using namespace std;

//储存数据的结构体 
struct process {
	int id;
	vector<int>a;
	vector<int>b;
	vector<int>c;
	bool flag;
};

//银行家算法 
void solve(vector<int>f,vector<process>&p)
{
	int m=p.size();
	int n=f.size();
	int num=m;
	vector<int>q;
	while(num>0)
	{
		int flag2=0;
		for(int i=0;i<m;i++)
		{
			
			if(p[i].flag)
			{
				bool flag1=1;
				for(int j=0;j<n;j++){
					//cout<<p[i].c[j]<<' '<<f[j]<<'\n';
					if(p[i].c[j]>f[j]){
						flag2++;
						flag1=0;
						break;
					}
				}
				if(flag1){
					cout<<"id="<<p[i].id<<'\n';
					q.push_back(p[i].id);
					for(int j=0;j<n;j++){
						f[j]+=p[i].a[j];
					}
					p[i].flag=0;
					num--;
				}
			}
			else{
				flag2++;
			}
		}
		if(flag2>=m){
			break;
		}
	}
	if(num>0){
		cout<<"不安全\n";
	}
	else{
		
		cout<<"安全序列为：\n";
		for(auto it=q.begin();it!=q.end();it++){
			cout<<*it<<' ';
		} 
		cout<<'\n';
	}

}

//获取输入 
int main()
{
	int n,m;
	cout<<"输入资源数和进程数：";
	cin>>n>>m;
	
	vector<int>f(n,0);
	cout<<"输入"<<n<<"个资源数目：";
	for(int i=0;i<n;i++){
		cin>>f[i];
	}
	
	vector<process>p(m);
	for(int i=0;i<m;i++){
		cout<<"目前id是："<<i<<'\n';
		cout<<"输入"<<n<<"个已分配资源：";
		p[i].id=i;
		p[i].flag=1;
		for(int i1=0;i1<n;i1++) {
			int j; cin>>j;
			p[i].a.push_back(j);
		}
		//for(int i1=0;i1<n;i1++) cout<<p[i].a[i1]<<" ";
		//cout<<"\n";
		cout<<"输入"<<n<<"个所需最大资源：";
		for(int i1=0;i1<n;i1++) {
			int j; cin>>j;
			p[i].b.push_back(j);
			j=p[i].b[i1]-p[i].a[i1];
			p[i].c.push_back(j);
		} 
		//for(int i1=0;i1<n;i1++) cout<<p[i].c[i1]<<" ";
		cout<<"-----------------------------------\n";
	} 
	solve(f,p);
}
