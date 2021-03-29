#pragma once

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "DTableWidget.h"
#include "DPageBtn.h"
#include "DLineEdit.h"
#include "DLabel.h"
#include "DDialog.h"
#include "ChangePasswd.h"
#include "DialogWidget.h"

class SettingInterface : public QWidget
{
    Q_OBJECT

public:
    SettingInterface(QWidget *parent = NULL);
    ~SettingInterface();
    void SettingMsg(SocketMsg msg);
private slots:
    void OnModifyPassBtnClick();
private:
    void ChangePasswordResult(SocketMsg msg);
    void InitGui();
    DPageBtn* m_ModifyPass;
};