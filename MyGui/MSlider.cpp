#include "MSlider.h"


MSlider::MSlider(MWidget *Parent, int x, int y, int xsize, int ysize, int Flag)
:MWidget(Parent, xsize, ysize, x, y, 0, Flag),
BackColor(MSLIDER_DEFAULT_BACK_BACK_COLOR),
BackTextColor(MSLIDER_DEFAULT_BACK_TEXT_COLOR),
SliderUpColor0(MSLIDER_DEFAULT_SLIDER_UP0_COLOR),
SliderUpColor1(MSLIDER_DEFAULT_SLIDER_UP1_COLOR),
SliderTextColor(MSLIDER_DEFAULT_SLIDER_TEXT_COLOR),
SliderBackColor(MSLIDER_DEFAULT_SLIDER_BACK_COLOR),
SliderDownColor(MSLIDER_DEFAULT_SLIDER_DOWN_COLOR),
CurrValue(20),
MinValue(MSLIDER_DEFAULT_VALUE_MIN),
MaxValue(MSLIDER_DEFAULT_VALUE_MAX),
SliderWidth(MSLIDER_DEFAULT_SLIDER_WIDTH),
BackShowValNum(MSLIDER_DEFAULT_BACK_SHOW_VAL_NUM),
Font(MSLIDER_DEFAULT_FONT),
Unit(MSLIDER_DEFAULT_VALUE_UNIT_CHAR)
{
	SetHasTrans();
	Connect(this, PidStateChanged, this, &MSlider::PidStateChangedSlot);
	Connect(this, Touch, this, &MSlider::TouchSlot);
}
MSlider::~MSlider(void)
{
	
}
void MSlider::Dec(void)
{
	if (CurrValue > MinValue)
	{
		CurrValue--;
		Paint();
	}	
}
void MSlider::Inc(void)
{
	if (CurrValue < MaxValue)
	{
		CurrValue++;
		Paint();
	}
}
void MSlider::SetUnitText(char *text)
{
	Unit = text;
}
void MSlider::TouchSlot(WM_PID_STATE_CHANGED_INFO *paramter)
{
	if (paramter->State)
	{
		CurrValue = (float)paramter->x / GetWindowSizeX() * (MaxValue - MinValue) + 0.5;
	}
	Paint();
}
void MSlider::PidStateChangedSlot(WM_PID_STATE_CHANGED_INFO *paramter)
{
	
}
void MSlider::Painter(GUI_RECT *pRect)
{
	char *str = new char[20];
	GUI_RECT Rect = *pRect;
	GUI_SetFont(Font);
	Rect.x0 -= GetWindowOrgX();
	Rect.y0 -= GetWindowOrgY();
	Rect.x1 -= pRect->x0;
	Rect.y1 -= pRect->y0;
	GUI_SetBkColor(GUI_ARGB_COLOR(255,0,0,0));
	GUI_ClearRect(Rect.x0, 0, Rect.x1, 
		(float)GetWindowSizeY() * (((float)1 - (float)MSLIDER_BACK_HIGHT_SCALE) / 2) - 1);
	GUI_ClearRect(Rect.x0, GetWindowSizeY() * ((float)MSLIDER_BACK_HIGHT_SCALE + (((float)1 - MSLIDER_BACK_HIGHT_SCALE) / 2)),
		Rect.x1, GetWindowSizeY() - 1);
	GUI_SetBkColor(BackColor);
	GUI_ClearRect(Rect.x0, (float)GetWindowSizeY() * ((float)((float)1 - MSLIDER_BACK_HIGHT_SCALE) / 2),
		Rect.x1, GetWindowSizeY() * ((float)MSLIDER_BACK_HIGHT_SCALE + (((float)1 - MSLIDER_BACK_HIGHT_SCALE) / 2)) - 1);
	//Text
	GUI_SetColor(BackTextColor);
	int x, y, textlen;
	sprintf((char *)str, "%d%s", MinValue + MaxValue * (MaxValue - MinValue) / (BackShowValNum - 1), Unit);
	Font->pfGetCharDistX(str[0], &textlen);
	textlen = strlen(str) * textlen;
	for (int i = 0; i < BackShowValNum; i++)
	{	
		sprintf((char *)str, "%d%s", MinValue + i * (MaxValue - MinValue) / (BackShowValNum - 1), Unit);
		x = SliderWidth / 2 + i * ((GetWindowSizeX() - SliderWidth - textlen) / (BackShowValNum - 1));
		y = GetWindowSizeY() / 2 - (Font->YDist / 2);
		Rect.x0 = x;
		Rect.y0 = y;
		Rect.x1 = x + ((GetWindowSizeX() - SliderWidth) / BackShowValNum);
		Rect.y1 = y + GetWindowSizeY();
		GUI_DispStringInRectWrap(str, &Rect, GUI_TA_LEFT, GUI_WRAPMODE_CHAR);
	}
	//Slider draw
	x = (GetWindowSizeX() - SliderWidth) * ((float)CurrValue / (float)(MaxValue - MinValue));
	y = GetWindowSizeY() * (((float)1 - MSLIDER_BACK_HIGHT_SCALE) / 2);
	GUI_DrawGradientH(x, 0, x + SliderWidth - 1, y - 1, SliderUpColor0, SliderUpColor1);

	y = GetWindowSizeY() * ((float)((float)1 - MSLIDER_BACK_HIGHT_SCALE) / 2 + MSLIDER_BACK_HIGHT_SCALE);
	GUI_DrawGradientV(x, y, x + SliderWidth - 1, y + GetWindowSizeY() * (((float)1 - MSLIDER_BACK_HIGHT_SCALE) / 2) - 1,
		SliderDownColor, SliderDownColor);
	GUI_SetColor(SliderTextColor);
	y = y + GetWindowSizeY() * (((float)1 - MSLIDER_BACK_HIGHT_SCALE) / 2) - 1;
	GUI_DrawVLine(SliderWidth / 2 + x,  y, y + 12);

	GUI_SetBkColor(SliderBackColor);
	GUI_SetColor(SliderTextColor);
	sprintf((char *)str, "%d%s", CurrValue, Unit);
	Rect.x0 = x;
	Rect.x1 = x + SliderWidth - 1;
	Rect.y0 = GetWindowSizeY() * (((float)1 - MSLIDER_BACK_HIGHT_SCALE) / 2);
	Rect.y1 = Rect.y0 + (float)GetWindowSizeY() * MSLIDER_BACK_HIGHT_SCALE - 1;
	GUI_ClearRectEx(&Rect);
	GUI_DispStringInRectWrap(str, &Rect, GUI_TA_HCENTER | GUI_TA_VCENTER, GUI_WRAPMODE_CHAR);

	GUI_SetColor(GUI_ARGB_COLOR(00, 0, 0, 0));
	//GUI_InvertRect(Rect.x0, Rect.y0, Rect.x1, Rect.y1);
	delete[] str;
}


