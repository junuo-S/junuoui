#pragma once

#ifndef JUNUOUI_EXPORT

#ifdef _JUNUOUI_MODULE_
#define JUNUOUI_EXPORT __declspec(dllexport)
#else
#define JUNUOUI_EXPORT __declspec(dllimport)
#endif // _JUNUOUI_MODULE_

#endif // JUNUOUI_EXPORT

#include <QPoint>

class QLabel;
class QPushButton;
class QHBoxLayout;
class QWidget;
class QPixmap;
class QString;
class QSize;
class QMouseEvent;
class QShowEvent;
class QPaintEvent;
class QResizeEvent;

class JUNUOUI_EXPORT JunuoBaseTitleBar : public QWidget
{
	Q_OBJECT
public:
	JunuoBaseTitleBar(QWidget* parent = nullptr);
	JunuoBaseTitleBar(const QPixmap& logo, const QString& title, QWidget* parent = nullptr);
	virtual ~JunuoBaseTitleBar();
	void setTargetWidget(QWidget* target);
	void setTitleIconSize(const QSize& size);

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseDoubleClickEvent(QMouseEvent* event) override;
	void showEvent(QShowEvent* event) override;
	void paintEvent(QPaintEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;
	virtual void onMinButtonClicked();
	virtual void onMaxButtonClicked();
	virtual void onCloseButtonClicked();

private:
	void initUi(const QPixmap& logo, const QString& title);
	bool isTargetWidgetHasFixedSize() const;

	QLabel *m_logoLabel = nullptr;
	QLabel *m_titleLabel = nullptr;
	QPushButton *m_minButton = nullptr;
	QPushButton *m_maxButton = nullptr;
	QPushButton *m_closeButton = nullptr;
	QHBoxLayout *m_hLayout = nullptr;
	QWidget *m_targetWidget = nullptr;

	bool m_leftButtonDown = false;
	QPoint m_lastPos;
};
