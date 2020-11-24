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

	//ֻ֧�ִ����Զ�����������̣�Ҫ�뻻��������������Ե�CustomKeyBorad�����Touchbegin�޸�Ϊmousepressed
	CustomKeyBorad::Instance();
	connect(ui.btnPopup, SIGNAL(clicked()), this, SLOT(slotDlg_Base()));	//���Ե��������������̵ļ���
}

void KeyBoradTest::slotDlg_Base()
{
	Dlg_Base a(this);
	a.execDlg(true);
}