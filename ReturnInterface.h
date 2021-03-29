#pragma once

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QAction>
#include "DTableWidget.h"
#include "DPageBtn.h"
#include "DLineEdit.h"
#include "DLabel.h"
#include "DLFUNC.h"
#include "comnQss.h"

class ReturnInterface : public QWidget
{
    Q_OBJECT

public:
    ReturnInterface(QWidget *parent = NULL);
    ~ReturnInterface();
    void ReturnMsg(SocketMsg msg);
    void ChangeBtnState(int);   //改变底下按钮的颜色
    void UpdateUserInfo();
    void SetTableData();
    bool IsReturn(QString booknum);        //书籍是否处于归还状态
    std::vector<Borrowinfo> GetBorrowinfoData();
    void SetReturnTime(QString booknum,unsigned long returntime);//归还操作后同步更改本地的缓存数据
    void DeleteBorrowVectorItem(QString borrownum);//删除本地保留的信息
    Borrowinfo GetBorrowinfoItem(QString borrownum);//通过借阅编号获取信息
    Bookinfo GetBookinfoItem(QString borrownum);//通过借阅编号获取书籍信息
private slots:
    void CheckBoxChange(int, int);
    void ViewDetail(QTableWidgetItem*); //双击item查看详情
    void OnReturnBtnClick();
    void OnSearchBtnClick();
    void OnMenuBtnClick();
    void OnSearchBooknumAct();
    void OnSearchBooknaemAct();
    void OnSearchCatagoryAct();
    void OnSearchAuthorAct();
private:
    void InitGui();
    void ReturnResult(SocketMsg msg,bool b);
    std::vector<Borrowinfo> m_borrowVector;//保留所有的借阅表的信息
    DTableWidget* m_tablewidget;
    QLabel* m_NameLb;
    QLabel* m_IDLb;
    DLabel* m_NameShowLb;
    DLabel* m_IDShowLb;
    QLabel* m_BottomLb;
    DPageBtn* m_ReturnBtn;
    DPageBtn* m_MenuBtn;
    DPageBtn* m_SearchBtn;
    QMenu *m_Menu;
    DLineEdit* m_SearchLed;
    std::vector<QString> m_CheckBookVector;//保留选中的书籍编号
    int m_itemCount;
    int  m_count;                //记录勾选的树有多少个
    bool m_bcont;               //是否能修改m_count
signals:
    void SigUserInfoUpdate();
};
