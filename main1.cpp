<<<<<<< HEAD
#include <windows.h>
#include <iostream>
#include <stdio.h>
using namespace std;
/** 孙鑫多线程买票
 *  HANDLE CreateEvent(LPSECURITY_ATTRIBUTES lpEventAttributes,BOOL bManualReset,BOOL bInitialState,LPCTSTR lpName);
 *  第一个参数表示安全控制，一般传入NULL
 *  第二个参数表示事件是手动设置还是自动设置，自动设置则对该事件调用WaitForSingleObject()
 *  后会自动调用ResetEvent()使事件变成未触发状态，true表示手动设置
 *  第三个参数表示初始时是由有信号，true表示有信号
 *  第四个参数表示事件的名称，传入NULL表示匿名事件
 *  重要：
 *          当人工重置的事件得到通知时，等待该事件的所有线程均变为可调度线程。
 *          当一个自动重置的事件得到通知时，等待该事件的线程中只有一个线程变为可调度线程。
 *  SetEvent(HANDLE handle):每次触发后，必有一个或多个处于等待状态下的线程变成可调度状态。,注意是“必有”
 */

DWORD WINAPI Fun1Proc(
  LPVOID lpParameter
);

DWORD WINAPI Fun2Proc(
  LPVOID lpParameter
);
DWORD WINAPI Fun3Proc(
  LPVOID lpParameter
);
HANDLE g_hEvent;
int tickets =10;

int main()
{


    HANDLE hThread1;
    HANDLE hThread2;
    HANDLE hThread3;

    hThread1 =CreateThread(NULL,0,Fun1Proc,NULL,0,NULL);
    hThread2 =CreateThread(NULL,0,Fun2Proc,NULL,0,NULL);
  //  hThread3 =CreateThread(NULL,0,Fun3Proc,NULL,0,NULL);

    //要实现同步的话，必须是自动置位，
    g_hEvent =CreateEvent(NULL,true,false,NULL);   //自动置位，无信号 自动动置位，
//    g_hEvent =CreateEvent(NULL,false,false,"Tickets");
//    if (g_hEvent)                                                  // 判断对象是否存在
//    {
//        if (ERROR_ALREADY_EXISTS == GetLastError())               // 当程序检测到当前的对象与你打开的实例对象相同的时候
//// 就会返回ERROR_ALREADY_EXISTS，如果接收到这个信息就说明你将
//// 打开一个已经打开的实例
//        {
//            cout << "不能打开一个实例!" << endl;
//            return 0;                                              // 直接返回，程序不往下执行
//        }
//
//    }
    SetEvent(g_hEvent);
    CloseHandle(hThread1);
    CloseHandle(hThread2);
    Sleep(3000);
    return 0;
}

DWORD WINAPI Fun1Proc(
  LPVOID lpParameter
)
{
    while(true)
    {
        WaitForSingleObject(g_hEvent,INFINITE);
        if(tickets>0)
        {
            printf("thread1 sleep\n");
            Sleep(50);                                  //睡眠时间要长才会出现交替现象。只能说sleep()时间越长，那么出现交替的概率越大
            //Sleep(1);
            printf("thread1 sell ticket: %d\n",tickets--);

        }
        else
            break;
        SetEvent(g_hEvent);


    }
    return 0;
}

DWORD WINAPI Fun2Proc(
  LPVOID lpParameter
)
{
    while(true)
    {
        WaitForSingleObject(g_hEvent,INFINITE);
        if(tickets>0)
        {
            printf("thread2 sleep \n");
            Sleep(50);
            //Sleep(1);
            printf("thread2 sell ticket: %d\n",tickets--);

        }
        else
            break;
         SetEvent(g_hEvent);

    }
=======
#include <iostream>
#include <string>
#include <map>
#include <stdio.h>
using namespace std;
typedef void* (*CreateFunction)(void);    //回调函数指针,指针函数，

/**
 *以下为工厂类，用来创建和注册类
 */
class ClassFactory
{
public:
    ClassFactory();
    ~ClassFactory();
    static void* GetClassByName(std::string name)
    {
        std::map<std::string,CreateFunction>::const_iterator pfind=m_clsMap.find(name);

        return (m_clsMap.end() == pfind) ? 0 : pfind->second();
    }
    static void RegisterClass(std::string name,CreateFunction method)
    {
        m_clsMap.insert(make_pair(name,method));
    }
protected:
private:
    static std::map<std::string,CreateFunction> m_clsMap;
};

map<string,CreateFunction> ClassFactory::m_clsMap;

class RegisterClass
{
public:
    RegisterClass(std::string name,CreateFunction method)
    {
        ClassFactory::RegisterClass(name,method);
    };

};

template <class T,const char name[]>
class Register
{
public:
     Register()
    {
         const RegisterClass tmp = rc;
    };
    static void* CreateInstance()
    {
        return new T;
    }
public:
    static const RegisterClass rc;


};

template<class T,const char name[]>
const RegisterClass Register<T,name>::rc(name,Register<T,name>::CreateInstance);
#define DEFINE_CLASS(class_name)\
char NameArray[]=#class_name;\
class class_name:public Register<class_name,NameArray>

#define DEFINE_CLASS_EX(class_name,father_class)\
char NameArray[]=#class_name;\
class class_name:public Register<class_name,NameArray>,public father_class

DEFINE_CLASS(CG)
{
public:
    void display()
    {
        printf("ff");
    }
};

int main()
{
    CG* tmp = (CG*)ClassFactory::GetClassByName("CG");
    tmp->display();

>>>>>>> 24cea4d52f94fa8ccf06cd2dd3a4b2136517ef4c

    return 0;
}

<<<<<<< HEAD
DWORD WINAPI Fun3Proc(
  LPVOID lpParameter
)
{
    while(true)
    {
        WaitForSingleObject(g_hEvent,INFINITE);
        if(tickets>0)
        {
            printf("thread3 sleep \n");
            Sleep(20);
            //Sleep(1);
            printf("thread3 sell ticket: %d\n",tickets--);
            SetEvent(g_hEvent);
        }
        else
            break;


    }

    return 0;
}
=======











































>>>>>>> 24cea4d52f94fa8ccf06cd2dd3a4b2136517ef4c
