#pragma once
struct Userinfo
{
    bool    admin;                      //是否管理员
    bool    reportloss;                //是否挂失
    int        borrownum;            //还能借阅数量
    QString usernum;                //账号
    QString password;               //密码
    QString username;               //名称
    QString sex;                          //性别
    QString telephone;               //电话
    QString department;            //院系
    QString speciality;                //专业
};

struct Bookinfo
{
    int totalinventory;               //在管数量
    int totalavailable;                //可借数量
    unsigned long entertime;
    QString booknum;              //书籍编号
    QString bookname;            //书籍名称
    QString author;                    //作者
    QString catagory;               //类别
    QString publisher;              //出版社
    QString dealpeople;           //添加操作人
};
struct Borrowinfo
{
    QString borrownum;            //借阅编号
    int renewalnum;                    //可续期次数
    unsigned long borrowtime;           //借阅时间
    unsigned long nowtime;
    unsigned long returntime;
    QString booknum;               //书籍编号
    QString usernum;                //用户编号
    QString expirydate;             //到期时间
};
enum btntype
{
    BUTTON_NONE,
    BUTTON_TEXT,        //只设置文字的按钮
    BUTTON_HOME,        //主页面的切换按钮
    BUTTON_ICON        //加载图片的按钮
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
    LOGIN,               //登录
    REGISTER,            //注册
    BORROW,              //借阅
    RETURN,              //归还
    INFORMATION,         //个人信息
    VIEWINFO,            //删除书籍
    SETTING,             //设置
    BOOKINFO,            //书籍管理
    SAVEBOOK,            //服务器发送过来，需要保留在本地的书籍信息
    ADDBOOK,             //添加书籍
    ADDBOOKITEM,         //添加book页面的书籍信息
    CHANGEPASSWORD,      //修改密码
    ERRORJSON,           //json数据包错误（在某个缓冲区）让服务器再发送消息，强制刷新
    MODIFYBOOK,          //修改书籍信息
    //DELETEBOOK           //删除书籍
};

struct SocketMsg
{
    int status;
    QString firstmsg;
    QString secondmsg;
    QString thirdmsg;
    QString fourthmsg;
};
