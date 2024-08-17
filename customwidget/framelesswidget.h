#pragma once

#ifndef JUNUOUI_EXPORT

#ifdef _JUNUOUI_MODULE_
#define JUNUOUI_EXPORT __declspec(dllexport)
#else
#define JUNUOUI_EXPORT __declspec(dllimport)
#endif // _JUNUOUI_MODULE_

#endif // JUNUOUI_EXPORT

#include <QWidget>

class JunuoBaseTitleBar;

class JUNUOUI_EXPORT JunuoFrameLessWidget : public QWidget
{
	Q_OBJECT
public:
	JunuoFrameLessWidget(QWidget* parent = nullptr);
	~JunuoFrameLessWidget();
	void setMoveable(bool moveable);
	bool getMoveable() const;
	void setDragable(bool dragable);
	bool getDragable() const;
	void setPadding(size_t padding);
	size_t getPadding() const;
	void setTitleBar(JunuoBaseTitleBar* titleBar);
	void setMainWidget(QWidget* widget);

protected:
	void paintEvent(QPaintEvent* event) override;
	bool eventFilter(QObject* obj, QEvent* event) override;

private:
	void doMainWidgetMouseEvent(QMouseEvent* event);
	void doResize(QPoint delta);
	void onTimeOut();
	bool m_moveable = true;
	bool m_dragable = true;
	size_t m_padding = 0;
	QWidget* m_mainWidget = nullptr;
	QWidget* m_titleBar = nullptr;
	QPoint m_lastPos;
	QTimer* m_timer = nullptr;
	unsigned short m_containerIndex = -1;
};
