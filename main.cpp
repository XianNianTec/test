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

    return 0;
}

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
