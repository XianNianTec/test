<<<<<<< HEAD
#include <windows.h>
#include <iostream>
#include <stdio.h>
using namespace std;
/** ���ζ��߳���Ʊ
 *  HANDLE CreateEvent(LPSECURITY_ATTRIBUTES lpEventAttributes,BOOL bManualReset,BOOL bInitialState,LPCTSTR lpName);
 *  ��һ��������ʾ��ȫ���ƣ�һ�㴫��NULL
 *  �ڶ���������ʾ�¼����ֶ����û����Զ����ã��Զ�������Ը��¼�����WaitForSingleObject()
 *  ����Զ�����ResetEvent()ʹ�¼����δ����״̬��true��ʾ�ֶ�����
 *  ������������ʾ��ʼʱ�������źţ�true��ʾ���ź�
 *  ���ĸ�������ʾ�¼������ƣ�����NULL��ʾ�����¼�
 *  ��Ҫ��
 *          ���˹����õ��¼��õ�֪ͨʱ���ȴ����¼��������߳̾���Ϊ�ɵ����̡߳�
 *          ��һ���Զ����õ��¼��õ�֪ͨʱ���ȴ����¼����߳���ֻ��һ���̱߳�Ϊ�ɵ����̡߳�
 *  SetEvent(HANDLE handle):ÿ�δ����󣬱���һ���������ڵȴ�״̬�µ��̱߳�ɿɵ���״̬��,ע���ǡ����С�
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

    //Ҫʵ��ͬ���Ļ����������Զ���λ��
    g_hEvent =CreateEvent(NULL,true,false,NULL);   //�Զ���λ�����ź� �Զ�����λ��
//    g_hEvent =CreateEvent(NULL,false,false,"Tickets");
//    if (g_hEvent)                                                  // �ж϶����Ƿ����
//    {
//        if (ERROR_ALREADY_EXISTS == GetLastError())               // �������⵽��ǰ�Ķ�������򿪵�ʵ��������ͬ��ʱ��
//// �ͻ᷵��ERROR_ALREADY_EXISTS��������յ������Ϣ��˵���㽫
//// ��һ���Ѿ��򿪵�ʵ��
//        {
//            cout << "���ܴ�һ��ʵ��!" << endl;
//            return 0;                                              // ֱ�ӷ��أ���������ִ��
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
            Sleep(50);                                  //˯��ʱ��Ҫ���Ż���ֽ�������ֻ��˵sleep()ʱ��Խ������ô���ֽ���ĸ���Խ��
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
typedef void* (*CreateFunction)(void);    //�ص�����ָ��,ָ�뺯����

/**
 *����Ϊ�����࣬����������ע����
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
