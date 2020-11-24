/********************************************************************************
** Form generated from reading UI file 'KeyBoradTest.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KEYBORADTEST_H
#define UI_KEYBORADTEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KeyBoradTestClass
{
public:
    QLineEdit *lineEdit;
    QTableWidget *tableWidget;
    QTextEdit *textEdit;
    QPlainTextEdit *plainTextEdit;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QTextBrowser *textBrowser;
    QLabel *label_4;
    QPushButton *btnPopup;

    void setupUi(QWidget *KeyBoradTestClass)
    {
        if (KeyBoradTestClass->objectName().isEmpty())
            KeyBoradTestClass->setObjectName(QStringLiteral("KeyBoradTestClass"));
        KeyBoradTestClass->resize(1249, 875);
        lineEdit = new QLineEdit(KeyBoradTestClass);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(110, 100, 382, 41));
        tableWidget = new QTableWidget(KeyBoradTestClass);
        if (tableWidget->columnCount() < 20)
            tableWidget->setColumnCount(20);
        if (tableWidget->rowCount() < 20)
            tableWidget->setRowCount(20);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(510, 90, 511, 211));
        tableWidget->setRowCount(20);
        tableWidget->setColumnCount(20);
        textEdit = new QTextEdit(KeyBoradTestClass);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(110, 180, 381, 141));
        textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        plainTextEdit = new QPlainTextEdit(KeyBoradTestClass);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(110, 370, 381, 171));
        label = new QLabel(KeyBoradTestClass);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(110, 71, 101, 21));
        label_2 = new QLabel(KeyBoradTestClass);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(110, 151, 91, 21));
        label_3 = new QLabel(KeyBoradTestClass);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(110, 340, 101, 21));
        textBrowser = new QTextBrowser(KeyBoradTestClass);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(580, 380, 381, 171));
        label_4 = new QLabel(KeyBoradTestClass);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(580, 331, 101, 31));
        btnPopup = new QPushButton(KeyBoradTestClass);
        btnPopup->setObjectName(QStringLiteral("btnPopup"));
        btnPopup->setGeometry(QRect(120, 630, 151, 61));

        retranslateUi(KeyBoradTestClass);

        QMetaObject::connectSlotsByName(KeyBoradTestClass);
    } // setupUi

    void retranslateUi(QWidget *KeyBoradTestClass)
    {
        KeyBoradTestClass->setWindowTitle(QApplication::translate("KeyBoradTestClass", "KeyBoradTest", Q_NULLPTR));
        label->setText(QApplication::translate("KeyBoradTestClass", "LineEdit", Q_NULLPTR));
        label_2->setText(QApplication::translate("KeyBoradTestClass", "TextEdit", Q_NULLPTR));
        label_3->setText(QApplication::translate("KeyBoradTestClass", "PlainTextEdit", Q_NULLPTR));
        label_4->setText(QApplication::translate("KeyBoradTestClass", "TextBrowser", Q_NULLPTR));
        btnPopup->setText(QApplication::translate("KeyBoradTestClass", "\345\274\271\347\252\227", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class KeyBoradTestClass: public Ui_KeyBoradTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KEYBORADTEST_H
