#pragma once

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QDateTime>
#include "DTableWidget.h"
#include "DPageBtn.h"
#include "DLineEdit.h"
#include "DLabel.h"
#include "DLFUNC.h"
#include "ReturnInterface.h"

class BorrowInterface : public QWidget
{
    Q_OBJECT

public:
    BorrowInterface(QWidget *parent = NULL);
    ~BorrowInterface();
    //响应服务器的数据函数
    void BorrowMsg(SocketMsg msg);
    void UpdateUserInfo();
    //清楚所有选中的
    void ClearCheckItem();
private slots:
    void ViewDetail(QTableWidgetItem*); //双击item查看详情
    void CheckBoxChange(int, int);
    void ChangeBtnState(int);   //改变底下按钮的颜色
    void OnBorrowBtnClick();
    void OnSearchBtnClick();
    void OnScrollBarArriveBottom();
    void OnMenuBtnClick();
    void OnSearchBooknumAct();
    void OnSearchBooknaemAct();
    void OnSearchCatagoryAct();
    void OnSearchAuthorAct();
private:
    void InitGui();
    //借阅的diglog
    void BorrowRepeat(QString text);
    //借阅结果函数（通过服务器的返回来执行）
    void BorrowResult(SocketMsg msg,bool b = true);
    //不管是否失败改变checkbox选中状态
    int  ChangeCheckBoxState(QString booknum);
    DTableWidget *m_tablewidget;
    QLabel      *m_NameLb;
    QLabel      *m_IDLb;
    DLabel      *m_NameShowLb;
    DLabel      *m_IDShowLb;
    QLabel      *m_BottomLb;
    DPageBtn    *m_BorrowBtn;
    DPageBtn    *m_SearchBtn;
    DPageBtn    *m_MenuBtn;
    QMenu       *m_Menu;
    DLineEdit   *m_SearchLed;
    QString     m_sqlwhere;
    std::vector<QString> m_CheckBookVector;//保留选中的书籍编号
    int  m_count;                //记录勾选的树有多少个
    int m_bookcount;            //记录书籍一起弹出提示
    bool m_bcont;               //是否能修改m_count
    bool m_bSearch;
signals:
    void SigUserInfoUpdate();
};