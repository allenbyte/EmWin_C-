#ifndef _MBUTTON_H_
#define _MBUTTON_H_
#include "MWidget.h"

#define MBUTTON_DEFAULT_DISABLE_BACK_COLOR													0x003A3A3A
#define MBUTTON_DEFAULT_PRESSED_BACK_COLOR													0x003A3A3A
#define MBUTTON_DEFAULT_UNPRESSED_BACK_COLOR												0x004D4D4D
#define MBUTTON_DEFAULT_TEXT_DISABLE_BACK_COLOR												0x00000000
#define MBUTTON_DEFAULT_TEXT_PRESSED_BACK_COLOR												0x00000000
#define MBUTTON_DEFAULT_TEXT_UNPRESSED_BACK_COLOR											0x00000000
#define MBUTTON_DEFAULT_FONT																(GUI_FONT *)&GUI_Font8x16
#define MBUTTON_TEXT_DEFAULT_ALIGN															(TextAlignConfig)((U32)GUI_TA_HCENTER | (U32)GUI_TA_VCENTER)
class MButton : public MWidget
{
public:
	MButton(int x = 0, int y = 0, int xsize = 150, int ysize = 80, int Flags = ConfigShow);
	MButton(MWidget *Parent, int x = 0, int y = 0, int xsize = 150, int ysize = 80, int Flags = ConfigShow);
	~MButton(void);
	enum ButtonShowConfig
	{
		Disable = 2,
		Pressed = 1,
		Unpressed = 0
	};
	enum TextAlignConfig
	{
		Left = GUI_TA_LEFT,
		Right = GUI_TA_RIGHT,
		HCenter = GUI_TA_HCENTER,
		Top = GUI_TA_TOP,
		Bottom = GUI_TA_BOTTOM,
		VCenter = GUI_TA_VCENTER
	};
	enum PictureFlagType{ PIC_BIT, PIC_BMP, PIC_STR_BIT, PIC_NONE };
	typedef union
	{
		GUI_BITMAP *Bitmap[3];
		GUI_BITMAP_STREAM *StrBitmap[3];
		void *Bmp[3];
		int BitX;
		int BitY;
	}PictureTypedef;
	GUI_BITMAP * GetBitmap(ButtonShowConfig ShowIndex);
	GUI_COLOR GetBkColor(ButtonShowConfig ShowIndex);
	GUI_FONT *GetFont(void);
	void GetText(char *buffer, int maxsize){ strncpy(buffer, Text, maxsize); }
	TextAlignConfig GetTextAlign(void){ return TextAlign; }
	GUI_COLOR GetTextColor(ButtonShowConfig ShowIndex){ return TextColor[ShowIndex]; }
	bool IsPressed(void){ return PressedFlag; }
	void SetBitmap(ButtonShowConfig ShowIndex, GUI_BITMAP * pBitmap, int x = 0, int y = 0);
	static GUI_COLOR ButtonPressureColor(GUI_COLOR UnPressureColor);												//°´ÏÂÑÕÉ«
	void SetBkColor(ButtonShowConfig ShowIndex, GUI_COLOR Color){ BackColor[ShowIndex] = Color; }
	void SetBmp(ButtonShowConfig ShowIndex, void *pBitmap, int x = 0, int y = 0);
	void SetFont(GUI_FONT* pFont){ Font = pFont; }
	void SetPressed(bool state = true){ PressedFlag = state; }
	void SetStreamedBitmap(unsigned int Index, const GUI_BITMAP_STREAM * pBitmap, int x = 0, int y = 0);
	void SetText(char *str);
	void SetTextAlign(TextAlignConfig Align){ TextAlign = Align; }
	void SetTextColor(ButtonShowConfig ShowIndex, GUI_COLOR Color){ TextColor[ShowIndex ] = Color; }
	void SetTextOffset(int x, int y){ xPos = x, yPos = y; }
	void ENABLE(bool valid){ EnableFlag = valid; }
	
	//slot
	void TouchSlot(WM_PID_STATE_CHANGED_INFO *paramter);
	void PidStateChangedSlot(WM_PID_STATE_CHANGED_INFO *paramter);
	//signal
	MSignal <MButton *> Clicked;
	MSignal <MButton *> Released;
private:
	WM_HWIN hWin;
	PictureTypedef *Picture;
	PictureFlagType Flag;
	GUI_COLOR BackColor[3];
	GUI_COLOR TextColor[3];
	GUI_FONT *Font;
	char *Text;
	int xPos, yPos;
	TextAlignConfig TextAlign;
	bool PressedFlag;	
	bool EnableFlag;
	void Init(void);
	void Painter(GUI_RECT *pRect);
};


#endif
