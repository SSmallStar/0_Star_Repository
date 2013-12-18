#include <iostream>
#include <string>
#include <process.h>
#include <windows.h>
using namespace std;
/*在原来的1版本上改进，把线程封装成类，方便操作管理
主要的问题：
函数参数的引用传递可以直接用，但赋值给其他变量就不再与原来的变量绑定了，如：
int a(int &a){b=a;}对b的操作不再影响a
引用相关：
1)引用必须在声明时立即初始化，不允许空引用

2)引用一旦初始化，就不能再引用其它数据

3)引用和被引用的变量实际上代表同一个内存的数据

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
	ThreadTest *t1=new ThreadTest("线程1",1);
	ThreadTest *t2=new ThreadTest("线程2",2);
	ThreadTest *t3=new ThreadTest("线程3",3);
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