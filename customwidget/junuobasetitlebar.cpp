#include "stdafx.h"

#include "junuobasetitlebar.h"

#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QStyle>
#include <QStyleOption>
#include <QPainter>

JunuoBaseTitleBar::JunuoBaseTitleBar(QWidget* parent /*= nullptr*/)
	: QWidget(parent)
{
	initUi(QPixmap(":/icon_svg/app_logo_default.svg"), "This is title");
}

JunuoBaseTitleBar::JunuoBaseTitleBar(const QPixmap& logo, const QString& title, QWidget* parent /*= nullptr*/)
	: QWidget(parent)
{
	initUi(logo, title);
}

JunuoBaseTitleBar::~JunuoBaseTitleBar()
{

}

void JunuoBaseTitleBar::setTargetWidget(QWidget* target)
{
	m_targetWidget = target;
}

void JunuoBaseTitleBar::setTitleIconSize(const QSize& size)
{
	m_logoLabel->setFixedSize(size);
}

void JunuoBaseTitleBar::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton && rect().adjusted(DPI(30), DPI(5), DPI(-30), 0).contains(event->pos()))
	{
		m_leftButtonDown = true;
		m_lastPos = event->pos();
	}
}

void JunuoBaseTitleBar::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_leftButtonDown = false;
	}
}

void JunuoBaseTitleBar::mouseMoveEvent(QMouseEvent* event)
{
	if (!m_targetWidget || !m_leftButtonDown)
		return;
	auto deltaPos = event->pos() - m_lastPos;
	m_targetWidget->move(m_targetWidget->pos() + deltaPos);
}

void JunuoBaseTitleBar::mouseDoubleClickEvent(QMouseEvent* event)
{
	onMaxButtonClicked();
}

void JunuoBaseTitleBar::showEvent(QShowEvent* event)
{
	QWidget::showEvent(event);
}

void JunuoBaseTitleBar::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	QStyleOption opt;
	opt.initFrom(this);
	QPainter painter(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void JunuoBaseTitleBar::resizeEvent(QResizeEvent* event)
{
	if (m_targetWidget)
	{
		if (m_targetWidget->isMaximized())
			m_maxButton->setIcon(QIcon(":/icon_svg/maximum_reset.svg"));
		else
			m_maxButton->setIcon(QIcon(":/icon_svg/maximum.svg"));
		if (isTargetWidgetHasFixedSize())
			m_maxButton->hide();
	}
}

void JunuoBaseTitleBar::onMinButtonClicked()
{
	if (m_targetWidget)
		m_targetWidget->showMinimized();
}

void JunuoBaseTitleBar::onMaxButtonClicked()
{
	if (!m_targetWidget)
		return;
	if (isTargetWidgetHasFixedSize())
		return;
	if (m_targetWidget->isMaximized())
		m_targetWidget->showNormal();
	else
		m_targetWidget->showMaximized();
}

void JunuoBaseTitleBar::onCloseButtonClicked()
{
	if (m_targetWidget)
		m_targetWidget->close();
}

bool JunuoBaseTitleBar::isTargetWidgetHasFixedSize() const
{
	if (m_targetWidget && m_targetWidget->minimumSize() == m_targetWidget->maximumSize())
		return true;
	return false;
}

void JunuoBaseTitleBar::initUi(const QPixmap& logo, const QString& title)
{
	setAttribute(Qt::WA_TranslucentBackground, true);
	m_hLayout = new QHBoxLayout(this);
	m_hLayout->setContentsMargins(DPI(8), 0, DPI(8), 0);
	setFixedHeight(DPI(32));

	m_logoLabel = new QLabel(this);
	m_logoLabel->setFixedSize(DPI_SIZE(24, 24));
	m_logoLabel->setScaledContents(true);
	m_logoLabel->setPixmap(logo);
	m_hLayout->addWidget(m_logoLabel);

	m_titleLabel = new QLabel(this);
	m_titleLabel->setText(title);
	m_titleLabel->setObjectName("titleLabel");
	m_hLayout->addWidget(m_titleLabel);
	m_hLayout->addStretch();

	m_minButton = new QPushButton(this);
	connect(m_minButton, &QPushButton::clicked, this, &JunuoBaseTitleBar::onMinButtonClicked);
	m_minButton->setIcon(QIcon(":/icon_svg/minimum.svg"));
	m_hLayout->addWidget(m_minButton);

	m_maxButton = new QPushButton(this);
	connect(m_maxButton, &QPushButton::clicked, this, &JunuoBaseTitleBar::onMaxButtonClicked);
	m_maxButton->setIcon(QIcon(":/icon_svg/maximum.svg"));
	m_hLayout->addWidget(m_maxButton);

	m_closeButton = new QPushButton(this);
	connect(m_closeButton, &QPushButton::clicked, this, &JunuoBaseTitleBar::onCloseButtonClicked);
	m_closeButton->setObjectName("closeButton");
	m_closeButton->setIcon(QIcon(":/icon_svg/close.svg"));
	m_hLayout->addWidget(m_closeButton);
}

