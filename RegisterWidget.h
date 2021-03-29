#pragma once
//在头文件前面加上下面几行代码
#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "DLineEdit.h"
#include "DPageBtn.h"
#include "DLFUNC.h"
class RegisterWidget : public QWidget
{
    Q_OBJECT

public:
    RegisterWidget(QWidget *parent = NULL);
    ~RegisterWidget();
private slots:
    void OnOkBtnClick();
    void OnCancelBtnClick();
signals:
    void SigLoginWidgetShow();
private:
    void InitGui();
    QLabel* m_UserNum;
    QLabel* m_UserName;
    QLabel* m_UserSex;
    QLabel* m_Telephone;
    QLabel* m_Department;
    QLabel* m_Speciality;
    QLabel* m_PassWord;
    QLabel* m_ConfirmPass;
    DLineEdit* m_UserNumLd;
    DLineEdit* m_UserNameLd;
    DLineEdit* m_PassWordLd;
    DLineEdit* m_ConfirmPassLd;
    DLineEdit* m_UserSexLd;
    DLineEdit* m_TelephoneLd;
    DLineEdit* m_DepartmentLd;
    DLineEdit* m_SpecialityLd;
    DPageBtn* m_Ok;
    DPageBtn* m_Cancel;
};
