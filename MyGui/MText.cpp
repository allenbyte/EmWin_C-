#include "MText.h"
#include <string.h>

//static GUI_FONT *TextDefaultFont = MTEXT_DEFAULT_FONT;

MText::MText(MWidget *Parent, int x, int y, int xsize, int ysize, int textAlign, int Flags)
: MWidget(Parent, xsize, ysize, x, y, 0, Flags),
	TextAlign(textAlign),
	text(0),
	Font(MTEXT_DEFAULT_FONT),
	TextColor(MTEXT_TEXT_COLOR),
	BackColor(MTEXT_BACK_COLOR),
	AutoTextColor(false)
{
	Init();
}

MText::MText(char  *str)
: MWidget(),
	TextAlign(0),
	text(0),
	Font(0),
	TextColor(MTEXT_TEXT_COLOR),
	BackColor(MTEXT_BACK_COLOR),
	AutoTextColor(false)
{
	SetText(str);
	Init();
}
void MText::Init(void)
{
	SetHasTrans();
	
}

void MText::SetBackColor(GUI_COLOR Color)
{
	BackColor = Color;
}

void MText::SetText(char *str)
{
	int len;
	if (text != 0)
		delete text;
	len = strlen(str);
	text = new char[len + 1];
	strcpy(text, str);
	text[len] = '\0';
}




void MText::Painter(GUI_RECT *pRect)
{
	GUI_RECT Rect = *pRect;
	GUI_SetBkColor(BackColor);
	Rect.x0 -= GetWindowOrgX();
	Rect.y0 -= GetWindowOrgY();
	Rect.x1 -= pRect->x0;
	Rect.y1 -= pRect->y0;
	GUI_ClearRectEx(pRect);
	GUI_SetFont(Font);
	if (AutoTextColor)
		GUI_SetColor(~BackColor);
	else
		GUI_SetColor(TextColor);
	GUI_GetClientRect(&Rect);
	GUI_DispStringInRectWrap(text, &Rect, TextAlign, GUI_WRAPMODE_CHAR);
}

MText::~MText(void)
{
	if (text != 0)
		delete text;
}

