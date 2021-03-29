#include "DLabel.h"

DLabel::DLabel(QWidget *parent, QString strText )
    : QLabel(parent)
{
    if (!strText.isEmpty())
    {
        setText(strText);
    }
}

DLabel::~DLabel()
{
}
