#ifndef _WIDGET_H_
#define _WIDGET_H_

#include "WM.h"
#include "GUI.h"
#include "MSignal.h"

#define MWIDGET_DEFAULT_SIZE_W													10
#define MWIDGET_DEFAULT_SIZE_H													10



#define GUI_RGB_COLOR(r,g,b)													((unsigned int)b << 16 | (unsigned int)g << 8 | (unsigned int)r & 0xFF)
#define GUI_ARGB_COLOR(a,r,g,b)													((unsigned int)a << 24 \
																				| (unsigned int)b << 16 \
																				| (unsigned int)g << 8 \
																				| (unsigned int)r & 0xFF)
#define GUI_GET_COLOR_R(COLOR)													(COLOR & 0xFF)
#define GUI_GET_COLOR_G(COLOR)													((COLOR >> 8) & 0xFF)
#define GUI_GET_COLOR_B(COLOR)													((COLOR >> 16) & 0xFF)

/*在使用“桌面”窗口时，不支持MWidget，无法保存对象地址，因此回调需要另外处理*/

class MWTimer;


class MWidget
{
public:
	typedef WM_HWIN HANDLETYPE;
	typedef void CALLBACKTYPE(WM_MESSAGE *);
	typedef void tfForEach(HANDLETYPE hWin, void * pData);
	HANDLETYPE hWin;
	MWidget(int width = MWIDGET_DEFAULT_SIZE_W, int height = MWIDGET_DEFAULT_SIZE_H, int x = 0, int y = 0, int NumExtraBytes = 0, U8 style = ConfigHide);
	MWidget(MWidget *hWinParent, int width = MWIDGET_DEFAULT_SIZE_W, int height = MWIDGET_DEFAULT_SIZE_H, int x = 0, int y = 0, int NumExtraBytes = 0, U8 style = ConfigHide);
	MWidget(HANDLETYPE win);																	//基于现有窗口句柄创建对象
	~MWidget(void);
	void Activate(void);																		//激活窗口
	void AttachWindow(MWidget *hParent);														//重新连接父窗口
	void AttachWindow(MWidget *hParent, int x, int y);											//重新连接父窗口并重定义位置
	void BringToBottom(void);																	//将窗口放在其同属窗口下面
	void BringToTop(void);																		//将窗口放在其同属窗口顶部
	int BroadcastMessage(WM_MESSAGE * pMsg);													//发送给定消息到所有现有窗口
	void ClrHasTrans(void);																		//清除有透明性标记
	void Deactivate(void);																		//去除激活窗口管理器
	void DetachWindow(void);																	//断开窗口与其父窗口的关联。窗口管理器将不会重绘分离的窗口
	void DisableWindow(void);																	//将指定窗口设置为禁用状态。WM 不会将指针输入设备(PID) 消息（触摸、鼠标、操纵手柄...）发送到被禁用的窗口
	void EnableWindows(void);																	//将指定的窗口设置为启用状态。启用的窗口接收来自WM 的指针输入设备(PID) 消息（触摸、鼠标、操纵手柄...）
	void ForEachDesc(tfForEach * pcb, void * pData);											//迭代给定窗口的所有后代。窗口的后代是一个子窗口，或孙窗口，或孙窗口的子窗口，或....
	CALLBACKTYPE *GetCallback(void);															//查询窗口回调
	MWidget *GetActiveWindow(void);																//返回用于绘制操作的活动窗口的句柄
	void GetClientRect(GUI_RECT *pRect, MWidget *Widget = 0);									//返回活动窗口的客户区在窗口坐标中的坐标
	MWidget *GetDesktopWindow(int LayerIndex = -1);												//返回桌面窗口
	MWidget *GetDialogItem(MWidget *widget, int id);											//返回对话框项目（小工具）的窗口
	MWidget *GetFirstChild(MWidget *widget);													//返回指定窗口的第一个子窗口
	MWidget *GetFocussedWindow(void);															//返回具有输入焦点的窗口
	bool GetHasTrans(MWidget *widget = 0);														//返回有透明性标记的当前值
	bool GetInvalidRect(GUI_RECT *pRect);														//返回窗口在桌面坐标中的无效矩形
	MWidget *GetNextSibling(void);																//查询窗口的下一同属窗口（没有则返回0）
	int GetOrgX(void);																			//返回活动窗口的原点在桌面坐标
	int GetOrgY(void);																			//返回活动窗口的原点在桌面坐标
	MWidget *GetParent(void);																	//返回指定窗口的父窗口
	MWidget *GetPrevSibling(void);																//返回窗口的前一同属窗口（没有则返回0）
	bool GetStayOnTop(void);																	//返回保持在顶部标记的当前值
	int GetWindowOrgX(void);																	//返回窗口的原点在桌面坐标中的X位置
	int GetWindowOrgY(void);																	//返回窗口的原点在桌面坐标中的Y位置
	void GetWindowRect(GUI_RECT* pRect);														//返回窗口在桌面坐标中的坐标
	void GetWindowRect(MWidget *widget,GUI_RECT* pRect);										//返回窗口在桌面坐标中的坐标(0表示查询活动窗口）
	int GetWindowSizeX(void);																	//返回指定窗口的X尺寸
	int GetWindowSizeY(void);																	//返回制定窗口的Y尺寸
	bool HasCaptured(void);																		//给定窗口捕获到鼠标和触摸屏输入时返回1，否则返回0
	bool HasFocus(void);																		//检查窗口是否具有输入焦点
	void Hide(void);																			//使窗口不可见
	void InvalidateArea(GUI_RECT *pRect);														//使显示器的指定矩形区域无效(GUI_RECT 结构的坐标必须使用窗口坐标)
	void InvalidateRect(GUI_RECT *pRect);														//使窗口的指定矩形区域无效(GUI_RECT 结构的坐标必须使用窗口坐标)
	void InvalidateWindow(void);																//使指定窗口无效(调用此函数会告诉WM 指定的窗口未更新)
	bool IsCompletelyCovered(void);																//检查给定窗口是否完全被覆盖
	bool IsCompletelyVisible(void);																//检查给定窗口是否完全可见
	bool IsEnabled(void);																		//检查窗口是否启用
	bool IsVisible(void);																		//检查窗口是否可见
	bool IsWindow(void);																		//确定指定句柄是否是有效的窗口句柄
	void MakeModal(void);																		//此函数使窗口在“模态”模式下作业
	void MoveChildTo(int x, int y);																//将窗口移动到某个位置
	void MoveTo(int x, int y);																	//将窗口移动到某个位置
	void Move(int x, int y);																	//将指定窗口移动某段距离
	void NotifyParent(int Notification);														//将WM_NOTIFY_PARENT 消息发送到给定窗口((WM_NOTIFOCATION_USER + 0))
	void Paint(void){ WM_Paint(hWin); }															//立即绘制或重绘窗口
	void PaintWindowAndDescs(void){ WM_PaintWindowAndDescs(hWin); }								//给窗口及其所有子代窗口着色
	void ReleaseCapture(void){ WM_ReleaseCapture(); }											//释放捕获的鼠标和触摸屏输入
	void ResizeWindow(int x, int y){ WM_ResizeWindow(hWin, x, y); }								//通过增加（或减少）给定差别更改指定窗口的尺寸
	void SelectWindow(void){ WM_SelectWindow(hWin); }											//设置要用于绘制操作的活动窗口
	void SendMessage(MWidget *widget, WM_MESSAGE* pMsg){ WM_SendMessage(widget->hWin, pMsg); }	//将消息发送到指定窗口
	void SendMessageNoPara(MWidget *widget, int MsgId)											//将不带参数的消息发送到指定窗口
	{WM_SendMessageNoPara(widget->hWin, MsgId);}
	void SendToParent(MWidget *widget, WM_MESSAGE* pMsg){ WM_SendMessage(widget->hWin, pMsg); }	//将给定消息发送到给定窗口的父窗口
	void SetBkColor(GUI_COLOR Color){ BackColor = Color; }										//设定窗口背景颜色
	void SetDesktopColor(GUI_COLOR Color, int LayerIndex = -1)									//设置桌面窗口的颜色("LayerIndex"在多层环境下设置桌面窗口的颜色)
	{
		if (LayerIndex == -1)
			WM_SetDesktopColor(Color);
		else
			WM_SetDesktopColorEx(Color, LayerIndex);
	}
	void SetCallback(MWidget *widget, CALLBACKTYPE *cb){ WM_SetCallback(widget->hWin, cb); }	//设置窗口管理器要执行的回调例程
	void SetCapture(void)
	{WM_SetCapture(hWin, 1);}
	void SetConfig(unsigned long flag){ WM_SetCreateFlags(flag); }								//设置在创建新窗口时用作默认的标标记
	void SetFocus(void){ WM_SetFocus(hWin); }													//将输入焦点设置到指定窗口
	void SetHasTrans(void);																		//设置有透明性 标记（将其设置为1）
	void SetId(int Id){ WM_SetId(hWin, Id); }													//此函数将WM_SET_ID 消息发送到给定窗口	
	WM_tfPollPID * SetpfPollPID(WM_tfPollPID * pf){ return WM_SetpfPollPID(pf); }				//设置将由窗口管理器调用的函数，以轮询指针输入设备（触摸屏或鼠标）
	void SetSize(int x, int y){ WM_SetSize(hWin, x, y); }										//设置窗口的新尺寸
	void SetPos(int x, int y, int xsize, int ysize)												//设置窗口的尺寸和位置
	{
		WM_SetWindowPos(hWin, x, y, xsize, ysize);
	}
	void SetXSize(int xsize){ WM_SetXSize(hWin, xsize); }										//设置窗口的新X尺寸
	void SetYSize(int ysize){ WM_SetYSize(hWin, ysize); }										//设置窗口的新Y尺寸
	void SetStayOnTop(bool On){ WM_SetStayOnTop(hWin, On); }									//设置保持在顶部标记 
	void SetTransState(unsigned long State){ WM_SetTransState(hWin, State); }					//设置或清除给定窗口的标记WM_CF_HASTRANS 和WM_CF_CONST_OUTLINE
	GUI_RECT* SetUserClipRect(GUI_RECT* pRect)													//临时将当前窗口的裁剪区缩小为指定矩形
	{
		return (GUI_RECT *)WM_SetUserClipRect(pRect);
		/*
		返回值
			指向前一裁剪矩形的指针。
		其他信息
			可传递NULL 指针，以恢复默认设置。裁剪矩形将在使用回调时由WM 自动重置。
			指定的矩形必须与当前窗口相关，不能将裁剪矩形扩大到超出当前窗口矩形。
			应用程序必须确保指定的矩形保留其值直到不再需要它，即，直到指定了其它裁剪矩形或直到传递了
			NULL 指针为止。这意味着如果裁剪矩形在返回操作之前始终保持活动状态，则作为参数传递的矩形
			结构不应为自动变量（通常位于堆栈上）。此时，应使用静态变量。
		*/
	}
	void Show(void);																			//使窗口可见
	void Update(void){ WM_Update(hWin); }														//立即绘制指定窗口的无效部分
	void UpdateWindowAndDescs(void){ WM_UpdateWindowAndDescs(hWin); }							//对给定窗口的无效部分及其所有后代窗口的无效部分着色
	void ValidateRect(GUI_RECT* pRect){ WM_ValidateRect(hWin, pRect); }							//使窗口的指定矩形区域有效(必须使用桌面坐标)
	void ValidateWindow(void){ WM_ValidateWindow(hWin); }										//使指定的窗口有效
	//存储设备的支持
	void DisableMemdev(void){ WM_DisableMemdev(hWin); }											//禁止使用存储设备来重绘窗口
	void EnableMemdev(void){ WM_EnableMemdev(hWin); }											//启用使用存储设备来重绘窗口
	//定时器相关函数
	
	void Exec(void);																			//通过执行回调重绘无效窗口（所有工作）。
	//Timer 
	MWTimer *newTimer(int Period);
	void DeleteTimer(MWTimer *timer);

	//配置标志
	enum Config{
		ConfigShow = WM_CF_SHOW,																//显示
		ConfigHide = WM_CF_HIDE,																//隐藏
		ConfigMemDev = WM_CF_MEMDEV,															//使用内存设备
		ConfigStayOnTop = WM_CF_STAYONTOP,														//留在上面
		ConfigDisabled = WM_CF_DISABLED,														//使失效
		
	};
public:
	//signal
	MSignal <int> SubWindow;
	MSignal <WM_PID_STATE_CHANGED_INFO *> Touch;																		//指针输入设备接触到处于按下状态的窗口轮廓时发送到窗口
	MSignal <WM_PID_STATE_CHANGED_INFO *> PidStateChanged;																//按下状态已更改时，发送到指针输入设备指向的窗口

	//Timer
	vector <MWTimer *> Timer;
private:
	CALLBACKTYPE *SubWindowCallback;
	GUI_COLOR BackColor;
	void init(void);
	MWidget *ReturnWindows(HANDLETYPE win);														//将句柄转换成窗口对象，无对象则创建一个
protected:
	virtual void Callback(WM_MESSAGE *pMsg);
private:
	static void _Callback(WM_MESSAGE *pMsg);
	virtual void Painter(GUI_RECT *pRect);
	
};



#endif

