#include<bits/stdc++.h>
using namespace std;

//�������ݵĽṹ�� 
struct process {
	int id;
	vector<int>a;
	vector<int>b;
	vector<int>c;
	bool flag;
};

//���м��㷨 
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
		cout<<"����ȫ\n";
	}
	else{
		
		cout<<"��ȫ����Ϊ��\n";
		for(auto it=q.begin();it!=q.end();it++){
			cout<<*it<<' ';
		} 
		cout<<'\n';
	}

}

//��ȡ���� 
int main()
{
	int n,m;
	cout<<"������Դ���ͽ�������";
	cin>>n>>m;
	
	vector<int>f(n,0);
	cout<<"����"<<n<<"����Դ��Ŀ��";
	for(int i=0;i<n;i++){
		cin>>f[i];
	}
	
	vector<process>p(m);
	for(int i=0;i<m;i++){
		cout<<"Ŀǰid�ǣ�"<<i<<'\n';
		cout<<"����"<<n<<"���ѷ�����Դ��";
		p[i].id=i;
		p[i].flag=1;
		for(int i1=0;i1<n;i1++) {
			int j; cin>>j;
			p[i].a.push_back(j);
		}
		//for(int i1=0;i1<n;i1++) cout<<p[i].a[i1]<<" ";
		//cout<<"\n";
		cout<<"����"<<n<<"�����������Դ��";
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
