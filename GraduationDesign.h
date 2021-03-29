#pragma once

//在头文件前面加上下面几行代码
#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

#include <QtWidgets/QWidget>
#include "ui_GraduationDesign.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QStackedWidget>
#include <QTcpSocket>
#include <QJsonParseError>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>
#include <QFile>

#include "BorrowInterface.h"
#include "ReturnInterface.h"
#include "ModifyInterface.h"
#include "ViewInformation.h"
#include "SettingInterface.h"
#include "BookManagement.h"
#include "DMessageBox.h"
#include "LoginWidget.h"
#include "RegisterWidget.h"
#include "DLFUNC.h"


class GraduationDesign : public QWidget
{
	Q_OBJECT

public:
	GraduationDesign(QWidget *parent = Q_NULLPTR);
    void InitNetWork();                                     //初始化网络连接
    //返回每个页面的指针方便操作
    BorrowInterface* GetBorrowInterface();
    ReturnInterface* GetReturnInterface();
    ModifyInterface* GetModifyInterface();
    ViewInformation* GetViewInformation();
    SettingInterface* GetSettingInterface();
    BookManagement* GetBookManagement();
    //通过书籍标号获取整本书的信息
    Bookinfo GetSaveBook(QString booknum);
    //再添加一本需要保留的书籍
    void SetSaveBookinfo(Bookinfo book);
    //获取保留在本地的书籍信息
    std::vector<Bookinfo> GetSaveBookVector();
    //删除保留的数据因为其已经归还
    void DeleteBookinfoItem(QString booknum);
    //保留需要保留的书籍信息
    void SaveBook(SocketMsg msg);
private slots:
    void UpdateUserInfo();                     //更新用户的数据函数
    void OnPageBtnClienk();                    //按钮点击的响应函数
    void TestMessageBox();                     //测试函数
    void RecvSocketMsg();                       //客户端响应函数
    void DisConnect();                              //服务器断开连接
    void ErrorConnect();                              //连接服务器失败
    void Connected();                              //连接服务器失败
private:
    void InitGui();
	Ui::GraduationDesignClass ui;
    QStackedWidget     * m_stackwidget;
    DPageBtn* m_BorrowBtn;
    DPageBtn* m_ReturnBtn;
    DPageBtn* m_ModifyBtn;
    DPageBtn* m_ViewInfoBtn;
    DPageBtn* m_BookManageBtn;
    DPageBtn* m_SettingBtn;

    std::map<int, QWidget*> m_mapStackWgt;
    BorrowInterface* m_Borrow;
    ReturnInterface* m_Return;
    ModifyInterface* m_Modify;
    ViewInformation* m_ViewInfo;
    SettingInterface* m_Setting;
    BookManagement* m_BookManage;
    LoginWidget* m_Login;

    QTcpSocket* m_Socket;
    std::vector<Bookinfo> m_BookinfoVector;
    QString m_Errormsg;

    QFile *m_logfile;
};
