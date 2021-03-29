#pragma once

#include <QLabel>

class DLabel : public QLabel
{
    Q_OBJECT

public:
    DLabel(QWidget *parent, QString strText = "");
    ~DLabel();
};
