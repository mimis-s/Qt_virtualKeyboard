#include "KeyButton.h"
#include <QDebug>

KeyButton::KeyButton(QWidget *parent)
	: QPushButton(parent)
{
	setAttribute(Qt::WA_AcceptTouchEvents);
	this->setFocusPolicy(Qt::NoFocus);
	m_NormalImage = "";
	m_TouchImage = "";
	setNormalStyle();
}

KeyButton::~KeyButton()
{
}

bool KeyButton::event(QEvent* event)
{

	switch (event->type())
	{
	case QEvent::TouchBegin:
	{
		setTouchStyle();
		break;
	}
	case QEvent::TouchUpdate:
	{
		setHoverStyle();
		break;
	}
	case QEvent::TouchEnd:
	{
		setNormalStyle();
		break;
	}
	default:
		break;
	}
	if (event->type() == QEvent::MouseButtonRelease)
	{
		setNormalStyle();
	}
	if (event->type() == QEvent::HoverEnter)
	{
		setHoverStyle();
	}
	if (event->type() == QEvent::HoverLeave)
	{
		setNormalStyle();
	}
	return QPushButton::event(event);
}

void KeyButton::setNormalStyle()
{
	if (m_NormalImage != "")
	{
		this->setIcon(QIcon(m_NormalImage));
		this->setIconSize(QSize(30,20));
	}
	this->setStyleSheet("border:0px solid #a4a4a4;background-color:rgba(230,230,230,50);color:#fff;font-size:20px;font-weight:bold;");
}

void KeyButton::setTouchStyle()
{
	if (m_NormalImage != "")
	{
		this->setIcon(QIcon(m_NormalImage));
		this->setIconSize(QSize(30, 20));
	}
	this->setStyleSheet("border:0px solid #a4a4a4;background-color:#025bc7;color:#fff;font-size:20px;font-weight:bold;");
}

void KeyButton::setHoverStyle()
{
	if (m_TouchImage != "")
	{
		this->setIcon(QIcon(m_TouchImage));
		this->setIconSize(QSize(30, 20));
	}
	this->setStyleSheet("border:0px solid #a4a4a4;background-color:white;color:black;font-size:20px;font-weight:bold;");
}

void KeyButton::setStyleImage(QString sNormalImage, QString sTouchImage)
{
	m_NormalImage = sNormalImage;
	m_TouchImage = sTouchImage;
	setNormalStyle();
}