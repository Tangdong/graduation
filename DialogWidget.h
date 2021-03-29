#pragma once

#include <QWidget>
#include "DDialog.h"

class DialogWidget : public QWidget
{
    Q_OBJECT

public:
    DialogWidget(DDialog *parent);
    ~DialogWidget();
    void SetShowLb(QString text,QString color = "rgb(0,0,0)");
private slots:
    void onCloseDlg();
    void onOkClicked();
private:
    DDialog *m_parent;
    QLabel *m_tiplb;
    QPushButton *m_okBtn;
};
