#pragma once

#include <QMessageBox>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "DPageBtn.h"

class DMessageBox : public QDialog
{
    Q_OBJECT

public:
    DMessageBox(int type = 0);
    ~DMessageBox();
protected:
    void paintEvent(QPaintEvent* event);
private slots:
    void OnOkBtnClienk();
    void OnCloseBtnClienk();
private:
    void showEvent(QShowEvent *event);
    bool m_btnShow;
    QLabel* m_Lable;
    DPageBtn* m_CloseBtn;
    DPageBtn* m_OkBtn;
    QString m_strTitleName;
    QString m_strText;
};
