#pragma once

#include <QPushButton>
#include <QEvent>

class KeyButton : public QPushButton
{
	Q_OBJECT

public:
	KeyButton(QWidget *parent);
	~KeyButton();

	virtual bool event(QEvent* event);

	void setStyleImage(QString sNormalImage,QString sTouchImage);		//如果按钮有图片设置	

	//设置按钮样式
	void setTouchStyle();		//触摸
	void setNormalStyle();		//正常
	void setHoverStyle();		//覆盖

private:

	QString m_NormalImage;
	QString m_TouchImage;
};
