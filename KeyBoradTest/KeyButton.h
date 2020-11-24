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

	void setStyleImage(QString sNormalImage,QString sTouchImage);		//�����ť��ͼƬ����	

	//���ð�ť��ʽ
	void setTouchStyle();		//����
	void setNormalStyle();		//����
	void setHoverStyle();		//����

private:

	QString m_NormalImage;
	QString m_TouchImage;
};
