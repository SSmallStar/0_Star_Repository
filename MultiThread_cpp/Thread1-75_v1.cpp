#include <iostream>
#include <Windows.h>
using namespace std;
//��ԭ����0�汾�ϸĽ�����ȡ�����ٽ���state���жϣ��Է���������
int num=1;
int state=1;
HANDLE mutex;
DWORD WINAPI printThread(LPVOID lpPara)
{
	
	int s=(int )lpPara;
	cout<<"�߳�"<<s<<" ID is :"<<GetCurrentThreadId()<<endl;
	while (num<=75)
	{
		cout<<"�߳�"<<s<<"is waiting for the mutex !!!!!!!!!!!"<<endl;
		WaitForSingleObject(mutex,0);
		cout<<"�߳�"<<s<<"has the mutex !!!!!!!!!!!"<<endl;
		//!!!!!!wait������INFINITE���������ڣ�������һֱ�ȴ�����Ȼ�����߳��ͷ�������������ȴ��֪��������������
		if(s!=state)
		{
			ReleaseMutex(mutex);
			cout<<"�߳�"<<s<<"release the mutex??????"<<endl;
			Sleep(500);
			//sleep����Ǳ���ģ����򼸸��߳�һֱ������mutex�����������������������̵߳ò���mutex
		}
		else
		{
			//WaitForSingleObject(mutex,INFINITE);
			//!!!!wait��䲻�ܷ������
			for(int i=0;i<5;i++)
			{
				/*if(num>75)
				{
				int j;
				cin>>j;
				exit(0);
				}*/
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
	return 1;
}
int main()
{
	DWORD a[3]={0};
	int s[3]={1,2,3};
	mutex=CreateMutex(NULL,false,"print");
	LPDWORD a0=NULL;
	HANDLE thread1=CreateThread(NULL,0,printThread,(void *)s[0],0,a0);
	HANDLE thread2=CreateThread(NULL,0,printThread,(void *)s[1],0,&a[1]);//�߳�id�Ĳ���Ӧ�ö�DWORD����ȡ��ַ
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