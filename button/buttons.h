#pragma once

#ifndef JUNUOUI_EXPORT

#ifdef _JUNUOUI_MODULE_
#define JUNUOUI_EXPORT __declspec(dllexport)
#else
#define JUNUOUI_EXPORT __declspec(dllimport)
#endif // _JUNUOUI_MODULE_

#endif // JUNUOUI_EXPORT

#include <QPushButton>

class JUNUOUI_EXPORT JunuoBaseButton : public QPushButton
{
	Q_OBJECT
public:
	enum IconPosition { LeftOfText, RightOfText };

	JunuoBaseButton(const QIcon& icon, const QString& text, QWidget* parent = nullptr);
	JunuoBaseButton(const QString& text, QWidget* parent = nullptr);
	JunuoBaseButton(QWidget* parent = nullptr);
	void setBgColor(const QColor& normalColor, const QColor& hoverColor, const QColor& clickColor, const QColor& disableColor = QColor());
	void setNormalBgColor(const QColor& normalColor);
	void setHoverBgColor(const QColor& hoverColor);
	void setClickBgColor(const QColor& clickColor);
	void setDisableBgColor(const QColor& disableColor);
	void setTextColor(const QColor& textColor);
	void setBorderRadius(int borderRadius);
	void setLeftRightPadding(int leftRightPadding);
	void setSpacing(int spacing);
	void setIconPosition(IconPosition iconPosition);
	QColor getNormalBgColor() const;
	QColor getHoverBgColor() const;
	QColor getClickBgColor() const;
	QColor getDisableBgColor() const;
	QColor getTextColor() const;
	int getBorderRadius() const;
	int getLeftRightPadding() const;
	int getSpacing() const;
	IconPosition getIconPosition() const;
	void adjustBestSize();

protected:
	void paintEvent(QPaintEvent* event) override;
	void drawBackground(QPainter& painter, const QRect& rect, QIcon::Mode currentState);
	void drawContent(QPainter& painter, const QRect& rect, QIcon::Mode currentState);

private:
	QColor m_normalColor;
	QColor m_hoverColor;
	QColor m_clickColor;
	QColor m_disableColor;
	QColor m_textColor;
	int m_borderRadius = 6;
	int m_leftRightPadding = 16;
	int m_spacing = 6;
	IconPosition m_iconPosition = LeftOfText;
};
