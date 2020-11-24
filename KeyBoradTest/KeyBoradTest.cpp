#include "KeyBoradTest.h"
#include <./src/pinyinime.h>
#include <QFileInfo>
#include <QDebug>
#include <QDialog>
#include <QLineEdit>
#include "Dlg_Base.h"

KeyBoradTest::KeyBoradTest(QWidget *parent) :
	QWidget(parent)
{
	ui.setupUi(this);

	//只支持触屏自动弹出虚拟键盘，要想换成鼠标点击弹出可以到CustomKeyBorad里面把Touchbegin修改为mousepressed
	CustomKeyBorad::Instance();
	connect(ui.btnPopup, SIGNAL(clicked()), this, SLOT(slotDlg_Base()));	//测试弹出框对于虚拟键盘的兼容
}

void KeyBoradTest::slotDlg_Base()
{
	Dlg_Base a(this);
	a.execDlg(true);
}