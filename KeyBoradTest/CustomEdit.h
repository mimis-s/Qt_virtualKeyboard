#pragma once

#include <QWidget>
#include <QPlainTextEdit>
#include <QTableView>
#include <QLineEdit>
#include <QTextBrowser>
#include <QTextEdit>
class CustomEdit : public QWidget
{
	Q_OBJECT

public:

	enum EDITTYPE
	{
		NOTYPE,					//当前没有编辑框被选中
		QLINEEDIT,				//单行文本编辑(QLineEdit)
		QEXPANDINGLINEEDIT,		//表格中的编辑框
		QTEXTEDIT,				//多行文本框(QTextEdit)
		QPLAINTEXTEDIT,			//富文本框(QPlainTextEdit)
		QTEXTBROWSER			//文本浏览框(QTextBrowser)
	};

	CustomEdit(QWidget *parent);
	~CustomEdit();

	void insert(const QString &);				//插入字符串
	void backspace();							//回退字符

	void setCurrentEdit(QObject *pWatch);		//将当前的文本编辑框传进来
	QWidget* getCurrentEdit();					//获取当前编辑框

private:

	QLineEdit *m_pCurLineEdit;					// 当前焦点的单行文本框
	QTextEdit *m_pCurTextEdit;					// 当前焦点的多行文本框
	QPlainTextEdit *m_pCurPlain;				// 当前焦点的富文本框
	QTextBrowser *m_pCurBrowser;				// 当前焦点的文本浏览框
	QTableView *m_pCurTable;					// 当前焦点的表格(只能通过表格找到里面的编辑框)

	int m_EditType;								//当前编辑的控件类型
};
