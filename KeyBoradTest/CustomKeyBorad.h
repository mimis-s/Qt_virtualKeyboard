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
	//单例
	static CustomKeyBorad *Instance();

private:
	CustomKeyBorad(QWidget *parent = Q_NULLPTR);
	~CustomKeyBorad();


	//判断输入中文还是英文的枚举
	enum JUDGEINPUT
	{
		CHINESE,
		ENGLISH
	};
	//把不同的按键分组标记
	enum MAPBUTTON
	{
		ENTER = 1,			//回车键
		BACKSPACE,			//回格键
		SPACE,				//空格键
		CASE,				//大小写键
		SWITCHLANGUAGE,		//中英文切换键
		SWITCHSYMBOL,		//切换符号和数字键盘界面键
		SWITCHLETTER,		//切换为字母键盘界面键
		LETTER,				//字母键
		SYMBOL,				//符号键
		NUMBER,				//数字键
	};

public:

	//事件函数
	virtual bool event(QEvent* event);								//监视自身事件
	virtual bool eventFilter(QObject *watched, QEvent *event);		//监视其它界面事件

	bool SelectChinese(const QString &arg);							//查找中文库同时显示在界面上

	void setKeyBoradPosition(QObject *pObject);						//设置位置键盘位置

private:
	void InitMainWidget();				//初始化主界面
	void InitWidgetKey();				//初始化按键界面
	void InitWidgetSymbol();			//初始化符号界面
	void InitKeyButtonConnect();		//初始化所有按钮的信号和槽

	void UpdateCaseKey(QList<QString>LSCase);//更新大小写变化

public slots:
	void slotKeyButtonClick(QWidget *e);	//所有按钮公用一个槽函数
	void slotChineseSelect(int iR, int iC);	//选择表格中的中文输入到当前编辑框
private:
	Ui::CustomKeyBorad *ui;
	QWidget *m_pSymbol;					//符号界面
	QWidget *m_pKey;					//字母按键界面
	
	QTableWidget *m_pPreview;			//上面的预览汉字列表
	QLabel *m_pInputChinese;			//中文输入的东西

	QWidget *m_pUnder;					//下面界面
	QList<QPushButton*>m_KeyLetters;	//字母按钮列表
	QList<QPushButton*>m_KetAll;		//存储所有按钮列表

	QMap<QPushButton*, int>m_NameMapNumber;//把字母，数字，字符和一些按键分组标记

	bool m_bMousePressed;				//判断鼠标按下(用于拖动键盘)
	QPoint m_MousePoint;				//键盘的坐标
	//QLineEdit *m_pCurrentEdit;			//当前要输入的编辑框

	int m_bJudgeInputWay;				//判断输入方式(中文或者英文)
	QString m_CurrentString;			//当前的中文输入字符
	bool m_bBigCase;					//大小写判断(true为大写)

	static CustomKeyBorad *m_pSelf;		//自己的指针

	CustomEdit *m_pCurEdit;				//自定义当前编辑框类
};
