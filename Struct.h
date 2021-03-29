#pragma once
struct Userinfo
{
    bool    admin;                      //�Ƿ����Ա
    bool    reportloss;                //�Ƿ��ʧ
    int        borrownum;            //���ܽ�������
    QString usernum;                //�˺�
    QString password;               //����
    QString username;               //����
    QString sex;                          //�Ա�
    QString telephone;               //�绰
    QString department;            //Ժϵ
    QString speciality;                //רҵ
};

struct Bookinfo
{
    int totalinventory;               //�ڹ�����
    int totalavailable;                //�ɽ�����
    unsigned long entertime;
    QString booknum;              //�鼮���
    QString bookname;            //�鼮����
    QString author;                    //����
    QString catagory;               //���
    QString publisher;              //������
    QString dealpeople;           //��Ӳ�����
};
struct Borrowinfo
{
    QString borrownum;            //���ı��
    int renewalnum;                    //�����ڴ���
    unsigned long borrowtime;           //����ʱ��
    unsigned long nowtime;
    unsigned long returntime;
    QString booknum;               //�鼮���
    QString usernum;                //�û����
    QString expirydate;             //����ʱ��
};
enum btntype
{
    BUTTON_NONE,
    BUTTON_TEXT,        //ֻ�������ֵİ�ť
    BUTTON_HOME,        //��ҳ����л���ť
    BUTTON_ICON        //����ͼƬ�İ�ť
};

enum SearchType
{
    BOOKNUM,
    BOOKNAME,
    CATAGORY,
    AUTHOR,
    PUBLISHER
};
enum SocketService
{
    LOGIN,               //��¼
    REGISTER,            //ע��
    BORROW,              //����
    RETURN,              //�黹
    INFORMATION,         //������Ϣ
    VIEWINFO,            //ɾ���鼮
    SETTING,             //����
    BOOKINFO,            //�鼮����
    SAVEBOOK,            //���������͹�������Ҫ�����ڱ��ص��鼮��Ϣ
    ADDBOOK,             //����鼮
    ADDBOOKITEM,         //���bookҳ����鼮��Ϣ
    CHANGEPASSWORD,      //�޸�����
    ERRORJSON,           //json���ݰ�������ĳ�����������÷������ٷ�����Ϣ��ǿ��ˢ��
    MODIFYBOOK,          //�޸��鼮��Ϣ
    //DELETEBOOK           //ɾ���鼮
};

struct SocketMsg
{
    int status;
    QString firstmsg;
    QString secondmsg;
    QString thirdmsg;
    QString fourthmsg;
};
