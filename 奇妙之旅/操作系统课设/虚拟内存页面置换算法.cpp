#include<bits/stdc++.h>
using namespace std;

const int COMMD=320;
const int PAGE=10;
const int MEM=4;

struct px{
	int index;
	int time;
};


int commds[COMMD+10];
px memory[MEM];
vector<int>a;
vector<int>b;

void commds_init()
{
	int tmp=0;
	for(int i=0;i<COMMD;i++){
		commds[i]=tmp;
		if((i+1)%PAGE==0){
			tmp++;
		}
	}
}

void solve()
{
	srand((unsigned int)time(NULL));
	int cnt=0;
	while(cnt<COMMD)
	{
		int m=rand()%COMMD;
		a.push_back(m);
		cnt++;
		
		m=rand()%(m+2);
		a.push_back(m);
		cnt++;
		
		m=rand()%(COMMD-m-2)+m+2;
		a.push_back(m);
		cnt++;
	}
	
	for(int i=0;i<COMMD;i++)
	{
		b.push_back(commds[a[i]]);
		//cout<<b[i]<<'\n';
	}
}


double FIFO()
{
	int num=0;
	int err=0;
	for(int i=0;i<COMMD;i++)
	{
		bool flag=0;
		for(int j=0;j<num;j++){
			if(memory[j].index==b[i]){
				flag=1;
				break;
			}
		}
		
		if(!flag)
		{
			err++;
			if(num<MEM)
			{
				memory[num++].index=b[i];
			}
			else
			{
				for(int j=1;j<num;j++){
					memory[j-1]=memory[j];
				}
				memory[num-1].index=b[i];
			}
		}	
	}
//	for(int i=0;i<sizeof(memory)/sizeof(memory[1]);i++){
//		cout<<memory[i].index<<'\n';
//	}
	cout<<"FIFO err= "<<err<<'\n';
	return err*1.0/COMMD;
}

double OPT()
{
	int num=0;
	int err=0;
	for(int i=0;i<COMMD;i++)
	{
		bool flag=0;
		for(int j=0;j<num;j++){
			if(memory[j].index == b[i]){
				flag=1;
				break;
			}
		}
		
		if(!flag)
		{
			err++;
			if(num<MEM)
			{
				memory[num++].index=b[i];
			}
			else
			{
				int tmp1=0;
				int index=0;
				for(int j=0;j<num;j++)
				{
					int tmp=0;
					for(int k=i;k<COMMD;k++){
						tmp=k;
						if(memory[j].index==b[k]){
							break;
						}
					}
					if(tmp1<tmp){
						tmp1=tmp;
						index=j;
					}
				}
				memory[index].index=b[i];
			}
		}
	}
	cout<<"OPT err="<<err<<'\n';
	return err*1.0/COMMD;
}

double LRU()
{
	int num=0;
	int err=0;
	for(int i=0;i<COMMD;i++)
	{
		bool flag=0;
		for(int j=0;j<num;j++){
			if(memory[j].index==b[i]){
				flag=1;
				memory[j].time=i;
				break; 
			}
			
		}
		
		if(!flag)
		{
			err++;
			if(num<MEM)
			{
				memory[num].time=i;
				memory[num++].index=b[i];
			}
			else
			{
				int index=0;
				for(int j=0;j<num;j++)
				{
					if(memory[j].time<memory[index].time){						
						index=j;
					}
				}
				memory[index].time=i;
				memory[index].index=b[i];
			}
		}
	}
	cout<<"LRU err="<<err<<'\n';
	return err*1.0/COMMD;
}

int main()
{
	commds_init();
	solve();
	double x=FIFO();
	cout<<"fifo = "<<x<<'\n';
	x=OPT();
	cout<<"opt = "<<x<<'\n';
	x=LRU();
	cout<<"lru = "<<x<<'\n';
	return 0;
}
