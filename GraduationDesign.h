#pragma once

//��ͷ�ļ�ǰ��������漸�д���
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
    void InitNetWork();                                     //��ʼ����������
    //����ÿ��ҳ���ָ�뷽�����
    BorrowInterface* GetBorrowInterface();
    ReturnInterface* GetReturnInterface();
    ModifyInterface* GetModifyInterface();
    ViewInformation* GetViewInformation();
    SettingInterface* GetSettingInterface();
    BookManagement* GetBookManagement();
    //ͨ���鼮��Ż�ȡ���������Ϣ
    Bookinfo GetSaveBook(QString booknum);
    //�����һ����Ҫ�������鼮
    void SetSaveBookinfo(Bookinfo book);
    //��ȡ�����ڱ��ص��鼮��Ϣ
    std::vector<Bookinfo> GetSaveBookVector();
    //ɾ��������������Ϊ���Ѿ��黹
    void DeleteBookinfoItem(QString booknum);
    //������Ҫ�������鼮��Ϣ
    void SaveBook(SocketMsg msg);
private slots:
    void UpdateUserInfo();                     //�����û������ݺ���
    void OnPageBtnClienk();                    //��ť�������Ӧ����
    void TestMessageBox();                     //���Ժ���
    void RecvSocketMsg();                       //�ͻ�����Ӧ����
    void DisConnect();                              //�������Ͽ�����
    void ErrorConnect();                              //���ӷ�����ʧ��
    void Connected();                              //���ӷ�����ʧ��
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
