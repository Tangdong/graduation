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
    bool            m_login_status;                 //��ֹ���������������������͵�½���� false���Է�������true���ܷ�������
    DLineEdit          * m_nameEdt;
    QLabel             * m_nameLb;
    DLineEdit          * m_passEdt;
    QLabel             * m_passLb;
    DPageBtn         * m_login;                 //��½��ť
    DPageBtn         * m_register;              //ע�ᰴť
};
