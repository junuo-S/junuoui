#include "stdafx.h"

#include "junuobasetitlebar.h"

#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QPixmap>
#include <QMouseEvent>

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
		JunuoBaseTitleBar::connect(minButton, &QPushButton::clicked, q, &JunuoBaseTitleBar::onMinButtonClicked);
		minButton->setIcon(QIcon(":/icon_svg/minimum.svg"));
		hLayout->addWidget(minButton);
		maxButton = new QPushButton(q);
		JunuoBaseTitleBar::connect(maxButton, &QPushButton::clicked, q, &JunuoBaseTitleBar::onMaxButtonClicked);
		maxButton->setIcon(QIcon(":/icon_svg/maximum.svg"));
		hLayout->addWidget(maxButton);
		closeButton = new QPushButton(q);
		JunuoBaseTitleBar::connect(closeButton, &QPushButton::clicked, q, &JunuoBaseTitleBar::onCloseButtonClicked);
		closeButton->setObjectName("closeButton");
		closeButton->setIcon(QIcon(":/icon_svg/close.svg"));
		hLayout->addWidget(closeButton);
	}

	// 控件
	JunuoBaseTitleBar* q = nullptr;
	QLabel* logoLabel = nullptr;
	QLabel* titleLabel = nullptr;
	QPushButton* minButton = nullptr;
	QPushButton* maxButton = nullptr;
	QPushButton* closeButton = nullptr;
	QHBoxLayout* hLayout = nullptr;
	QWidget* targetWidget = nullptr;

	// 窗口状态
	bool leftButtonDown = false;
	QPoint lastPos;
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
	if (event->button() == Qt::LeftButton && rect().adjusted(DPI(30), DPI(5), DPI(-30), 0).contains(event->pos()))
	{
		data->leftButtonDown = true;
		data->lastPos = event->pos();
	}
}

void JunuoBaseTitleBar::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		data->leftButtonDown = false;
	}
}

void JunuoBaseTitleBar::mouseMoveEvent(QMouseEvent* event)
{
	if (!data->targetWidget || !data->leftButtonDown)
		return;
	auto deltaPos = event->pos() - data->lastPos;
	data->targetWidget->move(data->targetWidget->pos() + deltaPos);
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
	QWidget::paintEvent(event);
}

void JunuoBaseTitleBar::resizeEvent(QResizeEvent* event)
{
	if (data->targetWidget)
	{
		if (data->targetWidget->isMaximized())
			data->maxButton->setIcon(QIcon(":/icon_svg/maximum_reset.svg"));
		else
			data->maxButton->setIcon(QIcon(":/icon_svg/maximum.svg"));
		if (isTargetWidgetHasFixedSize())
			data->maxButton->hide();
	}
}

void JunuoBaseTitleBar::onMinButtonClicked()
{
	if (data->targetWidget)
		data->targetWidget->showMinimized();
}

void JunuoBaseTitleBar::onMaxButtonClicked()
{
	if (!data->targetWidget)
		return;
	if (isTargetWidgetHasFixedSize())
		return;
	if (data->targetWidget->isMaximized())
		data->targetWidget->showNormal();
	else
		data->targetWidget->showMaximized();
}

void JunuoBaseTitleBar::onCloseButtonClicked()
{
	if (data->targetWidget)
		data->targetWidget->close();
}

bool JunuoBaseTitleBar::isTargetWidgetHasFixedSize() const
{
	if (data->targetWidget && data->targetWidget->minimumSize() == data->targetWidget->maximumSize())
		return true;
	return false;
}

