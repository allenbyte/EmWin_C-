#include "mwidget.h"
#include "MWTimer.h"

MWidget::MWidget(MWidget *hWinParent, int width, int height,
	int x, int y, int NumExtraBytes, U8 style)
	: hWin(0), SubWindowCallback(0), BackColor(GUI_RGB_COLOR(255, 255, 255))
{
	if (hWinParent == 0)
		hWin = WM_CreateWindow(x, y, width, height, style, 0, NumExtraBytes + sizeof(this));
	else
		hWin = WM_CreateWindowAsChild(x, y, width, height, hWinParent->hWin, style, 0, NumExtraBytes + sizeof(this));
	init();
}
MWidget::MWidget(int width, int height,
	int x, int y, int NumExtraBytes, U8 style)
	: hWin(0), SubWindowCallback(0)
{
	
	hWin = WM_CreateWindow(x, y, width, height, style, 0, NumExtraBytes + sizeof(this));
	init();
	
}
MWidget::MWidget(HANDLETYPE win)
:hWin(win), SubWindowCallback(0)
{
	U32 This;
	This = (U32)this;
	WM_SetUserData(hWin, &This, sizeof(this));
}
void MWidget::init(void)
{
	U32 This;
	//signal 
	This = (U32)this;
	WM_SetUserData(hWin, &This, sizeof(this));
	CALLBACKTYPE *cb;
	cb = MWidget::_Callback;
	WM_SetCallback(hWin, cb);
}
MWidget *MWidget::ReturnWindows(HANDLETYPE win)
{
	MWidget *This = 0;
	U32 tmp = 0;
	WM_GetUserData(win, &tmp, sizeof(tmp));
	This = (MWidget *)tmp;
	if (This == 0)
	{
		This = new MWidget(win);
	}
	return This;
}

void MWidget::Activate(void)
{
	WM_Activate();
}

void MWidget::AttachWindow(MWidget *hParent)
{
	WM_AttachWindow(hWin, hParent->hWin);
}
void MWidget::AttachWindow(MWidget *hParent, int x, int y)
{
	WM_AttachWindowAt(hWin, hParent->hWin, x, y);
}
void MWidget::BringToBottom(void)
{
	WM_BringToBottom(hWin);
}
void MWidget::BringToTop(void)
{
	WM_BringToTop( hWin);
}
int MWidget::BroadcastMessage(WM_MESSAGE * pMsg)
{
	return WM_BroadcastMessage(pMsg);
}
void MWidget::ClrHasTrans(void)
{
	WM_ClrHasTrans(hWin);
}
void MWidget::Deactivate(void)
{
	WM_Deactivate();
}
void MWidget::DetachWindow(void)
{
	WM_DetachWindow(hWin);
}
void MWidget::DisableWindow(void)
{
	WM_DisableWindow(hWin);
}
void MWidget::EnableWindows(void)
{
	WM_EnableWindow(hWin);
}
void MWidget::Exec(void)
{
	WM_Exec();
}

void MWidget::ForEachDesc(tfForEach * pcb, void * pData)
{
	WM_ForEachDesc(hWin, pcb, pData);
}
MWidget::CALLBACKTYPE *MWidget::GetCallback(void)
{
	return WM_GetCallback(hWin);
}
MWidget* MWidget::GetActiveWindow(void)
{
	HANDLETYPE win;
	win = WM_GetActiveWindow();
	return ReturnWindows(win);
}
void MWidget::GetClientRect(GUI_RECT *pRect, MWidget *Widget)
{
	if (Widget == 0)
		WM_GetClientRect(pRect);
	else
		WM_GetClientRectEx(hWin, pRect);
}
MWidget *MWidget::GetDesktopWindow(int LayerIndex)
{
	HANDLETYPE win;
	if (LayerIndex != -1)
		win = WM_GetDesktopWindow();
	else
		win = WM_GetDesktopWindowEx(LayerIndex);
	
	return ReturnWindows(win);
}
MWidget *MWidget::GetDialogItem(MWidget *widget, int id)
{
	HANDLETYPE win;;
	win = WM_GetDialogItem(widget->hWin, id);
	return ReturnWindows(win);
}
MWidget *MWidget::GetFirstChild(MWidget *widget)
{
	HANDLETYPE win;
	win = WM_GetFirstChild(widget->hWin);
	return ReturnWindows(win);
}
MWidget *MWidget::GetFocussedWindow(void)
{
	HANDLETYPE win;
	win = WM_GetFocussedWindow();
	return ReturnWindows(win);
}
bool MWidget::GetHasTrans(MWidget *widget)
{
	if (widget == 0)
		return WM_GetHasTrans(hWin) == 1.;
	return WM_GetHasTrans(widget->hWin) == 1;
}
bool MWidget::GetInvalidRect(GUI_RECT *pRect)
{
	return WM_GetInvalidRect(hWin, pRect) == 1;
}
MWidget *MWidget::GetNextSibling(void)
{
	HANDLETYPE win;
	win = WM_GetNextSibling(hWin);
	if (win == 0)
		return 0;
	return ReturnWindows(win);
}
int MWidget::GetOrgX(void)
{
	return WM_GetOrgX();
}
int MWidget::GetOrgY(void)
{
	return WM_GetOrgY();
}
MWidget *MWidget::GetParent(void)
{
	HANDLETYPE win;
	win = WM_GetParent(hWin);
	return ReturnWindows(win);
}
MWidget *MWidget::GetPrevSibling(void)
{
	HANDLETYPE win;
	win = WM_GetPrevSibling(hWin);
	if (win == 0)
		return 0;
	return ReturnWindows(hWin);
}
bool MWidget::GetStayOnTop(void)
{
	return WM_GetStayOnTop(hWin) == 1;
}
int MWidget::GetWindowOrgX(void)
{
	return WM_GetWindowOrgX(hWin);
}
int MWidget::GetWindowOrgY(void)
{
	return WM_GetWindowOrgY(hWin);
}
void MWidget::GetWindowRect(GUI_RECT* pRect)
{
	WM_GetWindowRectEx(hWin, pRect);
}
void MWidget::GetWindowRect(MWidget *widget, GUI_RECT* pRect)
{
	if (widget == 0)
		WM_GetWindowRect(pRect);
	else
		widget->GetWindowRect(pRect);
}
int MWidget::GetWindowSizeX(void)
{
	return WM_GetWindowSizeX(hWin);
}
int MWidget::GetWindowSizeY(void)
{
	return WM_GetWindowSizeY(hWin);
}
bool MWidget::HasCaptured(void)
{
	return WM_HasCaptured(hWin) == 1;
}
bool MWidget::HasFocus(void)
{
	return WM_HasFocus(hWin) == 1;
}
void MWidget::Hide(void)
{
	WM_HideWin(hWin);
}
void MWidget::InvalidateArea(GUI_RECT *pRect)
{
	WM_InvalidateArea(pRect);
}
void MWidget::InvalidateRect(GUI_RECT *pRect)
{
	WM_InvalidateRect(hWin, pRect);
}
bool MWidget::IsCompletelyCovered(void)
{
	return WM_IsCompletelyCovered(hWin) == 1;
}
bool MWidget::IsCompletelyVisible(void)
{
	return WM_IsCompletelyVisible(hWin) == 1;
}
bool MWidget::IsEnabled(void)
{
	return WM_IsEnabled(hWin) == 1;
}
bool MWidget::IsVisible(void)
{
	return WM_IsVisible(hWin) == 1;
}
bool MWidget::IsWindow(void)
{
	return WM_IsWindow(hWin) == 1;
}
void MWidget::MakeModal(void)
{
	WM_MakeModal(hWin);
}
void MWidget::MoveChildTo(int x, int y)
{
	WM_MoveChildTo(hWin, x, y);
}
void MWidget::MoveTo(int x, int y)
{
	WM_MoveTo(hWin, x, y);
}
void MWidget::Move(int x, int y)
{
	WM_MoveWindow(hWin, x, y);
}
void MWidget::NotifyParent(int Notification)
{
	WM_NotifyParent(hWin, Notification);
}

void MWidget::Show(void)
{
	WM_ShowWindow(hWin);
}
void MWidget::SetHasTrans(void)
{
	WM_SetHasTrans(hWin);
}

MWTimer *MWidget::newTimer(int Period)
{
	Timer.push_back(new MWTimer(this, Period));
	return Timer[Timer.size() - 1];
}
void MWidget::DeleteTimer(MWTimer *timer)
{
	vector<MWTimer *>::iterator itor;
	delete timer;
	for (itor = Timer.begin(); itor != Timer.end();)
	{
		if (*itor == timer)
		{
			itor = Timer.erase(itor); 
			break;
		}
		else
			itor++;
	}
	vector<MWTimer *>(Timer).swap(Timer);	//ÊÍ·ÅÄÚ´æ
}

void MWidget::_Callback(WM_MESSAGE *pMsg)
{
	MWidget *This;
	U32 tmp;
	WM_GetUserData(pMsg->hWin, &tmp, sizeof(tmp));
	This = (MWidget *)tmp;
	//if (This == 0) return;
	if(pMsg->MsgId == WM_DELETE)
		{
		
	}
	else
		{
		if(This != 0)
			{
			This->Callback(pMsg);
		}
		else
			{
			
		}
	}
	
	
}
void MWidget::Painter(GUI_RECT *pRect)
{
	int x = GetWindowOrgX(), y = GetWindowOrgY();
	GUI_RECT Rect = (*pRect);
	//GUI_SetBkColor(GUI_TRANSPARENT);
	GUI_SetBkColor(BackColor); //GUI_TRANSPARENT
	Rect.x0 -= x;
	Rect.y0 -= y;
	Rect.x1 -= x;
	Rect.y1 -= y;
	GUI_ClearRectEx(&Rect);
	
}
void MWidget::Callback(WM_MESSAGE *pMsg)
{
	int NCode, Id;
	switch(pMsg->MsgId)
	{
		case WM_NOTIFY_PARENT:
			NCode = pMsg->Data.v;
			//Id = pMsg->hWinSrc;
			if(NCode == WM_NOTIFICATION_RELEASED)
			{
				if(SubWindowCallback != 0)
					SubWindowCallback(pMsg);
			}
		break;
		case WM_TOUCH:
			if (pMsg->Data.p != 0)
				Touch((WM_PID_STATE_CHANGED_INFO *)pMsg->Data.p);
			break;
		case WM_PID_STATE_CHANGED:
			PidStateChanged((WM_PID_STATE_CHANGED_INFO *)pMsg->Data.p);
			break;
		case WM_TIMER:
			for (unsigned int i = 0; i < Timer.size(); i++)
			{
				if (Timer[i]->hTimer == pMsg->Data.v)
					Timer[i]->TimerEvent(Timer[i]);
			}
			break;
		case WM_PAINT:
			Painter((GUI_RECT *)pMsg->Data.p);
			
		break;
		default:
			WM_DefaultProc(pMsg);
		break;
	}
}

MWidget::~MWidget(void)
{
	int DeleteWin = 0;
	WM_SetUserData( hWin, &DeleteWin, sizeof(int));
	WM_DeleteWindow(hWin);
}



