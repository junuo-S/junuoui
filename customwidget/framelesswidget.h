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

protected:
	void paintEvent(QPaintEvent* event) override;

private:
	bool m_moveable = true;
	bool m_dragable = true;
	size_t m_padding = 0;
};
