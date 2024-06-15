#include "junuoWaterProgressBar.h"

#include <QtMath>
#include <QTimer>
#include <QPainter>
#include <QPainterPath>

JunuoWaterProgressBar::JunuoWaterProgressBar(QWidget* parent)
	: QWidget(parent)
{
	m_timer = new QTimer(this);
	m_timer->setInterval(200);
	m_offset = 50;
	connect(m_timer, &QTimer::timeout, [=]() {
		m_offset += 10;
		if (m_offset == 100)
			m_offset = 50;
		update();
	});
}

int JunuoWaterProgressBar::getValue() const
{
	return m_value;
}

int JunuoWaterProgressBar::getRadius() const
{
	return m_radius;
}

QColor JunuoWaterProgressBar::getWaterColor() const
{
	return m_waterColor;
}

QColor JunuoWaterProgressBar::getBgColor() const
{
	return m_bgColor;
}

int JunuoWaterProgressBar::getMinimumValue() const
{
	return m_minimumValue;
}

int JunuoWaterProgressBar::getMaxmumValue() const
{
	return m_maxmumValue;
}

void JunuoWaterProgressBar::startTimer()
{
	m_timer->start();
}

void JunuoWaterProgressBar::stopTimer()
{
	m_timer->stop();
}

void JunuoWaterProgressBar::setValue(int value)
{
	m_value = value;
	repaint();
}

void JunuoWaterProgressBar::setMinimumValue(int minimumValue)
{
	m_minimumValue = minimumValue;
	repaint();
}

void JunuoWaterProgressBar::setMaxmumValue(int maxmumValue)
{
	m_maxmumValue = maxmumValue;
	repaint();
}

void JunuoWaterProgressBar::setRadius(int radius)
{
	m_radius = radius;
	repaint();
}

void JunuoWaterProgressBar::setWaterColor(QColor waterColor)
{
	m_waterColor = waterColor;
	repaint();
}

void JunuoWaterProgressBar::setBgColor(QColor color)
{
	m_bgColor = color;
	repaint();
}

void JunuoWaterProgressBar::paintEvent(QPaintEvent* event)
{
	int width = this->width();
	int height = this->height();
	int side = qMin(width, height);

	QPainter painter(this);
	painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
	painter.translate(width / 2, height / 2);
	painter.scale(side / 200.0, side / 200.0);

	drawBackground(&painter);
	drawWater(&painter);
	drawText(&painter);
	QWidget::paintEvent(event);
}

void JunuoWaterProgressBar::drawWater(QPainter* painter)
{
	double sinA = 2.5;
	double sinAlph = 0.1;
	QRect rect(-m_radius, -m_radius, 2 * m_radius, 2 * m_radius);
	int startX = -m_radius;
	int startY = -m_radius;
	int endX = m_radius;
	int endY = m_radius;
	float height = m_radius - ((m_value * m_radius) / (m_maxmumValue - m_minimumValue) * 2);

	QPainterPath waterPath1;
	waterPath1.moveTo(startX, endY);
	QPainterPath waterPath2;
	waterPath2.moveTo(startX, endY);

	for (int i = startX; i <= endX; i++)
	{
		float y1, y2;
		y1 = sinA * qSin(sinAlph * i + m_offset) + height;
		y2 = sinA * qSin(sinAlph * i + 60 + m_offset) + height;

		if (m_value == m_minimumValue)
			y1 = y2 = endY;
		if (m_value == m_maxmumValue)
			y1 = y2 = -endY;
		waterPath1.lineTo(i, y1);
		waterPath2.lineTo(i, y2);
	}
	waterPath1.lineTo(endX, endY);
	waterPath2.lineTo(endX, endY);

	QPainterPath bigPath;
	bigPath.addEllipse(rect);
	waterPath1 = bigPath.intersected(waterPath1);
	waterPath2 = bigPath.intersected(waterPath2);
	painter->save();
	painter->setPen(Qt::NoPen);
	m_waterColor.setAlpha(180);
	painter->setBrush(m_waterColor);
	painter->drawPath(waterPath2);
	m_waterColor.setAlpha(100);
	painter->setBrush(m_waterColor);
	painter->drawPath(waterPath1);
	painter->restore();
}

void JunuoWaterProgressBar::drawText(QPainter* painter)
{
	painter->save();
	QString text = QString("%1%").arg(int(m_value / double(m_maxmumValue - m_minimumValue) * 100));
	QFont font = painter->font();
	font.setPixelSize(30);
	painter->setFont(font);
	QPen pen = painter->pen();
	pen.setColor(Qt::white);
	pen.setWidth(4);
	painter->setPen(pen);
	QRect rect(-m_radius, -m_radius, m_radius * 2, m_radius * 2);
	painter->drawText(rect, Qt::AlignCenter, text);
	painter->restore();
}

void JunuoWaterProgressBar::drawBackground(QPainter* painter)
{
	painter->save();
	painter->setPen(Qt::NoPen);
	painter->setBrush(QColor(m_bgColor));
	QRect rect(-m_radius, -m_radius, m_radius * 2, m_radius * 2);
	painter->drawEllipse(rect);
	painter->restore();
}
