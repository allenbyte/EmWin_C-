#ifndef _MTEXT_H_
#define _MTEXT_H_
#include "MWidget.h"
#include "MSignal.h"

#define MTEXT_DEFAULT_FONT							(GUI_FONT *)&GUI_Font8x16
#define MTEXT_BACK_COLOR							GUI_ARGB_COLOR(255,0,0,0)
#define MTEXT_TEXT_COLOR							GUI_RGB_COLOR(0,0,0)


class MText : private MWidget
{
public:
	MText(MWidget *Parent, int x = 0, int y = 0, int xsize = 10, int ysize = 10, int textAlign = HCenter | VCenter, int Flags = ConfigShow);
	MText(char  *str);
	~MText(void);
	void SetText(char *str);
	void SetBackColor(GUI_COLOR Color);
	void SetTextAlign(U32 align){ TextAlign = align; }
	void SetTextColor(GUI_COLOR Color){ TextColor = Color; }
	void SetFont(GUI_FONT *font){ Font = font; }
	void TextAutoColor(bool enable){ AutoTextColor = enable; }

	enum TextAlignConfig
	{
		Left = GUI_TA_LEFT,
		Right = GUI_TA_RIGHT,
		HCenter = GUI_TA_HCENTER,
		Top = GUI_TA_TOP,
		Bottom = GUI_TA_BOTTOM,
		VCenter = GUI_TA_VCENTER
	};
public:
	//signal
	MSignal<int> textsignal;
private:
	GUI_FONT *Font;
	char *text;
	U32 TextAlign;
	U32 BackColor;
	U32 TextColor;
	bool AutoTextColor;
	void Painter(GUI_RECT *pRect);
	void Init(void);
};





#endif
