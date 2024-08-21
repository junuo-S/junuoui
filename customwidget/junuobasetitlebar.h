#pragma once

#ifndef JUNUOUI_EXPORT

#ifdef _JUNUOUI_MODULE_
#define JUNUOUI_EXPORT __declspec(dllexport)
#else
#define JUNUOUI_EXPORT __declspec(dllimport)
#endif // _JUNUOUI_MODULE_

#endif // JUNUOUI_EXPORT

#include <QWidget>
#include <memory>

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
	bool isTargetWidgetHasFixedSize() const;
	struct Data;
	std::unique_ptr<Data> data;
};
