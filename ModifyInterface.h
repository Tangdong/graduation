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

class ModifyInterface : public QWidget
{
    Q_OBJECT

public:
    ModifyInterface(QWidget *parent = NULL);
    ~ModifyInterface();
    void ModifyMsg(SocketMsg msg);
    void SetInfomation();
private slots:
    void OnOkBtnClick();
    void OnModifyBtnClick();
private:
    void InitGui();
    QLabel* m_UserNum;
    QLabel* m_UserName;
    QLabel* m_UserSex;
    QLabel* m_Telephone;
    QLabel* m_Department;
    QLabel* m_Speciality;
    DLineEdit* m_UserNumLd;
    DLineEdit* m_UserNameLd;
    DLineEdit* m_UserSexLd;
    DLineEdit* m_TelephoneLd;
    DLineEdit* m_DepartmentLd;
    DLineEdit* m_SpecialityLd;
    DPageBtn * m_Modify;
    DPageBtn * m_Ok;
signals:
    void SigUserInfoUpdate();

};
