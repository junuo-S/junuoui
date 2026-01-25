#include "stdafx.h"

#include "junuoloadingwidget.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QTimer>
#include <QPainter>

JunuoNormalLoadingWidget::JunuoNormalLoadingWidget(QWidget* parent /*= nullptr*/)
	: QWidget(parent)
	, m_pLoadingLabel(new QLabel(this))
	, m_loadingPixmap(":/icon_svg/loading-light.svg")
	, m_pTimer(new QTimer(this))
{
	initUI();
	m_pTimer->setInterval(16);
	connect(m_pTimer, &QTimer::timeout, this, &JunuoNormalLoadingWidget::onTimeOut);
}

void JunuoNormalLoadingWidget::showEvent(QShowEvent* event)
{
	if (m_pTimer && !m_pTimer->isActive())
	{
		m_pTimer->start();
	}
}

void JunuoNormalLoadingWidget::hideEvent(QHideEvent* event)
{
	if (m_pTimer)
		m_pTimer->stop();
}

void JunuoNormalLoadingWidget::initUI()
{
	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->setContentsMargins(0, 0, 0, 0);
	mainLayout->setAlignment(Qt::AlignHCenter);
	m_pLoadingLabel->setAlignment(Qt::AlignCenter);
	mainLayout->addWidget(m_pLoadingLabel);
}

void JunuoNormalLoadingWidget::onTimeOut()
{
	nextRotation();
}

void JunuoNormalLoadingWidget::nextRotation()
{
	if (!m_pLoadingLabel)
	{
		m_pTimer->stop();
		return;
	}
	const QSize size = DPI_SIZE(48, 48);
	m_nAngle = (m_nAngle + 6) % 360;
	QImage image(size, QImage::Format_ARGB32_Premultiplied);
	image.fill(Qt::transparent);
	QPainter painter(&image);
	painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	painter.setCompositionMode(QPainter::CompositionMode_Source);
	painter.translate(size.width() / 2, size.height() / 2);
	painter.rotate(m_nAngle);
	painter.translate(-size.width() / 2, -size.height() / 2);
	painter.drawPixmap(0, 0, m_loadingPixmap.scaled(size));
	painter.end();
	m_pLoadingLabel->setPixmap(QPixmap::fromImage(image));
}
