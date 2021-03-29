#include "DLineEdit.h"

DLineEdit::DLineEdit(QWidget *parent, bool edit)
    : QLineEdit(parent)
{
    setStyleSheet("background-color: rgb(0, 238, 0);border-radius:5px; ");
    if ( !edit )
    {
        setReadOnly(true);
    }
}

DLineEdit::~DLineEdit()
{
}
