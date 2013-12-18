#include <iostream>
#include <Windows.h>
using namespace std;
//在原来的0版本上改进，先取得锁再进行state的判断，以防进行死锁
int num=1;
int state=1;
HANDLE mutex;
DWORD WINAPI printThread(LPVOID lpPara)
{
	
	int s=(int )lpPara;
	cout<<"线程"<<s<<" ID is :"<<GetCurrentThreadId()<<endl;
	while (num<=75)
	{
		cout<<"线程"<<s<<"is waiting for the mutex !!!!!!!!!!!"<<endl;
		WaitForSingleObject(mutex,0);
		cout<<"线程"<<s<<"has the mutex !!!!!!!!!!!"<<endl;
		//!!!!!!wait语句里的INFINITE是问题所在，导致了一直等待，虽然其他线程释放了锁，但是它却不知道，导致了死锁
		if(s!=state)
		{
			ReleaseMutex(mutex);
			cout<<"线程"<<s<<"release the mutex??????"<<endl;
			Sleep(500);
			//sleep语句是必须的，否则几个线程一直在争抢mutex锁，导致真正符合条件的线程得不到mutex
		}
		else
		{
			//WaitForSingleObject(mutex,INFINITE);
			//!!!!wait语句不能放在这里，
			for(int i=0;i<5;i++)
			{
				/*if(num>75)
				{
				int j;
				cin>>j;
				exit(0);
				}*/
				cout<<"线程"<<s<<":"<<num++<<endl;
			}
			cout<<endl;
			
			ReleaseMutex(mutex);
			state=state%3+1;
			cout<<"线程"<<s<<"release the mutex??????"<<endl;
			Sleep(10);
			/*
			!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			@111这里的sleep和时间没有关系，为0的时候也会线程阻塞
			@222这里就算把sleep注释掉，有时候也会死锁？？
			*/
		}
	}
	return 1;
}
int main()
{
	DWORD a[3]={0};
	int s[3]={1,2,3};
	mutex=CreateMutex(NULL,false,"print");
	LPDWORD a0=NULL;
	HANDLE thread1=CreateThread(NULL,0,printThread,(void *)s[0],0,a0);
	HANDLE thread2=CreateThread(NULL,0,printThread,(void *)s[1],0,&a[1]);//线程id的参数应该对DWORD类型取地址
	HANDLE thread3=CreateThread(NULL,0,printThread,(void *)s[2],0,&a[2]);
	WaitForSingleObject(thread1,INFINITE);
	WaitForSingleObject(thread2,INFINITE);
	WaitForSingleObject(thread3,INFINITE);
	cout<<"the thread id are:"<<a0<<","<<a[1]<<","<<a[2]<<"."<<endl;
	CloseHandle(thread1);
	CloseHandle(thread2);
	CloseHandle(thread3);
	CloseHandle(mutex);
	cin>>s[1];
	//return 0;
}