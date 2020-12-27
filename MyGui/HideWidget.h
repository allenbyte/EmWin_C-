#ifndef _HIDEWIDGET_H_
#define _HIDEWIDGET_H_
#include "MWidget.h"

#define HIDEWIDGET_DEFAULT_SIZE_X										MWIDGET_DEFAULT_SIZE_W
#define	HIDEWIDGET_DEFAULT_SIZE_Y										MWIDGET_DEFAULT_SIZE_H
#define HIDEWIDGET_DEFAULT_HIDE_TIME									3000
#define HIDEWIDGET_DEFAULT_DRAW_TIME									1
#define HIDEWIDGET_DEFAULT_COLOR										GUI_ARGB_COLOR(0,255,0,0)

class MHideWidget : protected MWidget
{
public:
	MHideWidget(MWidget *Parent = 0, int x = 0, int y = 0, int xsize = HIDEWIDGET_DEFAULT_SIZE_X, int ysize = HIDEWIDGET_DEFAULT_SIZE_Y, int Flag = ConfigShow);
	~MHideWidget(void);
	void SetSize(int width, int high);
	void Hide(void);
	void Show(void);
	//slot
private:
	int width, height;
	int flag;
	int	DrawTimer;
	bool HideFlag;
	void HideTimerSlot(MWTimer *timer);
	void HideDrawTimerSlot(MWTimer *timer);
	void ShowDrawTimerSlot(MWTimer *timer);
	void Painter(GUI_RECT *pRect);
};

/*
展开时间到达后自动隐藏
失去焦点后隐藏
按下按钮处理完后隐藏
*/


#endif

