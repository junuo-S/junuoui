#pragma once

#ifndef JUNUOUI_EXPORT

#ifdef _JUNUOUI_MODULE_
#define JUNUOUI_EXPORT __declspec(dllexport)
#else
#define JUNUOUI_EXPORT __declspec(dllimport)
#endif // _JUNUOUI_MODULE_

#endif // JUNUOUI_EXPORT

class QLabel;

class JUNUOUI_EXPORT JunuoNormalLoadingWidget : public QWidget
{
	Q_OBJECT
public:
	explicit JunuoNormalLoadingWidget(QWidget *parent = nullptr);

protected:
	void showEvent(QShowEvent* event) override;
	void hideEvent(QHideEvent* event) override;

private:
	void initUI();
	void onTimeOut();
	void nextRotation();

	QLabel* m_pLoadingLabel;
	int m_nAngle = 0;
	QPixmap m_loadingPixmap;
	QTimer* m_pTimer = nullptr;
};
