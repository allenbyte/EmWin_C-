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

/*��ʹ�á����桱����ʱ����֧��MWidget���޷���������ַ����˻ص���Ҫ���⴦��*/

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
	MWidget(HANDLETYPE win);																	//�������д��ھ����������
	~MWidget(void);
	void Activate(void);																		//�����
	void AttachWindow(MWidget *hParent);														//�������Ӹ�����
	void AttachWindow(MWidget *hParent, int x, int y);											//�������Ӹ����ڲ��ض���λ��
	void BringToBottom(void);																	//�����ڷ�����ͬ����������
	void BringToTop(void);																		//�����ڷ�����ͬ�����ڶ���
	int BroadcastMessage(WM_MESSAGE * pMsg);													//���͸�����Ϣ���������д���
	void ClrHasTrans(void);																		//�����͸���Ա��
	void Deactivate(void);																		//ȥ������ڹ�����
	void DetachWindow(void);																	//�Ͽ��������丸���ڵĹ��������ڹ������������ػ����Ĵ���
	void DisableWindow(void);																	//��ָ����������Ϊ����״̬��WM ���Ὣָ�������豸(PID) ��Ϣ����������ꡢ�����ֱ�...�����͵������õĴ���
	void EnableWindows(void);																	//��ָ���Ĵ�������Ϊ����״̬�����õĴ��ڽ�������WM ��ָ�������豸(PID) ��Ϣ����������ꡢ�����ֱ�...��
	void ForEachDesc(tfForEach * pcb, void * pData);											//�����������ڵ����к�������ڵĺ����һ���Ӵ��ڣ����ﴰ�ڣ����ﴰ�ڵ��Ӵ��ڣ���....
	CALLBACKTYPE *GetCallback(void);															//��ѯ���ڻص�
	MWidget *GetActiveWindow(void);																//�������ڻ��Ʋ����Ļ���ڵľ��
	void GetClientRect(GUI_RECT *pRect, MWidget *Widget = 0);									//���ػ���ڵĿͻ����ڴ��������е�����
	MWidget *GetDesktopWindow(int LayerIndex = -1);												//�������洰��
	MWidget *GetDialogItem(MWidget *widget, int id);											//���ضԻ�����Ŀ��С���ߣ��Ĵ���
	MWidget *GetFirstChild(MWidget *widget);													//����ָ�����ڵĵ�һ���Ӵ���
	MWidget *GetFocussedWindow(void);															//���ؾ������뽹��Ĵ���
	bool GetHasTrans(MWidget *widget = 0);														//������͸���Ա�ǵĵ�ǰֵ
	bool GetInvalidRect(GUI_RECT *pRect);														//���ش��������������е���Ч����
	MWidget *GetNextSibling(void);																//��ѯ���ڵ���һͬ�����ڣ�û���򷵻�0��
	int GetOrgX(void);																			//���ػ���ڵ�ԭ������������
	int GetOrgY(void);																			//���ػ���ڵ�ԭ������������
	MWidget *GetParent(void);																	//����ָ�����ڵĸ�����
	MWidget *GetPrevSibling(void);																//���ش��ڵ�ǰһͬ�����ڣ�û���򷵻�0��
	bool GetStayOnTop(void);																	//���ر����ڶ�����ǵĵ�ǰֵ
	int GetWindowOrgX(void);																	//���ش��ڵ�ԭ�������������е�Xλ��
	int GetWindowOrgY(void);																	//���ش��ڵ�ԭ�������������е�Yλ��
	void GetWindowRect(GUI_RECT* pRect);														//���ش��������������е�����
	void GetWindowRect(MWidget *widget,GUI_RECT* pRect);										//���ش��������������е�����(0��ʾ��ѯ����ڣ�
	int GetWindowSizeX(void);																	//����ָ�����ڵ�X�ߴ�
	int GetWindowSizeY(void);																	//�����ƶ����ڵ�Y�ߴ�
	bool HasCaptured(void);																		//�������ڲ������ʹ���������ʱ����1�����򷵻�0
	bool HasFocus(void);																		//��鴰���Ƿ�������뽹��
	void Hide(void);																			//ʹ���ڲ��ɼ�
	void InvalidateArea(GUI_RECT *pRect);														//ʹ��ʾ����ָ������������Ч(GUI_RECT �ṹ���������ʹ�ô�������)
	void InvalidateRect(GUI_RECT *pRect);														//ʹ���ڵ�ָ������������Ч(GUI_RECT �ṹ���������ʹ�ô�������)
	void InvalidateWindow(void);																//ʹָ��������Ч(���ô˺��������WM ָ���Ĵ���δ����)
	bool IsCompletelyCovered(void);																//�����������Ƿ���ȫ������
	bool IsCompletelyVisible(void);																//�����������Ƿ���ȫ�ɼ�
	bool IsEnabled(void);																		//��鴰���Ƿ�����
	bool IsVisible(void);																		//��鴰���Ƿ�ɼ�
	bool IsWindow(void);																		//ȷ��ָ������Ƿ�����Ч�Ĵ��ھ��
	void MakeModal(void);																		//�˺���ʹ�����ڡ�ģ̬��ģʽ����ҵ
	void MoveChildTo(int x, int y);																//�������ƶ���ĳ��λ��
	void MoveTo(int x, int y);																	//�������ƶ���ĳ��λ��
	void Move(int x, int y);																	//��ָ�������ƶ�ĳ�ξ���
	void NotifyParent(int Notification);														//��WM_NOTIFY_PARENT ��Ϣ���͵���������((WM_NOTIFOCATION_USER + 0))
	void Paint(void){ WM_Paint(hWin); }															//�������ƻ��ػ洰��
	void PaintWindowAndDescs(void){ WM_PaintWindowAndDescs(hWin); }								//�����ڼ��������Ӵ�������ɫ
	void ReleaseCapture(void){ WM_ReleaseCapture(); }											//�ͷŲ�������ʹ���������
	void ResizeWindow(int x, int y){ WM_ResizeWindow(hWin, x, y); }								//ͨ�����ӣ�����٣�����������ָ�����ڵĳߴ�
	void SelectWindow(void){ WM_SelectWindow(hWin); }											//����Ҫ���ڻ��Ʋ����Ļ����
	void SendMessage(MWidget *widget, WM_MESSAGE* pMsg){ WM_SendMessage(widget->hWin, pMsg); }	//����Ϣ���͵�ָ������
	void SendMessageNoPara(MWidget *widget, int MsgId)											//��������������Ϣ���͵�ָ������
	{WM_SendMessageNoPara(widget->hWin, MsgId);}
	void SendToParent(MWidget *widget, WM_MESSAGE* pMsg){ WM_SendMessage(widget->hWin, pMsg); }	//��������Ϣ���͵��������ڵĸ�����
	void SetBkColor(GUI_COLOR Color){ BackColor = Color; }										//�趨���ڱ�����ɫ
	void SetDesktopColor(GUI_COLOR Color, int LayerIndex = -1)									//�������洰�ڵ���ɫ("LayerIndex"�ڶ�㻷�����������洰�ڵ���ɫ)
	{
		if (LayerIndex == -1)
			WM_SetDesktopColor(Color);
		else
			WM_SetDesktopColorEx(Color, LayerIndex);
	}
	void SetCallback(MWidget *widget, CALLBACKTYPE *cb){ WM_SetCallback(widget->hWin, cb); }	//���ô��ڹ�����Ҫִ�еĻص�����
	void SetCapture(void)
	{WM_SetCapture(hWin, 1);}
	void SetConfig(unsigned long flag){ WM_SetCreateFlags(flag); }								//�����ڴ����´���ʱ����Ĭ�ϵı���
	void SetFocus(void){ WM_SetFocus(hWin); }													//�����뽹�����õ�ָ������
	void SetHasTrans(void);																		//������͸���� ��ǣ���������Ϊ1��
	void SetId(int Id){ WM_SetId(hWin, Id); }													//�˺�����WM_SET_ID ��Ϣ���͵���������	
	WM_tfPollPID * SetpfPollPID(WM_tfPollPID * pf){ return WM_SetpfPollPID(pf); }				//���ý��ɴ��ڹ��������õĺ���������ѯָ�������豸������������꣩
	void SetSize(int x, int y){ WM_SetSize(hWin, x, y); }										//���ô��ڵ��³ߴ�
	void SetPos(int x, int y, int xsize, int ysize)												//���ô��ڵĳߴ��λ��
	{
		WM_SetWindowPos(hWin, x, y, xsize, ysize);
	}
	void SetXSize(int xsize){ WM_SetXSize(hWin, xsize); }										//���ô��ڵ���X�ߴ�
	void SetYSize(int ysize){ WM_SetYSize(hWin, ysize); }										//���ô��ڵ���Y�ߴ�
	void SetStayOnTop(bool On){ WM_SetStayOnTop(hWin, On); }									//���ñ����ڶ������ 
	void SetTransState(unsigned long State){ WM_SetTransState(hWin, State); }					//���û�����������ڵı��WM_CF_HASTRANS ��WM_CF_CONST_OUTLINE
	GUI_RECT* SetUserClipRect(GUI_RECT* pRect)													//��ʱ����ǰ���ڵĲü�����СΪָ������
	{
		return (GUI_RECT *)WM_SetUserClipRect(pRect);
		/*
		����ֵ
			ָ��ǰһ�ü����ε�ָ�롣
		������Ϣ
			�ɴ���NULL ָ�룬�Իָ�Ĭ�����á��ü����ν���ʹ�ûص�ʱ��WM �Զ����á�
			ָ���ľ��α����뵱ǰ������أ����ܽ��ü��������󵽳�����ǰ���ھ��Ρ�
			Ӧ�ó������ȷ��ָ���ľ��α�����ֱֵ��������Ҫ��������ֱ��ָ���������ü����λ�ֱ��������
			NULL ָ��Ϊֹ������ζ������ü������ڷ��ز���֮ǰʼ�ձ��ֻ״̬������Ϊ�������ݵľ���
			�ṹ��ӦΪ�Զ�������ͨ��λ�ڶ�ջ�ϣ�����ʱ��Ӧʹ�þ�̬������
		*/
	}
	void Show(void);																			//ʹ���ڿɼ�
	void Update(void){ WM_Update(hWin); }														//��������ָ�����ڵ���Ч����
	void UpdateWindowAndDescs(void){ WM_UpdateWindowAndDescs(hWin); }							//�Ը������ڵ���Ч���ּ������к�����ڵ���Ч������ɫ
	void ValidateRect(GUI_RECT* pRect){ WM_ValidateRect(hWin, pRect); }							//ʹ���ڵ�ָ������������Ч(����ʹ����������)
	void ValidateWindow(void){ WM_ValidateWindow(hWin); }										//ʹָ���Ĵ�����Ч
	//�洢�豸��֧��
	void DisableMemdev(void){ WM_DisableMemdev(hWin); }											//��ֹʹ�ô洢�豸���ػ洰��
	void EnableMemdev(void){ WM_EnableMemdev(hWin); }											//����ʹ�ô洢�豸���ػ洰��
	//��ʱ����غ���
	
	void Exec(void);																			//ͨ��ִ�лص��ػ���Ч���ڣ����й�������
	//Timer 
	MWTimer *newTimer(int Period);
	void DeleteTimer(MWTimer *timer);

	//���ñ�־
	enum Config{
		ConfigShow = WM_CF_SHOW,																//��ʾ
		ConfigHide = WM_CF_HIDE,																//����
		ConfigMemDev = WM_CF_MEMDEV,															//ʹ���ڴ��豸
		ConfigStayOnTop = WM_CF_STAYONTOP,														//��������
		ConfigDisabled = WM_CF_DISABLED,														//ʹʧЧ
		
	};
public:
	//signal
	MSignal <int> SubWindow;
	MSignal <WM_PID_STATE_CHANGED_INFO *> Touch;																		//ָ�������豸�Ӵ������ڰ���״̬�Ĵ�������ʱ���͵�����
	MSignal <WM_PID_STATE_CHANGED_INFO *> PidStateChanged;																//����״̬�Ѹ���ʱ�����͵�ָ�������豸ָ��Ĵ���

	//Timer
	vector <MWTimer *> Timer;
private:
	CALLBACKTYPE *SubWindowCallback;
	GUI_COLOR BackColor;
	void init(void);
	MWidget *ReturnWindows(HANDLETYPE win);														//�����ת���ɴ��ڶ����޶����򴴽�һ��
protected:
	virtual void Callback(WM_MESSAGE *pMsg);
private:
	static void _Callback(WM_MESSAGE *pMsg);
	virtual void Painter(GUI_RECT *pRect);
	
};



#endif

