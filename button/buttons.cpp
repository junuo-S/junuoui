#include "stdafx.h"

#include "buttons.h"

#include <QPainter>

JunuoBaseButton::JunuoBaseButton(const QIcon& icon, const QString& text, QWidget* parent /*= nullptr*/)
	: QPushButton(icon, text, parent)
	, m_normalColor(0xffffff)
	, m_hoverColor(0xecf5ff)
	, m_clickColor(0xecf5ff)
	, m_disableColor(0xffffff)
	, m_textColor(0x6f7174)
{
	setCursor(Qt::PointingHandCursor);
}

JunuoBaseButton::JunuoBaseButton(const QString& text, QWidget* parent /*= nullptr*/)
	: QPushButton(text, parent)
	, m_normalColor(0xffffff)
	, m_hoverColor(0xecf5ff)
	, m_clickColor(0xecf5ff)
	, m_disableColor(0xffffff)
	, m_textColor(0x6f7174)
{
	setCursor(Qt::PointingHandCursor);
}

JunuoBaseButton::JunuoBaseButton(QWidget* parent /*= nullptr*/)
	: QPushButton(parent)
	, m_normalColor(0xffffff)
	, m_hoverColor(0xecf5ff)
	, m_clickColor(0xecf5ff)
	, m_disableColor(0xffffff)
	, m_textColor(0x6f7174)
{
	setCursor(Qt::PointingHandCursor);
}

void JunuoBaseButton::setBgColor(const QColor& normalColor, const QColor& hoverColor, const QColor& clickColor, const QColor& disableColor /*= QColor()*/)
{
	m_normalColor = normalColor;
	m_hoverColor = hoverColor;
	m_clickColor = clickColor;
	m_disableColor = disableColor.isValid() ? disableColor : normalColor;
}

void JunuoBaseButton::setNormalBgColor(const QColor& normalColor)
{
	m_normalColor = normalColor;
}

void JunuoBaseButton::setHoverBgColor(const QColor& hoverColor)
{
	m_hoverColor = hoverColor;
}

void JunuoBaseButton::setClickBgColor(const QColor& clickColor)
{
	m_clickColor = clickColor;
}

void JunuoBaseButton::setDisableBgColor(const QColor& disableColor)
{
	m_disableColor = disableColor;
}

void JunuoBaseButton::setTextColor(const QColor& textColor)
{
	m_textColor = textColor;
}

void JunuoBaseButton::setBorderColor(const QColor& borderColor)
{
	m_borderColor = borderColor;
}

void JunuoBaseButton::setBorderRadius(int borderRadius)
{
	m_borderRadius = borderRadius;
}

void JunuoBaseButton::setHasBorder(bool border)
{
	m_hasBorder = border;
}

void JunuoBaseButton::setLeftRightPadding(int leftRightPadding)
{
	m_leftRightPadding = leftRightPadding;
}

void JunuoBaseButton::setSpacing(int spacing)
{
	m_spacing = spacing;
}

void JunuoBaseButton::setIconPosition(IconPosition iconPosition)
{
	m_iconPosition = iconPosition;
}

QColor JunuoBaseButton::getNormalBgColor() const
{
	return m_normalColor;
}

QColor JunuoBaseButton::getHoverBgColor() const
{
	return m_hoverColor;
}

QColor JunuoBaseButton::getClickBgColor() const
{
	return m_clickColor;
}

QColor JunuoBaseButton::getDisableBgColor() const
{
	return m_disableColor;
}

QColor JunuoBaseButton::getTextColor() const
{
	return m_textColor;
}

QColor JunuoBaseButton::getBorderColor() const
{
	return m_borderColor;
}

int JunuoBaseButton::getBorderRadius() const
{
	return m_borderRadius;
}

bool JunuoBaseButton::hasBorder() const
{
	return m_hasBorder;
}

int JunuoBaseButton::getLeftRightPadding() const
{
	return m_leftRightPadding;
}

int JunuoBaseButton::getSpacing() const
{
	return m_spacing;
}

JunuoBaseButton::IconPosition JunuoBaseButton::getIconPosition() const
{
	return m_iconPosition;
}

void JunuoBaseButton::adjustBestSize()
{
	int textWidth = QFontMetrics(font()).width(text());
	bool hasIcon = !icon().isNull();
	setFixedSize(DPI(m_leftRightPadding) * 2 + textWidth + (hasIcon ? DPI(6) + iconSize().width() : 0), DPI(40));
}

void JunuoBaseButton::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	QRect rect = this->rect();
	bool isEnabled = this->isEnabled();
	QIcon::Mode currentState = isEnabled ? QIcon::Normal : QIcon::Disabled;
	if (isEnabled && isDown())
		currentState = QIcon::Selected;
	else if (isEnabled && underMouse())
		currentState = QIcon::Active;
	drawBackground(painter, rect, currentState);
	drawContent(painter, rect, currentState);
}

void JunuoBaseButton::drawBackground(QPainter& painter, const QRect& rect, QIcon::Mode currentState)
{
	painter.save();
	painter.setRenderHint(QPainter::Antialiasing);
	switch (currentState)
	{
	case QIcon::Normal:
		painter.setBrush(QBrush(m_normalColor));
		break;
	case QIcon::Disabled:
		painter.setBrush(QBrush(m_disableColor));
		break;
	case QIcon::Active:
		painter.setBrush(QBrush(m_hoverColor));
		break;
	case QIcon::Selected:
		painter.setBrush(QBrush(m_clickColor));
		break;
	default:
		painter.setBrush(QBrush(m_normalColor));
		break;
	}
	qreal radius = DPI(m_borderRadius);
	painter.setPen(m_hasBorder && m_borderColor.isValid() ? QPen(m_borderColor) : Qt::NoPen);
	painter.drawRoundedRect(rect, radius, radius);
	painter.restore();
}

void JunuoBaseButton::drawContent(QPainter& painter, const QRect& rect, QIcon::Mode currentState)
{
	painter.save();
	QIcon icon = this->icon();
	QString text = this->text();
	QSize iconSize = this->iconSize();
	QFont font = this->font();
	painter.setPen(QPen(m_textColor));
	int leftRightPadding = DPI(m_leftRightPadding);
	int textWidth = QFontMetrics(font).width(text);
	int textHeight = QFontMetrics(font).height();
	if (m_iconPosition == IconPosition::LeftOfText)
	{
		QRect textRect(0, 0, textWidth, textHeight);
		textRect.moveCenter(QPoint(rect.width() - leftRightPadding - textWidth / 2, rect.height() / 2));
		painter.drawText(textRect, Qt::AlignCenter, text);

		if (!icon.isNull())
		{
			QRect iconRect(QPoint(0, 0), iconSize);
			iconRect.moveCenter(QPoint(leftRightPadding + iconSize.width() / 2, rect.height() / 2));
			painter.drawPixmap(iconRect, icon.pixmap(iconSize));
		}
	}
	else if (m_iconPosition == IconPosition::RightOfText)
	{
		QRect textRect(0, 0, textWidth, textHeight);
		textRect.moveCenter(QPoint(leftRightPadding + textWidth / 2, rect.height() / 2));
		painter.drawText(textRect, Qt::AlignCenter, text);

		if (!icon.isNull())
		{
			QRect iconRect(QPoint(0, 0), iconSize);
			iconRect.moveCenter(QPoint(rect.width() - leftRightPadding - iconSize.width() / 2, rect.height() / 2));
			painter.drawPixmap(iconRect, icon.pixmap(iconSize));
		}
	}
	painter.restore();
}

