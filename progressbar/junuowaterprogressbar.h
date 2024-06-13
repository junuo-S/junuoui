#pragma once

#ifndef JUNUOUI_EXPORT

#ifdef _JUNUOUI_MODULE_
#define JUNUOUI_EXPORT __declspec(dllexport)
#else
#define JUNUOUI_EXPORT __declspec(dllimport)
#endif // _JUNUOUI_MODULE_

#endif // JUNUOUI_EXPORT

#include <QWidget>
#include <QColor>

class QTimer;

class JUNUOUI_EXPORT JunuoWaterProgressBar : public QWidget
{
	Q_OBJECT
public:
	explicit JunuoWaterProgressBar(QWidget* parent = nullptr);

	int getValue() const;
	int getRadius() const;
	QColor getWaterColor() const;
	QColor getBgColor() const;
	int getMinimumValue() const;
	int getMaxmumValue() const;
	void startTimer();
	void stopTimer();
	void setValue(int value);
	void setMinimumValue(int minimumValue);
	void setMaxmumValue(int maxmumValue);
	void setRadius(int radius);
	void setWaterColor(QColor color);
	void setBgColor(QColor color);

protected:
	virtual void paintEvent(QPaintEvent* event) override;
	void drawWater(QPainter* painter);
	void drawText(QPainter* painter); 
	void drawBackground(QPainter* painter);

private:
	int m_value = 0;
	int m_minimumValue = 0;
	int m_maxmumValue = 100;
	int m_radius;
	int m_offset;
	QColor m_waterColor;
	QColor m_bgColor;
	QTimer* m_timer;
};
