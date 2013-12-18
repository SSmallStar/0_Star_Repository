/*
一个有死锁的多线程，问题在于waitforsingleobject的位置
一定要注意的是线程的执行顺序是不一定的，你这个线程刚刚改完state另一个线程就进到循环等wait了，可能在此造成死锁
*/

#include <iostream>
#include <Windows.h>
using namespace std;

int num=1;
int state=1;
HANDLE mutex;
DWORD WINAPI printThread(LPVOID lpPara)
{
	
	int s=(int )lpPara;
	while (1)
	{
		//WaitForSingleObject(mutex,INFINITE);
		//!!!!!!wait语句里的INFINITE是问题所在，导致了一直等待，出现可能的死锁？
		
		if(s!=state)
		{
			cout<<"线程"<<s<<"is in the running and the state is"<<state<<endl;
			//ReleaseMutex(mutex);
			Sleep(1000);
		}
		else
		{
			cout<<"线程"<<s<<"is waiting for the mutex !!!!!!!!!!!"<<endl;
			WaitForSingleObject(mutex,INFINITE);
			cout<<"线程"<<s<<"has the mutex !!!!!!!!!!!"<<endl;
			//!!!!wait语句不能放在这里，
			for(int i=0;i<5;i++)
			{
				if(num>75)
				{
					int j;
					cin>>j;
					exit(0);
				}
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
}
int main()
{
	LPDWORD a[3]={0};
	int s[3]={1,2,3};
	mutex=CreateMutex(NULL,false,"print");
	HANDLE thread1=CreateThread(NULL,0,printThread,(void *)s[0],0,a[0]);
	HANDLE thread2=CreateThread(NULL,0,printThread,(void *)s[1],0,a[1]);
	HANDLE thread3=CreateThread(NULL,0,printThread,(void *)s[2],0,a[2]);
	
	CloseHandle(thread1);
	CloseHandle(thread2);
	CloseHandle(thread3);
	CloseHandle(mutex);
	//WaitForSingleObject(mutex,INFINITE);
	//cout<<"the thread id is"<<a[0]<<" "<<a[1]<<" "<<a[2]<<endl;
	//cout<<"the main is end"<<endl;
	/*ReleaseMutex(mutex);*/
	//Sleep(100);
	cin>>s[0];
	return 0;
}