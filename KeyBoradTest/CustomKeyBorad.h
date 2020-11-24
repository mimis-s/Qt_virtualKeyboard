#pragma once

#include <QtWidgets/QWidget>
#include <QEvent>
#include <QTableWidget>
#include "KeyButton.h"
#include <QLabel>
#include <QPoint>
#include "CustomEdit.h"
#include <QLineEdit>

namespace Ui { class CustomKeyBorad; };

class CustomKeyBorad : public QWidget
{
	Q_OBJECT

public:
	//����
	static CustomKeyBorad *Instance();

private:
	CustomKeyBorad(QWidget *parent = Q_NULLPTR);
	~CustomKeyBorad();


	//�ж��������Ļ���Ӣ�ĵ�ö��
	enum JUDGEINPUT
	{
		CHINESE,
		ENGLISH
	};
	//�Ѳ�ͬ�İ���������
	enum MAPBUTTON
	{
		ENTER = 1,			//�س���
		BACKSPACE,			//�ظ��
		SPACE,				//�ո��
		CASE,				//��Сд��
		SWITCHLANGUAGE,		//��Ӣ���л���
		SWITCHSYMBOL,		//�л����ź����ּ��̽����
		SWITCHLETTER,		//�л�Ϊ��ĸ���̽����
		LETTER,				//��ĸ��
		SYMBOL,				//���ż�
		NUMBER,				//���ּ�
	};

public:

	//�¼�����
	virtual bool event(QEvent* event);								//���������¼�
	virtual bool eventFilter(QObject *watched, QEvent *event);		//�������������¼�

	bool SelectChinese(const QString &arg);							//�������Ŀ�ͬʱ��ʾ�ڽ�����

	void setKeyBoradPosition(QObject *pObject);						//����λ�ü���λ��

private:
	void InitMainWidget();				//��ʼ��������
	void InitWidgetKey();				//��ʼ����������
	void InitWidgetSymbol();			//��ʼ�����Ž���
	void InitKeyButtonConnect();		//��ʼ�����а�ť���źźͲ�

	void UpdateCaseKey(QList<QString>LSCase);//���´�Сд�仯

public slots:
	void slotKeyButtonClick(QWidget *e);	//���а�ť����һ���ۺ���
	void slotChineseSelect(int iR, int iC);	//ѡ�����е��������뵽��ǰ�༭��
private:
	Ui::CustomKeyBorad *ui;
	QWidget *m_pSymbol;					//���Ž���
	QWidget *m_pKey;					//��ĸ��������
	
	QTableWidget *m_pPreview;			//�����Ԥ�������б�
	QLabel *m_pInputChinese;			//��������Ķ���

	QWidget *m_pUnder;					//�������
	QList<QPushButton*>m_KeyLetters;	//��ĸ��ť�б�
	QList<QPushButton*>m_KetAll;		//�洢���а�ť�б�

	QMap<QPushButton*, int>m_NameMapNumber;//����ĸ�����֣��ַ���һЩ����������

	bool m_bMousePressed;				//�ж���갴��(�����϶�����)
	QPoint m_MousePoint;				//���̵�����
	//QLineEdit *m_pCurrentEdit;			//��ǰҪ����ı༭��

	int m_bJudgeInputWay;				//�ж����뷽ʽ(���Ļ���Ӣ��)
	QString m_CurrentString;			//��ǰ�����������ַ�
	bool m_bBigCase;					//��Сд�ж�(trueΪ��д)

	static CustomKeyBorad *m_pSelf;		//�Լ���ָ��

	CustomEdit *m_pCurEdit;				//�Զ��嵱ǰ�༭����
};
