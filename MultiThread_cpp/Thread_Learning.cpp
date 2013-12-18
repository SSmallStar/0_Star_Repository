#include <Windows.h>
#include <iostream>
using namespace std;
HANDLE hMutex;
DWORD WINAPI Fun(LPVOID lpPara)
{
	int i=10;
	while(i>0)
	{
		//printf("the fun i:%d\n",i);
		WaitForSingleObject(hMutex,INFINITE);
		cout<<"the fun i:"<<i<<endl;
		//cerr<<"the fun i:"<<i<<endl;
		i--;
		//Sleep(10);
		ReleaseMutex(hMutex);
	}
	return 0;
}
int main1()
{
	char s[3][10]={"线程1","线程2","线程3"};
	int j=10;
	int state=1;
	HANDLE hThread=CreateThread(NULL,0,Fun,NULL,0,NULL);
	hMutex=CreateMutex(NULL,false,"screen");
	/*if(GetLastError()==Ex)*/
	char *s1=s[0];
	char a=state+'0';
	if(s1[2]==a)
		cout<<"bingo"<<endl;
	CloseHandle(hThread);
	while(j>0)
	{
		//printf("the main j:%d\n",j);
		WaitForSingleObject(hMutex,INFINITE);
		cout<<"the main j:"<<j<<endl;
		//cerr<<"the main j:"<<j<<endl;
		j--;
		
		//SwitchToThread();
		ReleaseMutex(hMutex);
		//Sleep(10);
		
	}
	cin>>j;
	return 0;
}