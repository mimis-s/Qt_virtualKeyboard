#include "CustomKeyBorad.h"
#include "ui_CustomKeyBorad.h"
#include <./src/pinyinime.h>
#include <QFileInfo>
#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QScrollArea>
#include <QScrollBar>
#include <QScroller>
#include <QGridLayout>
#include <QSignalMapper>
#include <QDebug>
#include <QTextCursor>
#include <QGraphicsDropShadowEffect>

CustomKeyBorad *CustomKeyBorad::m_pSelf = nullptr;

CustomKeyBorad *CustomKeyBorad::Instance()
{
	if (!m_pSelf)
	{
		m_pSelf = new CustomKeyBorad;
	}
	return m_pSelf;
}

CustomKeyBorad::CustomKeyBorad(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::CustomKeyBorad();
	ui->setupUi(this);

	m_bBigCase = false;				//大小写判断(false为小写)
	m_bJudgeInputWay = ENGLISH;		//默认输入英文
	m_bMousePressed = false;		//默认鼠标没有按下
	m_MousePoint = QPoint();
	m_pCurEdit = new CustomEdit(this);

	InitMainWidget();
	InitWidgetKey();
	InitWidgetSymbol();
	InitKeyButtonConnect();
	qApp->installEventFilter(this);

}

CustomKeyBorad::~CustomKeyBorad()
{
	delete ui;
}

void CustomKeyBorad::InitMainWidget()
{
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool | Qt::WindowDoesNotAcceptFocus | Qt::Dialog);
	setAttribute(Qt::WA_AcceptTouchEvents);
	setAttribute(Qt::WA_TranslucentBackground);

	QLabel *pLable = new QLabel(this);

	//加阴影
	QGraphicsDropShadowEffect *pShadowEffect = new QGraphicsDropShadowEffect(pLable);
	pShadowEffect->setColor(QColor("gray"));
	pShadowEffect->setBlurRadius(15);
	pShadowEffect->setOffset(0, 0);
	pLable->setGraphicsEffect(pShadowEffect);
	pLable->graphicsEffect()->setEnabled(true);

	pLable->setGeometry(10, 10, this->width() - 20, this->height() - 20);
	pLable->setStyleSheet("background-color:rgba(30,30,30,220);");

	m_pInputChinese = new QLabel(pLable);
	m_pInputChinese->setMinimumSize(865, 14);
	m_pInputChinese->setMaximumSize(865, 14);
	m_pInputChinese->setStyleSheet("background-color:rgba(0,0,0,0);color:#fff;font-size:14px;");

	m_pPreview = new QTableWidget(pLable);
	m_pPreview->setMinimumSize(865, 30);
	m_pPreview->setMaximumSize(865, 30);

	m_pUnder = new QWidget(pLable);
	m_pUnder->setStyleSheet("background-color:rgba(0,0,0,0)");
	m_pUnder->setMaximumWidth(865);
	m_pUnder->setMinimumWidth(865);
	QVBoxLayout *vbox = new QVBoxLayout(pLable);
	vbox->addWidget(m_pInputChinese);
	vbox->addWidget(m_pPreview);
	vbox->addWidget(m_pUnder);
	vbox->setMargin(10);

	//加载中文库
	QFileInfo info("./dict_pinyin/dict_pinyin.dat");

	if (!ime_pinyin::im_open_decoder("./dict_pinyin/dict_pinyin.dat",
		"./user_dict.dat")) {
		qDebug("%s[%d] open pinyin dictionary failed", __func__, __LINE__);
		return;
	}
	//初始化汉字显示的表格
	m_pPreview->setShowGrid(false);
	m_pPreview->setSelectionMode(QAbstractItemView::SingleSelection);
	m_pPreview->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_pPreview->setFocusPolicy(Qt::NoFocus);
	m_pPreview->verticalHeader()->hide();
	m_pPreview->horizontalHeader()->hide();
	m_pPreview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_pPreview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_pPreview->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	m_pPreview->setStyleSheet("background-color:rgba(0,0,0,0);color:white;font-size:16px;border:none;");
	QScroller::grabGesture(m_pPreview, QScroller::LeftMouseButtonGesture);
	m_pPreview->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

	connect(m_pPreview, SIGNAL(cellClicked(int, int)), this, SLOT(slotChineseSelect(int, int)));


}

void CustomKeyBorad::InitWidgetKey()
{
	m_pKey = new QWidget(m_pUnder);
	QVBoxLayout *vbox = new QVBoxLayout(m_pKey);
	vbox->setMargin(0);
	QList<QString> SKeyText;

	SKeyText.push_back("qwertyuiop");
	SKeyText.push_back("asdfghjkl'");
	SKeyText.push_back("zxcvbnm,.?");

	//第一排
	QHBoxLayout *pOneHbox = new QHBoxLayout(m_pKey);
	for (int i = 0;i < SKeyText[0].size();i++)
	{
		KeyButton *pButton = new KeyButton(m_pKey);
		m_NameMapNumber[pButton] = LETTER;
		m_KetAll.push_back(pButton);
		m_KeyLetters.push_back(pButton);
		pButton->setText("" + SKeyText[0][i]);
		pButton->setMaximumSize(67, 55);
		pButton->setMinimumSize(67, 55);
		pOneHbox->addWidget(pButton);
	}
	//回退按钮
	KeyButton *pBackButton = new KeyButton(m_pKey);
	QString sNormal = "./KeyBoradImage/delete_white.png";
	QString sHover = "./KeyBoradImage/delete_black.png";
	pBackButton->setStyleImage(sNormal, sHover);
	m_NameMapNumber[pBackButton] = BACKSPACE;
	m_KetAll.push_back(pBackButton);
	pBackButton->setMaximumSize(140, 55);
	pBackButton->setMinimumSize(140, 55);
	pOneHbox->addWidget(pBackButton);

	//第二排
	QHBoxLayout *pTwoHbox = new QHBoxLayout(m_pKey);
	pTwoHbox->addStretch();
	for (int i = 0;i < SKeyText[1].size();i++)
	{
		KeyButton *pButton = new KeyButton(m_pKey);
		if (i == SKeyText[1].size() - 1)
			m_NameMapNumber[pButton] = SYMBOL;
		else
			m_NameMapNumber[pButton] = LETTER;
		m_KetAll.push_back(pButton);
		m_KeyLetters.push_back(pButton);
		pButton->setText("" + SKeyText[1][i]);
		pButton->setMaximumSize(67, 55);
		pButton->setMinimumSize(67, 55);
		pTwoHbox->addWidget(pButton);
	}
	//回车按钮
	KeyButton *pEnterButton = new KeyButton(m_pKey);
	sNormal = "./KeyBoradImage/enter_white.png";
	sHover = "./KeyBoradImage/enter_black.png";
	pEnterButton->setStyleImage(sNormal, sHover);
	m_NameMapNumber[pEnterButton] = ENTER;
	m_KetAll.push_back(pEnterButton);
	pEnterButton->setMaximumSize(100, 55);
	pEnterButton->setMinimumSize(100, 55);
	pTwoHbox->addWidget(pEnterButton);

	//第三排
	QHBoxLayout *pThreeHbox = new QHBoxLayout(m_pKey);
	//大写按钮
	KeyButton *pFBigButton = new KeyButton(m_pKey);
	sNormal = "./KeyBoradImage/upper_white.png";
	sHover = "./KeyBoradImage/upper_black.png";
	pFBigButton->setStyleImage(sNormal, sHover);
	m_NameMapNumber[pFBigButton] = CASE;
	m_KetAll.push_back(pFBigButton);
	pFBigButton->setMaximumSize(67, 55);
	pFBigButton->setMinimumSize(67, 55);
	pThreeHbox->addWidget(pFBigButton);
	for (int i = 0;i < SKeyText[2].size();i++)
	{
		KeyButton *pButton = new KeyButton(m_pKey);
		if (i >= SKeyText[2].size() - 3)
			m_NameMapNumber[pButton] = SYMBOL;
		else
			m_NameMapNumber[pButton] = LETTER;
		m_KetAll.push_back(pButton);
		m_KeyLetters.push_back(pButton);
		pButton->setText("" + SKeyText[2][i]);
		pButton->setMaximumSize(67, 55);
		pButton->setMinimumSize(67, 55);
		pThreeHbox->addWidget(pButton);
	}
	//大写按钮
	KeyButton *pSBigButton = new KeyButton(m_pKey);
	sNormal = "./KeyBoradImage/upper_white.png";
	sHover = "./KeyBoradImage/upper_black.png";
	pSBigButton->setStyleImage(sNormal, sHover);
	m_NameMapNumber[pSBigButton] = CASE;
	m_KetAll.push_back(pSBigButton);
	pSBigButton->setMaximumSize(67, 55);
	pSBigButton->setMinimumSize(67, 55);
	pThreeHbox->addWidget(pSBigButton);
	pThreeHbox->addStretch(0);

	//第四排
	QHBoxLayout *pFourHbox = new QHBoxLayout(m_pKey);
	KeyButton *pButtonNumber = new KeyButton(m_pKey);
	m_NameMapNumber[pButtonNumber] = SWITCHSYMBOL;
	m_KetAll.push_back(pButtonNumber);
	pButtonNumber->setMaximumSize(67, 55);
	pButtonNumber->setMinimumSize(67, 55);
	pButtonNumber->setText("&&123");
	pFourHbox->addWidget(pButtonNumber);

	KeyButton *pButtonCtrl = new KeyButton(m_pKey);
	m_KetAll.push_back(pButtonCtrl);
	pButtonCtrl->setMaximumSize(67, 55);
	pButtonCtrl->setMinimumSize(67, 55);
	pButtonCtrl->setText("Ctrl");
	pFourHbox->addWidget(pButtonCtrl);

	KeyButton *pButtonLanguage = new KeyButton(m_pKey);
	m_NameMapNumber[pButtonLanguage] = SWITCHLANGUAGE;
	m_KetAll.push_back(pButtonLanguage);
	pButtonLanguage->setMaximumSize(67, 55);
	pButtonLanguage->setMinimumSize(67, 55);
	pButtonLanguage->setText(QString::fromWCharArray(L"英"));
	pFourHbox->addWidget(pButtonLanguage);

	KeyButton *pButtonSpace = new KeyButton(m_pKey);
	m_NameMapNumber[pButtonSpace] = SPACE;
	m_KetAll.push_back(pButtonSpace);
	pButtonSpace->setMaximumSize(400, 55);
	pButtonSpace->setMinimumSize(400, 55);
	pButtonSpace->setText("Space");
	pFourHbox->addWidget(pButtonSpace);

	KeyButton *pButtonExpression = new KeyButton(m_pKey);
	m_KetAll.push_back(pButtonExpression);
	pButtonExpression->setMaximumSize(165, 55);
	pButtonExpression->setMinimumSize(165, 55);
	pButtonExpression->setText("maccura");
	pFourHbox->addWidget(pButtonExpression);

	//关闭按钮
	KeyButton *pButtonCancel = new KeyButton(m_pKey);
	sNormal = "./KeyBoradImage/close_white.png";
	sHover = "./KeyBoradImage/close_black.png";
	pButtonCancel->setStyleImage(sNormal, sHover);
	connect(pButtonCancel, SIGNAL(clicked()), this, SLOT(hide()));
	pButtonCancel->setMaximumSize(80, 55);
	pButtonCancel->setMinimumSize(80, 55);
	pFourHbox->addWidget(pButtonCancel);

	vbox->addLayout(pOneHbox);
	vbox->addLayout(pTwoHbox);
	vbox->addLayout(pThreeHbox);
	vbox->addLayout(pFourHbox);
}

void CustomKeyBorad::InitWidgetSymbol()
{
	m_pSymbol = new QWidget(m_pUnder);
	m_pSymbol->setMaximumWidth(m_pUnder->width());
	m_pSymbol->setMinimumWidth(m_pUnder->width());
	m_pSymbol->hide();

	QHBoxLayout *pHboxSymbol = new QHBoxLayout(m_pSymbol);
	pHboxSymbol->setMargin(0);
	//中英文符号全部保存在这儿
	QString sSymbol = QString::fromWCharArray(L"!@#$%()-_=+\;:\"*/<>[]{}|°~^！￥（）-_=+；：、“”…〈〉【】｛｝｜");
	//符号存储的界面类
	QScrollArea * pSymbolScrollArea = new QScrollArea(m_pSymbol);
	pSymbolScrollArea->setMaximumSize(480, 170);
	pSymbolScrollArea->setMinimumSize(480, 170);
	pSymbolScrollArea->setStyleSheet("QScrollArea{border:none;background:rgba(0,0,0,0);}");
	pSymbolScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	QScroller::grabGesture(pSymbolScrollArea, QScroller::LeftMouseButtonGesture);

	QPushButton *pWidgetSymbol = new QPushButton(m_pSymbol);
	pSymbolScrollArea->setWidget(pWidgetSymbol);
	pWidgetSymbol->setStyleSheet("background:rgba(0,0,0,0);");
	pWidgetSymbol->setGeometry(0, 0, 460, 490);
	int temp = sSymbol.size();
	int i = 0;
	int iX = 0, iY = 0;
	while (temp)
	{
		KeyButton *pButton = new KeyButton(pWidgetSymbol);
		m_NameMapNumber[pButton] = SYMBOL;
		m_KetAll.push_back(pButton);
		pButton->setText("" + sSymbol[sSymbol.size() - temp]);
		pButton->setGeometry(iX, iY, 67, 55);
		temp--;
		i++;
		if (i == 6)
			iY += 60, iX = 0, i = 0;
		else
			iX += 72;
	}

	//左边整体界面
	QVBoxLayout *pVboxLeft = new QVBoxLayout(m_pSymbol);
	pVboxLeft->addWidget(pSymbolScrollArea);
	//左下界面的按钮
	QHBoxLayout *pHboxLeftButton = new QHBoxLayout(m_pSymbol);
	KeyButton *pPinYinButton = new KeyButton(m_pSymbol);
	m_NameMapNumber[pPinYinButton] = SWITCHLETTER;
	m_KetAll.push_back(pPinYinButton);
	pPinYinButton->setMaximumSize(67, 55);
	pPinYinButton->setMinimumSize(67, 55);
	pPinYinButton->setText(QString::fromWCharArray(L"拼音"));
	KeyButton *pCtrlButton = new KeyButton(m_pSymbol);
	m_KetAll.push_back(pCtrlButton);
	pCtrlButton->setMaximumSize(67, 55);
	pCtrlButton->setMinimumSize(67, 55);
	pCtrlButton->setText(QString::fromWCharArray(L"Ctrl"));
	KeyButton *pSpaceButton = new KeyButton(m_pSymbol);
	m_NameMapNumber[pSpaceButton] = SPACE;
	m_KetAll.push_back(pSpaceButton);
	pSpaceButton->setMaximumSize(200, 55);
	pSpaceButton->setMinimumSize(200, 55);
	pSpaceButton->setText(QString::fromWCharArray(L"空格"));

	pHboxLeftButton->addWidget(pPinYinButton);
	pHboxLeftButton->addWidget(pCtrlButton);
	pHboxLeftButton->addWidget(pSpaceButton);
	pHboxLeftButton->addStretch(0);
	pVboxLeft->addLayout(pHboxLeftButton);
	pHboxSymbol->addLayout(pVboxLeft);

	pHboxSymbol->addStretch(0);
	//中间的数字键盘
	QVBoxLayout *pVboxNumber = new QVBoxLayout(m_pSymbol);
	QGridLayout *pGridLayoutNumber = new QGridLayout(m_pSymbol);
	for (int i = 0;i < 3;i++)
	{
		for (int j = 0;j < 3;j++)
		{
			KeyButton *pButton = new KeyButton(m_pSymbol);
			m_NameMapNumber[pButton] = NUMBER;
			m_KetAll.push_back(pButton);
			pButton->setMinimumSize(67, 55);
			pButton->setMaximumSize(67, 55);
			pButton->setText(QString::number(i * 3 + j + 1));
			pGridLayoutNumber->addWidget(pButton, i, j);
		}
	}
	QHBoxLayout *pHboxNumber = new QHBoxLayout(m_pSymbol);
	KeyButton *pZeroButton = new KeyButton(m_pSymbol);
	m_NameMapNumber[pZeroButton] = NUMBER;
	m_KetAll.push_back(pZeroButton);
	pZeroButton->setMinimumSize(140, 55);
	pZeroButton->setMaximumSize(140, 55);
	pZeroButton->setText("0");
	pHboxNumber->addWidget(pZeroButton);

	KeyButton *pPointButton = new KeyButton(m_pSymbol);
	m_NameMapNumber[pPointButton] = SYMBOL;
	m_KetAll.push_back(pPointButton);
	pPointButton->setMinimumSize(67, 55);
	pPointButton->setMaximumSize(67, 55);
	pPointButton->setText(".");
	pHboxNumber->addWidget(pPointButton);

	pVboxNumber->addLayout(pGridLayoutNumber);
	pVboxNumber->addLayout(pHboxNumber);

	pHboxSymbol->addLayout(pVboxNumber);
	pHboxSymbol->addStretch(0);

	//最右边的删除，回车和关闭按钮
	QVBoxLayout *pVboxRight = new QVBoxLayout(m_pSymbol);
	KeyButton *pButtonBack = new KeyButton(m_pSymbol);
	QString sNormal = "./KeyBoradImage/delete_white.png";
	QString sHover = "./KeyBoradImage/delete_black.png";
	pButtonBack->setStyleImage(sNormal, sHover);
	m_NameMapNumber[pButtonBack] = BACKSPACE;
	m_KetAll.push_back(pButtonBack);
	pButtonBack->setMinimumSize(67, 67);
	pButtonBack->setMaximumSize(67, 67);
	pVboxRight->addWidget(pButtonBack);

	KeyButton *pButtonEnter = new KeyButton(m_pSymbol);
	sNormal = "./KeyBoradImage/enter_white.png";
	sHover = "./KeyBoradImage/enter_black.png";
	pButtonEnter->setStyleImage(sNormal, sHover);
	m_NameMapNumber[pButtonEnter] = ENTER;
	m_KetAll.push_back(pButtonEnter);
	pButtonEnter->setMinimumSize(67, 100);
	pButtonEnter->setMaximumSize(67, 100);
	pVboxRight->addWidget(pButtonEnter);

	//关闭按钮
	KeyButton *pButtonCancel = new KeyButton(m_pSymbol);
	sNormal = "./KeyBoradImage/close_white.png";
	sHover = "./KeyBoradImage/close_black.png";
	pButtonCancel->setStyleImage(sNormal, sHover);
	connect(pButtonCancel, SIGNAL(clicked()), this, SLOT(hide()));
	pButtonCancel->setMaximumSize(67, 55);
	pButtonCancel->setMinimumSize(67, 55);
	pVboxRight->addWidget(pButtonCancel);

	pHboxSymbol->addLayout(pVboxRight);
}

void CustomKeyBorad::InitKeyButtonConnect()
{
	QSignalMapper *pSignalMapper = new QSignalMapper(this);
	for (int i = 0;i < m_KetAll.size();i++)
	{
		pSignalMapper->setMapping(m_KetAll[i], m_KetAll[i]);
		connect(m_KetAll[i], SIGNAL(clicked()), pSignalMapper, SLOT(map()));
	}
	connect(pSignalMapper, SIGNAL(mapped(QWidget*)), this, SLOT(slotKeyButtonClick(QWidget *)));
}

void CustomKeyBorad::UpdateCaseKey(QList<QString>LSCase)
{
	int temp = 0;
	for (int i = 0;i < LSCase.size();i++)
	{
		for (int j = 0;j < LSCase[i].size();j++)
		{
			m_KeyLetters[temp++]->setText("" + LSCase[i][j]);
		}
	}
}

void CustomKeyBorad::slotChineseSelect(int iR, int iC)
{
	if (m_pPreview->item(iR, iC))
	{
		m_pCurEdit->insert(m_pPreview->item(iR, iC)->text());
		m_CurrentString = "";
		SelectChinese(m_CurrentString);
		m_pPreview->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	}

}

void CustomKeyBorad::slotKeyButtonClick(QWidget *e)
{
	KeyButton *pButton = qobject_cast<KeyButton*>(e);
	switch (m_NameMapNumber[pButton])
	{
	case SWITCHSYMBOL:				//切换符号和数字键盘界面键
	{
		m_pSymbol->show();
		m_pKey->hide();
		break;
	}
	case SWITCHLETTER:				//切换为字母键盘界面键
	{
		m_pSymbol->hide();
		m_pKey->show();
		break;
	}
	case SYMBOL:					//符号键
	{
		if (m_CurrentString.size() > 0)
		{
			if (m_pPreview->currentItem()->text() != "")
			{
				m_pCurEdit->insert(m_pPreview->currentItem()->text());
				m_pCurEdit->insert(pButton->text());
			}
			m_CurrentString = "";
			SelectChinese(m_CurrentString);
			m_pPreview->setCurrentItem(NULL);
			m_pPreview->setAttribute(Qt::WA_TransparentForMouseEvents, true);
		}
		else
			m_pCurEdit->insert(pButton->text());
		break;
	}
	case NUMBER:					//数字键
	{
		m_pCurEdit->insert(pButton->text());
		break;
	}
	case SWITCHLANGUAGE:			//中英文切换键
	{
		if (pButton->text() == QString::fromWCharArray(L"英"))
			pButton->setText(QString::fromWCharArray(L"中"));
		else
		{
			if (m_CurrentString != "")
			{

				if (m_pPreview->currentItem()->text() != "")
					m_pCurEdit->insert(m_pPreview->currentItem()->text());
				m_CurrentString = "";
				SelectChinese(m_CurrentString);
				m_pPreview->setCurrentItem(NULL);
				m_pPreview->setAttribute(Qt::WA_TransparentForMouseEvents, true);
			}
			pButton->setText(QString::fromWCharArray(L"英"));

		}
		break;
	}
	case LETTER:					//字母键
	{
		for (auto it = m_NameMapNumber.begin();it != m_NameMapNumber.end();it++)
		{
			if (it.value() == SWITCHLANGUAGE)
			{
				if (it.key()->text() == QString::fromWCharArray(L"英"))
				{
					m_pCurEdit->insert(pButton->text());
				}
				if (it.key()->text() == QString::fromWCharArray(L"中"))
				{
					m_CurrentString += pButton->text();
					SelectChinese(m_CurrentString);
				}
			}
		}
		break;
	}
	case BACKSPACE:					//回格键
	{
		if (m_CurrentString.size() > 0)
		{
			m_CurrentString.chop(1);
			SelectChinese(m_CurrentString);
			if (m_CurrentString.size() == 0)
			{
				m_pPreview->setCurrentItem(NULL);
				m_pPreview->setAttribute(Qt::WA_TransparentForMouseEvents, true);
			}

		}
		else
		{
			m_pCurEdit->backspace();
		}
		break;
	}
	case SPACE:						//空格键
	{
		if (m_CurrentString.size() > 0)
		{
			if (m_pPreview->currentItem()->text() != "")
				m_pCurEdit->insert(m_pPreview->currentItem()->text());
			m_CurrentString = "";
			SelectChinese(m_CurrentString);
			m_pPreview->setCurrentItem(NULL);
			m_pPreview->setAttribute(Qt::WA_TransparentForMouseEvents, true);
		}
		else
			m_pCurEdit->insert(" ");
		break;
	}
	case CASE:						//大小写键
	{
		if (m_bBigCase)
		{
			QList<QString> SKeyText;
			SKeyText.push_back("qwertyuiop");
			SKeyText.push_back("asdfghjkl'");
			SKeyText.push_back("zxcvbnm,.?");
			UpdateCaseKey(SKeyText);
			m_bBigCase = false;
		}
		else
		{
			QList<QString> SKeyText;
			SKeyText.push_back("QWERTYUIOP");
			SKeyText.push_back("ASDFGHJKL'");
			SKeyText.push_back("ZXCVBNM,.?");
			UpdateCaseKey(SKeyText);
			m_bBigCase = true;
		}
		break;
	}
	case ENTER:						//回车键
	{
		if (m_CurrentString.size() > 0)
		{
			if (m_pPreview->currentItem()->text() != "")
				m_pCurEdit->insert(m_pPreview->currentItem()->text());
			m_CurrentString = "";
			SelectChinese(m_CurrentString);
			m_pPreview->setCurrentItem(NULL);
			m_pPreview->setAttribute(Qt::WA_TransparentForMouseEvents, true);
		}
		else
		{
			//如果是单行输入enter键就直接退出了
			QWidget * pWidget = m_pCurEdit->getCurrentEdit();
			if (pWidget)
			{
				if (!pWidget->inherits("QLineEdit") && !pWidget->inherits("QTableView"))
					m_pCurEdit->insert("\n");
			}
		}

		break;
	}
	default:
		break;
	}

}

bool  CustomKeyBorad::SelectChinese(const QString &arg)
{
	m_pInputChinese->setText(arg);
	if (arg == "")
	{
		m_pPreview->clear();
		return true;
	}
	if (arg[0] == 'u' || arg[0] == 'i' || arg[0] == 'v' || arg[0] == 'U' || arg[0] == 'I' || arg[0] == 'V')
	{
		m_pPreview->setRowCount(1);
		m_pPreview->setColumnCount(1);
		m_pPreview->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
		m_pPreview->setAttribute(Qt::WA_TransparentForMouseEvents, false);
		m_pPreview->setItem(0, 0, new QTableWidgetItem(arg));
		m_pPreview->item(0, 0)->setTextAlignment(Qt::AlignCenter);
		m_pPreview->setCurrentCell(0, 0);
		return true;
	}
	size_t qty = ime_pinyin::im_search(arg.toUtf8().data(), arg.size());
	ime_pinyin::char16 buf[256] = { 0 };
	QList<QString> msg;
	for (size_t i = 0; i < 100; ++i) {
		ime_pinyin::im_get_candidate(i, buf, 255);
		if (buf)
			msg.push_back(QString::fromUtf16(buf));
	}
	m_pPreview->setRowCount(1);
	m_pPreview->setColumnCount(msg.size());
	m_pPreview->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	m_pPreview->setAttribute(Qt::WA_TransparentForMouseEvents, false);
	for (int i = 0;i < msg.size();i++)
	{
		m_pPreview->setItem(0, i, new QTableWidgetItem(msg[i]));
		m_pPreview->item(0, i)->setTextAlignment(Qt::AlignCenter);
	}
	if (m_pPreview->currentItem() == nullptr)
		m_pPreview->setCurrentCell(0, 0);
	return true;
}

bool CustomKeyBorad::event(QEvent* event)
{
	if (event->type() == QEvent::MouseMove)
	{
		QMouseEvent* MEvent = (QMouseEvent*)(event);
		if (m_bMousePressed)
		{
			this->move(MEvent->globalPos() - m_MousePoint); // 软键盘拖动
		}
	}

	if (event->type() == QEvent::MouseButtonPress)
	{
		QMouseEvent * e = (QMouseEvent*)(event);

		m_bMousePressed = true;
		m_MousePoint = e->globalPos() - this->pos();
		e->accept();
	}

	if (event->type() == QEvent::MouseButtonRelease)
	{
		m_bMousePressed = false;
	}
	return QWidget::event(event);
}

bool CustomKeyBorad::eventFilter(QObject *watched, QEvent *event)
{
	if (watched->inherits("QWidget"))
	{
		QList<char *> list;
		list.push_back("QLineEdit");
		list.push_back("QTextEdit");
		list.push_back("QPlainTextEdit");
		list.push_back("QTextBrowser");
		list.push_back("QExpandingLineEdit");
		for (int i = 0;i < list.size();i++)
		{
			if (watched->inherits(list[i]))
			{
				QWidget *pWidget = (QWidget*)watched;
				pWidget->setAttribute(Qt::WA_AcceptTouchEvents);
				qApp->setAttribute(Qt::AA_SynthesizeMouseForUnhandledTouchEvents, false);

			}
		}
	}
	if (watched->inherits("QWidget"))
	{
		if (event->type() == QEvent::MouseButtonPress)	//换成mousepressed只能识别QLineEdit和表格的编辑框(QTextEdit相应的是滚动区域，不知道为啥)
		{
			bool bEdit = false;
			QList<char *> list;
			list.push_back("QLineEdit");
			list.push_back("QTextEdit");
			list.push_back("QPlainTextEdit");
			list.push_back("QTextBrowser");
			list.push_back("QExpandingLineEdit");
			for (int i = 0;i < list.size();i++)
			{
				QWidget *pWidget = (QWidget*)watched;
				if (pWidget->inherits(list[i]))
				{
					m_pCurEdit->setCurrentEdit(pWidget);
					setKeyBoradPosition(pWidget);
					show();
					break;
				}
			}
		}
		if (watched == m_pCurEdit->getCurrentEdit())
		{
			if (event->type() == QEvent::Close)
			{
				m_pCurEdit->setCurrentEdit(nullptr);
			}
			if (event->type() == QEvent::Hide)
			{
				m_pCurEdit->setCurrentEdit(nullptr);
			}
		}

	}
	return QWidget::eventFilter(watched, event);
}

void CustomKeyBorad::setKeyBoradPosition(QObject *pObject)
{
	QWidget *pWidget = (QWidget *)(pObject);
	QPoint point = pWidget->mapToGlobal(QPoint(0, 0));
	if (point.x() >= 400 && point.x() <= 1300 && point.y() >= 100 && point.y() <= 700)
	{
		this->move(pWidget->mapToGlobal(QPoint(pWidget->width() / 2 - this->width() / 2, pWidget->height())));
	}
	else
	{
		if (point.x()>1300)
			this->move(350, 350);
		else
			this->move(450, 350);
	}
}