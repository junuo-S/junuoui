#include "stdafx.h"

#include "framelesswidget.h"

#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QVBoxLayout>
#include <QPainterPath>

#include "junuobasetitlebar.h"

JunuoFrameLessWidget::JunuoFrameLessWidget(QWidget* parent /*= nullptr*/)
	: QWidget(parent)
	, m_padding(DPI(2))
{
	setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
	this->setAttribute(Qt::WA_TranslucentBackground);
	auto shadowEffect = new QGraphicsDropShadowEffect(this);
	shadowEffect->setOffset(0, 0);
	QColor shadowColor = QColor(0x757575);
	shadowColor.setAlphaF(0.37);
	shadowEffect->setColor(shadowColor);
	shadowEffect->setBlurRadius(DPI(32));
	this->setGraphicsEffect(shadowEffect);
}

JunuoFrameLessWidget::~JunuoFrameLessWidget()
{

}

void JunuoFrameLessWidget::setMoveable(bool moveable)
{
	m_moveable = moveable;
}

bool JunuoFrameLessWidget::getMoveable() const
{
	return m_moveable;
}

void JunuoFrameLessWidget::setDragable(bool dragable)
{
	m_dragable = dragable;
}

bool JunuoFrameLessWidget::getDragable() const
{
	return m_dragable;
}

void JunuoFrameLessWidget::setPadding(size_t padding)
{
	m_padding = padding;
}

size_t JunuoFrameLessWidget::getPadding() const
{
	return m_padding;
}

void JunuoFrameLessWidget::setTitleBar(JunuoBaseTitleBar* titleBar)
{
	titleBar->setTargetWidget(this);
}

void JunuoFrameLessWidget::paintEvent(QPaintEvent* event)
{
	QWidget::paintEvent(event);
}
