#pragma once

#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "DDialog.h"
#include "DLFUNC.h"


class ChangePasswd : public QWidget
{
    Q_OBJECT

public:
    ChangePasswd(DDialog *parent);
    ~ChangePasswd();
private slots:
    void onCloseDlg();
    void onCancelClicked();
    void onOkClicked();
    void onChangeLineEdit(const QString &);
private:
    QStringList m_SpecialCharlist;
    DDialog *m_parent;
    QLineEdit *m_oldpassedt;
    QLineEdit *m_passedt;
    QLineEdit *m_newpassedt;
    QLabel *m_tiplb;
    QLabel *m_oldpasslb;
    QLabel *m_passlb;
    QLabel *m_newpasslb;
    QPushButton *m_cancelBtn;
    QPushButton *m_okBtn;
};
