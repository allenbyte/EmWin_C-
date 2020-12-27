#include "MButton.h"
#include "MSignal.h"

#define BUTTON_PRESSURE_VALUE																		20

MButton::MButton(int x, int y, int xsize, int ysize, int Flags)
:hWin(0),
MWidget(xsize, ysize, x, y, 0, Flags)
{
	Init();
}

MButton::MButton(MWidget *Parent, int x, int y, int xsize, int ysize, int Flags)
:hWin(0),
MWidget(Parent, xsize, ysize, x, y, 0, Flags)
{
	Init();
}

void MButton::Init(void)
{
	EnableFlag = true;
	Flag = PIC_NONE;
	Picture = 0;
	BackColor[Disable] = MBUTTON_DEFAULT_DISABLE_BACK_COLOR;
	BackColor[Unpressed] = MBUTTON_DEFAULT_UNPRESSED_BACK_COLOR;
	BackColor[Pressed] = MBUTTON_DEFAULT_PRESSED_BACK_COLOR;
	Font = MBUTTON_DEFAULT_FONT;
	Text = 0;
	xPos = yPos = 0;
	TextAlign = MBUTTON_TEXT_DEFAULT_ALIGN;
	TextColor[Disable] = MBUTTON_DEFAULT_TEXT_DISABLE_BACK_COLOR;
	TextColor[Unpressed] = MBUTTON_DEFAULT_TEXT_UNPRESSED_BACK_COLOR;
	TextColor[Pressed] = MBUTTON_DEFAULT_TEXT_PRESSED_BACK_COLOR;
	PressedFlag = false;
	//Connet signal and slot
	Connect(this, Touch, this, &MButton::TouchSlot);
	Connect(this, PidStateChanged, this, &MButton::PidStateChangedSlot);
}

GUI_BITMAP * MButton::GetBitmap(ButtonShowConfig ShowConfig)
{
	return Picture->Bitmap[ShowConfig];
}
GUI_COLOR MButton::ButtonPressureColor(GUI_COLOR UnPressureColor)
{
	int r = GUI_GET_COLOR_R(UnPressureColor), g = GUI_GET_COLOR_G(UnPressureColor), b = GUI_GET_COLOR_B(UnPressureColor);
	r += ((r + BUTTON_PRESSURE_VALUE) < 255) ? BUTTON_PRESSURE_VALUE : 255 - r;
	g += ((g + BUTTON_PRESSURE_VALUE) < 255) ? BUTTON_PRESSURE_VALUE : 255 - g;
	b += ((b + BUTTON_PRESSURE_VALUE) < 255) ? BUTTON_PRESSURE_VALUE : 255 - b;
	return GUI_RGB_COLOR(r, g, b);
}
GUI_COLOR MButton::GetBkColor(ButtonShowConfig ShowIndex)
{
	return BackColor[ShowIndex];
}
GUI_FONT *MButton::GetFont(void)
{
	return Font;
}
void MButton::SetBitmap(ButtonShowConfig ShowIndex, GUI_BITMAP * pBitmap, int x, int y)
{
	if (Picture == 0)Picture = new(PictureTypedef);
	Picture->Bitmap[ShowIndex] = pBitmap; 
	Picture->BitX = x; 
	Picture->BitY = y; 
	Flag = PIC_BIT;
}
void MButton::SetBmp(ButtonShowConfig ShowIndex, void *pBitmap, int x, int y)
{
	if (Picture == 0)Picture = new(PictureTypedef);
	Picture->Bmp[ShowIndex] = pBitmap; 
	Picture->BitX = x;
	Picture->BitY = y; 
	Flag = PIC_BMP;
}
void MButton::SetStreamedBitmap(unsigned int Index, const GUI_BITMAP_STREAM * pBitmap, int x, int y)
{
	if (Picture == 0)Picture = new(PictureTypedef);
	Picture->StrBitmap[Index], 
	Picture->BitX = x,
	Picture->BitY = y;
	Flag = PIC_STR_BIT;
}
void MButton::SetText(char *str)
{
	int len = strlen(str);
	if (Text != 0) delete[] Text;
	Text = new char[len + 1]; 
	strcpy(Text, str); 
	Text[len] = '\0';
}
//slot
void MButton::TouchSlot(WM_PID_STATE_CHANGED_INFO *paramter)
{ 
	
}
void MButton::PidStateChangedSlot(WM_PID_STATE_CHANGED_INFO *paramter)
{ 
	if (paramter->State == 0)
	{ 
		PressedFlag = false; 
		Released(this);
		Paint(); 
	} 
	else
	{
		PressedFlag = true;
		Paint();
		Clicked(this);
	}
}
void MButton::Painter(GUI_RECT *pRect)
{
	GUI_RECT Rect;
	if (Flag == PIC_NONE)
	{
		if (EnableFlag == true)
		{
			GUI_SetBkColor(BackColor[PressedFlag]);
			GUI_SetColor(TextColor[PressedFlag]);
		}
		else
		{
			GUI_SetBkColor(BackColor[Disable]);
			GUI_SetColor(TextColor[Disable]);
		}
		GUI_SetFont(Font);
		Rect.x0 = 0;
		Rect.y0 = 0;
		Rect.x1 = GetWindowSizeX();
		Rect.y1 = GetWindowSizeY();
		GUI_ClearRect(0, 0, Rect.x1, Rect.y1);
		GUI_DispStringInRectWrap(Text, &Rect, TextAlign, GUI_WRAPMODE_CHAR);
	}
	else if (Flag == PIC_BIT)
	{

	}
	else if (PIC_BMP)
	{

	}
	else if (PIC_STR_BIT)
	{

	}
}
MButton::~MButton(void)
{
	
}

