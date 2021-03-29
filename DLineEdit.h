#pragma once

#include <QtGui>
#include <QLineEdit>
class DLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    DLineEdit(QWidget *parent = NULL,bool edit = true);
    ~DLineEdit();
};
