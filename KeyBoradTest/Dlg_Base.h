#pragma once

#include <QWidget>
#include <QEventLoop>

namespace Ui { class Dlg_Base; };

class Dlg_Base : public QWidget
{
	Q_OBJECT

public:
	enum EM_BTNMSG
	{
		EM_OK,
		EM_CANCEL
	};
	Dlg_Base(QWidget *parent = Q_NULLPTR);
	~Dlg_Base();

	int execDlg(bool bCancelBtn = false);
	void showEvent(QShowEvent *event);
protected slots:
	void ConfirmSlot();
	void CancelSlot();

private:
	Ui::Dlg_Base *ui;

	QEventLoop m_loop;
};
