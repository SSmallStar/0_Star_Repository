#include <iostream>
#include <string>
#include <process.h>
#include <windows.h>
using namespace std;
/*��ԭ����1�汾�ϸĽ������̷߳�װ���࣬�����������
��Ҫ�����⣺
�������������ô��ݿ���ֱ���ã�����ֵ�����������Ͳ�����ԭ���ı������ˣ��磺
int a(int &a){b=a;}��b�Ĳ�������Ӱ��a
������أ�
1)���ñ���������ʱ������ʼ���������������

2)����һ����ʼ�����Ͳ�����������������

3)���úͱ����õı���ʵ���ϴ���ͬһ���ڴ������

*/
int num=1;
int s=1;
HANDLE mutex;
class ThreadTest
{
public:
	ThreadTest(string nam,int i)
	{
		name=nam;
		id=i;
	}
	static unsigned __stdcall theThreadFunction(void *para)
	{
		
		ThreadTest *p=(ThreadTest *)para;
		cout<<"the thread"<<p->id<<"is creat"<<endl;
		cout<<p->name<<"mutex is:"<<mutex<<endl;
		while(num<=75)
		{
			WaitForSingleObject(mutex,0);
			if(p->id!=s)
			{
				//cout<<p->name<<" the state is not true,is "<<s<<endl;
				ReleaseMutex(mutex);
				Sleep(1000);
			}
			else
			{
				for(int i=0;i<5;i++)
				{
					std::cout<<p->name<<":"<<num<<endl;
					num++;
				}
				s=s%3+1;
				//cout<<p->name<<"s is"<<s<<endl;
				ReleaseMutex(mutex);
				//Sleep(100);
			}
			
		}
		return 1;
	}
protected:
private:
	string name;
	int id;
};
int main()
{
	int number=1;
	int s=1;
	mutex=CreateMutex(NULL,false,"print");
	unsigned int a[3]={0};
	ThreadTest *t1=new ThreadTest("�߳�1",1);
	ThreadTest *t2=new ThreadTest("�߳�2",2);
	ThreadTest *t3=new ThreadTest("�߳�3",3);
	HANDLE th1=(HANDLE)_beginthreadex(NULL,
		0,
		ThreadTest::theThreadFunction,
		t1,
		CREATE_SUSPENDED,
		&a[0]);
	HANDLE th2=(HANDLE)_beginthreadex(NULL,
		0,
		ThreadTest::theThreadFunction,
		t2,
		CREATE_SUSPENDED,
		&a[1]);
	HANDLE th3=(HANDLE)_beginthreadex(NULL,
		0,
		ThreadTest::theThreadFunction,
		t3,
		CREATE_SUSPENDED,
		&a[2]);
	ResumeThread(th1);
	ResumeThread(th2);
	ResumeThread(th3);
	WaitForSingleObject(th1,INFINITE);
	WaitForSingleObject(th2,INFINITE);
	WaitForSingleObject(th3,INFINITE);
	cout<<"the s is "<<s<<endl;
	cout<<"the thread id are:"<<a[0]<<","<<a[1]<<","<<a[2]<<"."<<endl;
	CloseHandle(mutex);
	cin>>a[1];
	//return 0;
}