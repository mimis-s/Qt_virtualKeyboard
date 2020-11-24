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
		NOTYPE,					//��ǰû�б༭��ѡ��
		QLINEEDIT,				//�����ı��༭(QLineEdit)
		QEXPANDINGLINEEDIT,		//����еı༭��
		QTEXTEDIT,				//�����ı���(QTextEdit)
		QPLAINTEXTEDIT,			//���ı���(QPlainTextEdit)
		QTEXTBROWSER			//�ı������(QTextBrowser)
	};

	CustomEdit(QWidget *parent);
	~CustomEdit();

	void insert(const QString &);				//�����ַ���
	void backspace();							//�����ַ�

	void setCurrentEdit(QObject *pWatch);		//����ǰ���ı��༭�򴫽���
	QWidget* getCurrentEdit();					//��ȡ��ǰ�༭��

private:

	QLineEdit *m_pCurLineEdit;					// ��ǰ����ĵ����ı���
	QTextEdit *m_pCurTextEdit;					// ��ǰ����Ķ����ı���
	QPlainTextEdit *m_pCurPlain;				// ��ǰ����ĸ��ı���
	QTextBrowser *m_pCurBrowser;				// ��ǰ������ı������
	QTableView *m_pCurTable;					// ��ǰ����ı��(ֻ��ͨ������ҵ�����ı༭��)

	int m_EditType;								//��ǰ�༭�Ŀؼ�����
};
