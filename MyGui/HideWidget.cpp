#include "HideWidget.h"
#include "MWTimer.h"
MHideWidget::MHideWidget(MWidget *Parent, int x, int y, int xsize, int ysize, int Flag)
:MWidget(Parent, xsize, ysize, x, y, 0, Flag),
width(xsize),
height(ysize),
DrawTimer(0),
HideFlag(false)
{
	MWTimer *HideTimer;
	SetHasTrans();
	HideTimer = newTimer(HIDEWIDGET_DEFAULT_HIDE_TIME);
	Connect(HideTimer, TimerEvent, this, &MHideWidget::HideTimerSlot);
}

void MHideWidget::HideTimerSlot(MWTimer *timer)
{
	if (HideFlag == false)
		Hide();
	else
		Show();
	DeleteTimer(timer);
}
void MHideWidget::HideDrawTimerSlot(MWTimer *timer)
{
	if (flag--)
		Move(-1, 0),
		timer->Restart(HIDEWIDGET_DEFAULT_DRAW_TIME);
	else
	{
		/*MWTimer *HideTimer;
		HideTimer = newTimer(HIDEWIDGET_DEFAULT_HIDE_TIME);
		Connect(HideTimer, TimerEvent, this, &MHideWidget::HideTimerSlot);*/
		DeleteTimer(timer);
	}
}
void MHideWidget::ShowDrawTimerSlot(MWTimer *timer)
{
	if (flag--)
		Move(+1, 0),
		timer->Restart(HIDEWIDGET_DEFAULT_DRAW_TIME);
	else
	{
		MWTimer *HideTimer;
		HideTimer = newTimer(HIDEWIDGET_DEFAULT_HIDE_TIME);
		Connect(HideTimer, TimerEvent, this, &MHideWidget::HideTimerSlot);
		DeleteTimer(timer);
	}
}
void MHideWidget::Painter(GUI_RECT *pRect)
{
	GUI_RECT Rect = (*pRect);
	GUI_SetBkColor(HIDEWIDGET_DEFAULT_COLOR);
	Rect.x0 -= GetWindowOrgX();
	Rect.y0 -= GetWindowOrgY();
	Rect.x1 -= pRect->x0;
	Rect.y1 -= pRect->y0; 
	GUI_ClearRectEx(pRect);
}
void MHideWidget::SetSize(int Width, int High)
{
	width = Width;
	height = High;
	MWidget::SetSize(width, height);			//设定当前大小
}
void MHideWidget::Hide(void)
{
	MWTimer *DrawTimer;
	if (HideFlag == false)
	{
		HideFlag = true;
		DrawTimer = newTimer(HIDEWIDGET_DEFAULT_DRAW_TIME);
		Connect(DrawTimer, TimerEvent, this, &MHideWidget::HideDrawTimerSlot);
		flag = width;
	}
	
}
void MHideWidget::Show(void)
{
	MWTimer *DrawTimer;
	if (HideFlag == true)
	{
		HideFlag = false;
		DrawTimer = newTimer(HIDEWIDGET_DEFAULT_DRAW_TIME);
		Connect(DrawTimer, TimerEvent, this, &MHideWidget::ShowDrawTimerSlot);
		flag = width;
	}
}
MHideWidget::~MHideWidget(void)
{
	
}

