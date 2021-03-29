#pragma once

#include <QObject>

class DTreeWidget : public QObject
{
    Q_OBJECT

public:
    DTreeWidget(QObject *parent);
    ~DTreeWidget();
};
