/*
һ���������Ķ��̣߳���������waitforsingleobject��λ��
һ��Ҫע������̵߳�ִ��˳���ǲ�һ���ģ�������̸߳ոո���state��һ���߳̾ͽ���ѭ����wait�ˣ������ڴ��������
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
		//!!!!!!wait������INFINITE���������ڣ�������һֱ�ȴ������ֿ��ܵ�������
		
		if(s!=state)
		{
			cout<<"�߳�"<<s<<"is in the running and the state is"<<state<<endl;
			//ReleaseMutex(mutex);
			Sleep(1000);
		}
		else
		{
			cout<<"�߳�"<<s<<"is waiting for the mutex !!!!!!!!!!!"<<endl;
			WaitForSingleObject(mutex,INFINITE);
			cout<<"�߳�"<<s<<"has the mutex !!!!!!!!!!!"<<endl;
			//!!!!wait��䲻�ܷ������
			for(int i=0;i<5;i++)
			{
				if(num>75)
				{
					int j;
					cin>>j;
					exit(0);
				}
				cout<<"�߳�"<<s<<":"<<num++<<endl;
			}
			cout<<endl;
			
			ReleaseMutex(mutex);
			state=state%3+1;
			cout<<"�߳�"<<s<<"release the mutex??????"<<endl;
			Sleep(10);
			/*
			!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			@111�����sleep��ʱ��û�й�ϵ��Ϊ0��ʱ��Ҳ���߳�����
			@222��������sleepע�͵�����ʱ��Ҳ����������
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