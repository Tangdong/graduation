#pragma once

#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "DPageBtn.h"
#include "DLineEdit.h"
#include "DLFUNC.h"
#include "RegisterWidget.h"

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    LoginWidget(QWidget *parent = NULL);
    ~LoginWidget();
    void ChangeLoginStatus();
    void RegisterMsg(SocketMsg msg);
    bool LoginMsg(SocketMsg msg);
private slots:
    void OnLoginBtnClick();
    void OnRegisterBtnClick();
private:
    void InitGui();
    bool            m_login_status;                 //防止连续点击不断向服务器发送登陆请求 false可以发送请求，true不能发送请求
    DLineEdit          * m_nameEdt;
    QLabel             * m_nameLb;
    DLineEdit          * m_passEdt;
    QLabel             * m_passLb;
    DPageBtn         * m_login;                 //登陆按钮
    DPageBtn         * m_register;              //注册按钮
};
