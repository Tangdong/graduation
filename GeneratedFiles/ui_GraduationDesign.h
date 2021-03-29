/********************************************************************************
** Form generated from reading UI file 'GraduationDesign.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRADUATIONDESIGN_H
#define UI_GRADUATIONDESIGN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GraduationDesignClass
{
public:

    void setupUi(QWidget *GraduationDesignClass)
    {
        if (GraduationDesignClass->objectName().isEmpty())
            GraduationDesignClass->setObjectName(QStringLiteral("GraduationDesignClass"));
        GraduationDesignClass->resize(600, 400);

        retranslateUi(GraduationDesignClass);

        QMetaObject::connectSlotsByName(GraduationDesignClass);
    } // setupUi

    void retranslateUi(QWidget *GraduationDesignClass)
    {
        GraduationDesignClass->setWindowTitle(QApplication::translate("GraduationDesignClass", "GraduationDesign", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GraduationDesignClass: public Ui_GraduationDesignClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRADUATIONDESIGN_H
