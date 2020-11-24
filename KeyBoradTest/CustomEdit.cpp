#include "CustomEdit.h"
#include <QAbstractItemModel>
#include <QKeyEvent>
#include <windows.h>
#include <QDebug>
CustomEdit::CustomEdit(QWidget *parent)
	: QWidget(parent)
{

}

CustomEdit::~CustomEdit()
{
}

void CustomEdit::setCurrentEdit(QObject *pWatch)
{
	m_pCurLineEdit = nullptr;
	m_pCurTextEdit = nullptr;
	m_pCurPlain = nullptr;
	m_pCurBrowser = nullptr;
	m_pCurTable = nullptr;
	m_EditType = NOTYPE;

	if (!pWatch)
		return;

	if (pWatch->inherits("QLineEdit"))
	{
		m_pCurLineEdit = (QLineEdit*)pWatch;
		m_EditType = QLINEEDIT;
	}
	if (pWatch->inherits("QTextEdit"))
	{
		m_pCurTextEdit = (QTextEdit *)pWatch;
		m_EditType = QTEXTEDIT;
	}
	if (pWatch->inherits("QPlainTextEdit"))
	{
		m_pCurPlain = (QPlainTextEdit *)pWatch;
		m_EditType = QPLAINTEXTEDIT;
	}
	if (pWatch->inherits("QTextBrowser"))
	{
		m_pCurBrowser = (QTextBrowser *)pWatch;
		m_EditType = QTEXTBROWSER;
	}
	if (pWatch->inherits("QTableView"))
	{
		m_pCurTable = (QTableView *)pWatch;
		m_EditType = QEXPANDINGLINEEDIT;
	}
}

void CustomEdit::insert(const QString &sInsertString)
{
	// 软键盘隐藏状态下，不能输入字符
	if (!isVisible())
	{
		return;
	}

	switch(m_EditType)
	{
	case QLINEEDIT:
	{
		if (!m_pCurLineEdit)
			return;
		if (m_pCurLineEdit->property("keyPressEvent").toBool() && !sInsertString.isEmpty())
		{
			// 接收键盘事件
			QKeyEvent* keyEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_0, Qt::NoModifier);
			m_pCurLineEdit->parent()->event(keyEvent);
		}

		if (m_pCurLineEdit->echoMode() != QLineEdit::Normal)
		{		

			QString strOldText = m_pCurLineEdit->text();
			int iCursorPos = m_pCurLineEdit->cursorPosition();

			if (iCursorPos < 0)
			{
				return;
			}
			strOldText.insert(iCursorPos, sInsertString);

			const QRegExpValidator *vali = dynamic_cast<const QRegExpValidator*>(m_pCurLineEdit->validator());
			if (vali)
			{
				QRegExp r = vali->regExp();
				if (!r.exactMatch(strOldText))
				{
					return;
				}
			}
		}
		m_pCurLineEdit->insert(sInsertString);
		break;
	}
	case QTEXTEDIT:
	{
		m_pCurTextEdit->insertPlainText(sInsertString);
		break;
	}
	case QPLAINTEXTEDIT:
	{
		m_pCurPlain->insertPlainText(sInsertString);
		break;
	}
	case QTEXTBROWSER:
	{
		m_pCurBrowser->insertPlainText(sInsertString);
		break;
	}
	case QEXPANDINGLINEEDIT:
	{
		if (m_pCurTable)
		{
			QAbstractItemModel *model = m_pCurTable->model();
			QModelIndex index = model->index(m_pCurTable->currentIndex().row(), m_pCurTable->currentIndex().column());
			QString str = model->data(index).toString();
			model->setData(index, str + sInsertString);
		}
		break;
	}
	default:
		break;
	}
}

void CustomEdit::backspace()
{
	keybd_event(VK_BACK, 0, 0, 0);
	keybd_event(VK_BACK, 0, 2, 0);
}

QWidget* CustomEdit::getCurrentEdit()
{
	switch (m_EditType)
	{
	case QLINEEDIT:				//单行文本编辑(QLineEdit)
	{
		return m_pCurLineEdit;
		break;
	}
	case QEXPANDINGLINEEDIT:	//表格中的编辑框
	{
		return m_pCurTable;
		break;
	}
	case QTEXTEDIT:				//多行文本框(QTextEdit)
	{
		return m_pCurTextEdit;
		break;
	}
	case QPLAINTEXTEDIT:		//富文本框(QPlainTextEdit)
	{
		return m_pCurPlain;
		break;
	}
	case QTEXTBROWSER:			//文本浏览框(QTextBrowser)
	{
		return m_pCurBrowser;
		break;
	}
	default:
		break;
	}
	return nullptr;
}