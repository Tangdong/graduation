#pragma once

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "DTableWidget.h"
#include "DPageBtn.h"
#include "DLineEdit.h"
#include "DLabel.h"
#include "DLFUNC.h"


class ViewInformation : public QWidget
{
    Q_OBJECT

public:
    ViewInformation(QWidget *parent = NULL);
    ~ViewInformation();
    void ViewInfoMsg(SocketMsg msg);
    void UpdateUserInfo();
    void SetTableData();
private slots:
    void ViewDetail(QTableWidgetItem*); //双击item查看详情
    void CheckBoxChange(int, int);
    void ChangeBtnState(int);   //改变底下按钮的颜色
    void OnDeleteBtnClick();  
    void OnSearchBtnClick();
    void OnMenuBtnClick();
    void OnSearchBooknumAct();
    void OnSearchBooknaemAct();
    void OnSearchCatagoryAct();
    void OnSearchAuthorAct();
private:
    void InitGui();
    DTableWidget* m_tablewidget;
    QLabel* m_NameLb;
    QLabel* m_IDLb;
    DLabel* m_NameShowLb;
    DLabel* m_IDShowLb;
    QLabel* m_BottomLb;
    DPageBtn* m_DeleteBtn;
    DPageBtn* m_SearchBtn;
    DPageBtn* m_MenuBtn;
    QMenu *m_Menu;
    DLineEdit* m_SearchLed;
    std::vector<int> m_CheckBookVector;//保留选中的行号
    int  m_count;                //记录勾选的树有多少个
    bool m_bcont;               //是否能修改m_count
};
