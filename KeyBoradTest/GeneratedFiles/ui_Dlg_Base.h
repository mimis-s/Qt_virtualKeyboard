/********************************************************************************
** Form generated from reading UI file 'Dlg_Base.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLG_BASE_H
#define UI_DLG_BASE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dlg_Base
{
public:

    void setupUi(QWidget *Dlg_Base)
    {
        if (Dlg_Base->objectName().isEmpty())
            Dlg_Base->setObjectName(QStringLiteral("Dlg_Base"));
        Dlg_Base->resize(400, 300);

        retranslateUi(Dlg_Base);

        QMetaObject::connectSlotsByName(Dlg_Base);
    } // setupUi

    void retranslateUi(QWidget *Dlg_Base)
    {
        Dlg_Base->setWindowTitle(QApplication::translate("Dlg_Base", "Dlg_Base", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Dlg_Base: public Ui_Dlg_Base {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLG_BASE_H
