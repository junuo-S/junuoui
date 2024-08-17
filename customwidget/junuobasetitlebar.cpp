#include "stdafx.h"

#include "junuobasetitlebar.h"

#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QPixmap>

struct JunuoBaseTitleBar::Data
{
	void initUI(const QPixmap& logo, const QString& title)
	{
		q->setAttribute(Qt::WA_TranslucentBackground, true);
		hLayout = new QHBoxLayout(q);
		hLayout->setContentsMargins(DPI(8), 0, DPI(8), 0);
		q->setFixedHeight(DPI(32));
		logoLabel = new QLabel(q);
		logoLabel->setFixedSize(DPI_SIZE(24, 24));
		logoLabel->setScaledContents(true);
		logoLabel->setPixmap(logo);
		hLayout->addWidget(logoLabel);
		titleLabel = new QLabel(q);
		titleLabel->setText(title);
		titleLabel->setObjectName("titleLabel");
		hLayout->addWidget(titleLabel);
		hLayout->addStretch();
		minButton = new QPushButton(q);
		minButton->setIcon(QIcon(":/icon_svg/minimum.svg"));
		hLayout->addWidget(minButton);
		maxButton = new QPushButton(q);
		maxButton->setIcon(QIcon(":/icon_svg/maximum.svg"));
		hLayout->addWidget(maxButton);
		closeButton = new QPushButton(q);
		closeButton->setObjectName("closeButton");
		closeButton->setIcon(QIcon(":/icon_svg/close.svg"));
		hLayout->addWidget(closeButton);
	}

	JunuoBaseTitleBar* q = nullptr;
	QLabel* logoLabel = nullptr;
	QLabel* titleLabel = nullptr;
	QPushButton* minButton = nullptr;
	QPushButton* maxButton = nullptr;
	QPushButton* closeButton = nullptr;
	QHBoxLayout* hLayout = nullptr;
	QWidget* targetWidget = nullptr;
};

JunuoBaseTitleBar::JunuoBaseTitleBar(QWidget* parent /*= nullptr*/)
	: QWidget(parent)
	, data(new Data)
{
	data->q = this;
	data->initUI(QPixmap(":/icon_svg/app_logo_default.svg"), "This is title");
}

JunuoBaseTitleBar::JunuoBaseTitleBar(const QPixmap& logo, const QString& title, QWidget* parent /*= nullptr*/)
	: QWidget(parent)
	, data(new Data)
{
	data->q = this;
	data->initUI(logo, title);
}

JunuoBaseTitleBar::~JunuoBaseTitleBar()
{

}

void JunuoBaseTitleBar::setTargetWidget(QWidget* target)
{
	data->targetWidget = target;
}

void JunuoBaseTitleBar::setTitleIconSize(const QSize& size)
{
	data->logoLabel->setFixedSize(size);
}

void JunuoBaseTitleBar::mousePressEvent(QMouseEvent* event)
{

}

void JunuoBaseTitleBar::mouseReleaseEvent(QMouseEvent* event)
{

}

void JunuoBaseTitleBar::mouseMoveEvent(QMouseEvent* event)
{

}

void JunuoBaseTitleBar::mouseDoubleClickEvent(QMouseEvent* event)
{

}

void JunuoBaseTitleBar::showEvent(QShowEvent* event)
{
	if (data->targetWidget && data->targetWidget->isMaximized())
		data->maxButton->setIcon(QIcon(":/icon_svg/maximum_reset.svg"));
	else
		data->maxButton->setIcon(QIcon(":/icon_svg/maximum.svg"));
	if (data->targetWidget->minimumSize() == data->targetWidget->maximumSize())
		data->maxButton->hide();
	QWidget::showEvent(event);
}

void JunuoBaseTitleBar::paintEvent(QPaintEvent* event)
{
	QWidget::paintEvent(event);
}

void JunuoBaseTitleBar::onMinButtonClicked()
{

}

void JunuoBaseTitleBar::onMaxButtonClicked()
{

}

void JunuoBaseTitleBar::onCloseButtonClicked()
{

}

