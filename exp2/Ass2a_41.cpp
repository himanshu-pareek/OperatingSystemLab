#include <iostream>
#include <unistd.h>
#include <sys/ipc.h>

#include <sys/shm.h> 
#include <stdlib.h>
#include <bits/stdc++.h>
#include <time.h>
using namespace std;

int A[10001];
vector <int >P;

	
int key=5678;
int main()
{
	int np,nc,i,j,shmid,*shm,s;
	long 
	 //struct timespec ts,t;
    //timespec_get(&ts, TIME_UTC);
	//cout<<ts.tv_sec;
    //char buff[100];
    //strftime(buff, sizeof buff, "%D %T", gmtime(&ts.tv_sec));
    //printf("Current time: %s.%09ld UTC\n", buff, ts.tv_nsec);
	for(i=2;i<=10000;++i)
	if(A[i]==0)
	for(j=i*i;j<=10000;j+=i)
	A[j]=1;
	for(i=2;i<=10000;++i)
	if(!A[i])P.push_back(i);
	cin>>np>>nc;
	//cout<<"a";
	if((shmid=shmget(IPC_PRIVATE,7*sizeof(int),IPC_CREAT | 0666))<0)cout<<"err";
	//cout<<"a";
	if((shm=(int*)shmat(shmid,NULL,0))==(int*)-1)cout<<"err";
	//cout<<shm[0];
	shm[5]=shm[6]=0;
	//*(shm+5)=0;
	for(i=0;i<np;++i)
	{
		if(fork()==0)
		{
			cout<<getpid();
			srand(getpid());
			while(1)
			{
				//shm=(int*)shmat(shmid,0,0);
				//srand(clock());
				s=rand()%100;
				cout<<s<<" ";
				//m=(double)(rand()%1000)/1000;
				sleep(s);
				while(1)
				if(shm[5]-shm[6]<5)
				{
					shm[shm[5]%5]=P[rand()%P.size()];
					//timespec_get(&t, TIME_UTC);
					cout<<"producer "<<i<<" "<<shm[shm[5]%5]<<" "<<time(0)<<endl;
					shm[5]++;
					break;
				}
				//exit(0);
			}
		}
	}


	for(i=0;i<nc;++i)
	{
		if(fork()==0)
		{
			cout<<getpid();
			srand(getpid());
			while(1)
			{
				//shm=(int*)shmat(shmid,0,0);
				//srand(getpid());
				s=rand()%100;
				//m=(double)(rand()%1000)/1000;
				cout<<s<<" ";
				sleep(s);
				//cout<<s<<" ";
				while(1)
				if(shm[6]<shm[5])
				{
					//timespec_get(&t, TIME_UTC);
					cout<<"consumer "<<i<<" "<<shm[shm[6]%5]<<" "<<time(0)<<endl;
					shm[6]++;
					break;
				}
				//exit(0);
			}
		}
	}

	sleep(100);
	kill(-1*getpid(), SIGKILL);
}

