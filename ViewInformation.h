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
    void ViewDetail(QTableWidgetItem*); //˫��item�鿴����
    void CheckBoxChange(int, int);
    void ChangeBtnState(int);   //�ı���°�ť����ɫ
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
    std::vector<int> m_CheckBookVector;//����ѡ�е��к�
    int  m_count;                //��¼��ѡ�����ж��ٸ�
    bool m_bcont;               //�Ƿ����޸�m_count
};
