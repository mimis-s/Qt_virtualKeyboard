#pragma once

#include <QtWidgets/QWidget>
#include "ui_KeyBoradTest.h"
#include "CustomKeyBorad.h"

class KeyBoradTest : public QWidget
{
	Q_OBJECT

public:
	KeyBoradTest(QWidget *parent = Q_NULLPTR);
private slots:
	void slotDlg_Base();
private:
	Ui::KeyBoradTestClass ui;
};
