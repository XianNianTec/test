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


    return 0;
}












































