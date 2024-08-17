#include "stdafx.h"

#include "framelesswidget.h"

#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QVBoxLayout>
#include <QPainterPath>
#include <QMouseEvent>
#include <QTimer>
#include <QApplication>

#include "junuobasetitlebar.h"

JunuoFrameLessWidget::JunuoFrameLessWidget(QWidget* parent /*= nullptr*/)
	: QWidget(parent)
	, m_padding(DPI(2))
	, m_timer(new QTimer(this))
{
	setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
	this->setAttribute(Qt::WA_TranslucentBackground);
	m_timer->setInterval(100);
	connect(m_timer, &QTimer::timeout, this, &JunuoFrameLessWidget::onTimeOut);
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
	titleBar->setMouseTracking(true);
	titleBar->installEventFilter(this);
	m_titleBar = titleBar;
}

void JunuoFrameLessWidget::setMainWidget(QWidget* widget)
{
	m_mainWidget = widget;
	widget->setMouseTracking(true);
	widget->installEventFilter(this);
}

void JunuoFrameLessWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	for (int i = 0; i <= DPI(10); i++)
	{
		QRect rect = this->rect().adjusted(i, i, -i, -i);
		painter.setOpacity((float)i / DPI(10) / 13);
		painter.drawRoundedRect(rect, DPI(10), DPI(10));
	}
	painter.end();
	QWidget::paintEvent(event);
}

bool JunuoFrameLessWidget::eventFilter(QObject* obj, QEvent* event)
{
	if (obj == m_mainWidget || obj == m_titleBar)
		doMainWidgetMouseEvent(dynamic_cast<QMouseEvent*>(event));
	return QWidget::eventFilter(obj, event);
}

void JunuoFrameLessWidget::doMainWidgetMouseEvent(QMouseEvent* event)
{
	if (!event || hasFixedSize())
		return;
	auto mousePos = event->pos();
	const unsigned short cornersThreshold = DPI(6);
	const unsigned short edgesThreshold = 2;
	// 规划8个区域
	QVector<QRect> rectRegions = {
		QRect(0, 0, cornersThreshold, cornersThreshold),
		QRect(m_mainWidget->width() - cornersThreshold, 0, cornersThreshold, cornersThreshold),
		QRect(0, m_mainWidget->height() - cornersThreshold, cornersThreshold, cornersThreshold),
		QRect(m_mainWidget->width() - cornersThreshold, m_mainWidget->height() - cornersThreshold, cornersThreshold, cornersThreshold),
		QRect(0, cornersThreshold, edgesThreshold, m_mainWidget->height() - cornersThreshold * 2),
		QRect(cornersThreshold, 0, m_mainWidget->width() - cornersThreshold * 2, edgesThreshold),
		QRect(m_mainWidget->width() - edgesThreshold, cornersThreshold, edgesThreshold, m_mainWidget->height() - cornersThreshold * 2),
		QRect(cornersThreshold, m_mainWidget->height() - edgesThreshold, m_mainWidget->width() - cornersThreshold * 2, edgesThreshold)
	};
	m_containerIndex = -1;
	for (const auto& rect : rectRegions)
	{
		if (rect.contains(mousePos))
		{
			m_containerIndex = rectRegions.indexOf(rect);
			break;
		}
	}
	switch (m_containerIndex)
	{
	case 0:
	case 3:
		setCursor(Qt::SizeFDiagCursor);
		break;
	case 1:
	case 2:
		setCursor(Qt::SizeBDiagCursor);
		break;
	case 4:
	case 6:
		setCursor(Qt::SizeHorCursor);
		break;
	case 5:
	case 7:
		setCursor(Qt::SizeVerCursor);
		break;
	default:
		setCursor(Qt::ArrowCursor);
		break;
	}
	if (event->type() == QEvent::MouseButtonPress && event->button() == Qt::LeftButton && m_containerIndex != -1)
	{
		m_lastPos = event->globalPos();
		m_timer->start();
		m_mainWidget->removeEventFilter(this);
		m_titleBar->removeEventFilter(this);
	}
}

void JunuoFrameLessWidget::doResize(QPoint delta)
{
	if (m_containerIndex == -1)
		return;
	switch (m_containerIndex)
	{
	case 0:
		setGeometry(x() + delta.x(), y() + delta.y(), width() - delta.x(), height() - delta.y());
		break;
	case 1:
		setGeometry(x(), y() + delta.y(), width() + delta.x(), height() - delta.y());
		break;
	case 2:
		setGeometry(x() + delta.x(), y(), width() - delta.x(), height() + delta.y());
		break;
	case 3:
		setGeometry(x(), y(), width() + delta.x(), height() + delta.y());
		break;
	case 4:
		setGeometry(x() + delta.x(), y(), width() - delta.x(), height());
		break;
	case 5:
		setGeometry(x(), y() + delta.y(), width(), height() - delta.y());
		break;
	case 6:
		setGeometry(x(), y(), width() + delta.x(), height());
		break;
	case 7:
		setGeometry(x(), y(), width(), height() + delta.y());
		break;
	default:
		break;
	}
}

void JunuoFrameLessWidget::onTimeOut()
{
	if (m_containerIndex == -1 || !(qApp->mouseButtons() & Qt::LeftButton))
	{
		m_timer->stop();
		m_mainWidget->installEventFilter(this);
		m_titleBar->installEventFilter(this);
	}
	doResize(QCursor::pos() - m_lastPos);
	m_lastPos = QCursor::pos();
}

bool JunuoFrameLessWidget::hasFixedSize() const
{
	return minimumSize() == maximumSize();
}
