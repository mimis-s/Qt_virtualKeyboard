#include "Dlg_Base.h"
#include "ui_Dlg_Base.h"
#include <QLineEdit>
#include <QPushButton>
Dlg_Base::Dlg_Base(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::Dlg_Base();
	ui->setupUi(this);

	setWindowFlags(Qt::Dialog);
	setWindowModality(Qt::WindowModal);
	//setAttribute(Qt::WA_TranslucentBackground);
	QLineEdit *pLine = new QLineEdit(this);
	pLine->setGeometry(30, 30, 110, 40);
	QPushButton *pButton = new QPushButton(this);
	pButton->setGeometry(60, 60, 100, 38);
	connect(pButton, SIGNAL(clicked()), this, SLOT(CancelSlot()));

}

Dlg_Base::~Dlg_Base()
{
	delete ui;
}

int Dlg_Base::execDlg(bool bCancelBtn)
{
	Q_UNUSED(bCancelBtn);

	show();

	return m_loop.exec();
}

void Dlg_Base::ConfirmSlot()
{
	m_loop.exit(EM_OK);
	close();
}

void Dlg_Base::CancelSlot()
{
	m_loop.exit(EM_CANCEL);
	close();
}

void Dlg_Base::showEvent(QShowEvent *event)
{
	setAttribute(Qt::WA_Mapped);
	QWidget::showEvent(event);
}