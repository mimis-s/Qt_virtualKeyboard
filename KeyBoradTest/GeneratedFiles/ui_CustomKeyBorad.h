/********************************************************************************
** Form generated from reading UI file 'CustomKeyBorad.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMKEYBORAD_H
#define UI_CUSTOMKEYBORAD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CustomKeyBorad
{
public:

    void setupUi(QWidget *CustomKeyBorad)
    {
        if (CustomKeyBorad->objectName().isEmpty())
            CustomKeyBorad->setObjectName(QStringLiteral("CustomKeyBorad"));
        CustomKeyBorad->resize(900, 335);

        retranslateUi(CustomKeyBorad);

        QMetaObject::connectSlotsByName(CustomKeyBorad);
    } // setupUi

    void retranslateUi(QWidget *CustomKeyBorad)
    {
        CustomKeyBorad->setWindowTitle(QApplication::translate("CustomKeyBorad", "CustomKeyBorad", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CustomKeyBorad: public Ui_CustomKeyBorad {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMKEYBORAD_H
