#ifndef _MWTIMER_H_
#define _MWTIMER_H_
#include "MWidget.h"
#include "WM.h"

class MWTimer
{
public:
	MSignal<MWTimer *> TimerEvent;
	WM_HTIMER hTimer;
	MWTimer(MWidget *widget, int Period)
	{
		hTimer = WM_CreateTimer(widget->hWin, 0, Period, 0);
	}
	~MWTimer()
	{ 
			WM_DeleteTimer(hTimer); 
	}

	int GetId(void){ return WM_GetTimerId(hTimer); }																//查询定时器ID
	void Restart(int Period){ WM_RestartTimer(hTimer, Period); }													//重新开始指定周期
};


#endif
