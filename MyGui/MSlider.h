#ifndef _MSLIDER_H_
#define _MSLIDER_H_
#include "MWidget.h"

#define MSLIDER_DEFAULT_SIZE_X													400
#define MSLIDER_DEFAULT_SIZE_Y													60
#define MSLIDER_DEFAULT_VALUE_UNIT_CHAR											"%"
#define MSLIDER_DEFAULT_VALUE_MIN												0
#define MSLIDER_DEFAULT_VALUE_MAX												100
#define MSLIDER_DEFAULT_FONT													(GUI_FONT *)&GUI_Font8x16
#define MSLIDER_DEFAULT_BACK_TEXT_COLOR											GUI_RGB_COLOR(150,150,150)
#define MSLIDER_DEFAULT_BACK_BACK_COLOR											GUI_RGB_COLOR(239, 238, 236)
#define MSLIDER_DEFAULT_SLIDER_UP0_COLOR										GUI_RGB_COLOR(60, 150, 220)
#define MSLIDER_DEFAULT_SLIDER_UP1_COLOR										GUI_RGB_COLOR(50, 200, 120)
#define MSLIDER_DEFAULT_SLIDER_TEXT_COLOR										GUI_RGB_COLOR(100,100,100)
#define MSLIDER_DEFAULT_SLIDER_BACK_COLOR										GUI_RGB_COLOR(255,255,255)
#define MSLIDER_DEFAULT_SLIDER_DOWN_COLOR										GUI_RGB_COLOR(255,255,255)
#define MSLIDER_DEFAULT_SLIDER_WIDTH											40
#define MSLIDER_DEFAULT_BACK_SHOW_VAL_NUM										6

#define MSLIDER_BACK_HIGHT_SCALE												0.6								//60%

class MSlider : private MWidget
{
public:
	MSlider(MWidget *Parent = 0, int x = 0, int y = 0, int xsize = MSLIDER_DEFAULT_SIZE_X, int ysize = MSLIDER_DEFAULT_SIZE_Y, int Flag = ConfigShow);
	~MSlider(void);
	void Dec(void);
	int GetValue(void){ return CurrValue; }
	void Inc(void);
	void SetFont(GUI_FONT *font){ Font = font; }
	void SetBackColor(GUI_COLOR Color){ BackColor = Color; }
	void SetBackTextColor(GUI_COLOR Color){ BackTextColor = Color; }
	void SetSliderTextColor(GUI_COLOR Color){ SliderTextColor = Color; }
	void SetSliderBackColor(GUI_COLOR Color){ SliderBackColor = Color; }
	void SetSliderDownColor(GUI_COLOR Color){ SliderDownColor = Color; }
	void SetSliderUpColor(GUI_COLOR Color0, GUI_COLOR Color1){ SliderUpColor0 = Color0, SliderUpColor0 = Color1; }
	void SetRange(int Min, int Max){ MinValue = Min, MaxValue = Max; }
	void SetValue(int val){ CurrValue = val; }
	void SetSliderWidth(int Width){ SliderWidth = Width; }
	void SetUnitText(char *text);
private:
	//slot
	void TouchSlot(WM_PID_STATE_CHANGED_INFO *paramter);
	void PidStateChangedSlot(WM_PID_STATE_CHANGED_INFO *paramter);
	void Painter(GUI_RECT *pRect);
private:
	GUI_FONT *Font;
	GUI_COLOR BackColor;
	GUI_COLOR BackTextColor;
	GUI_COLOR SliderUpColor0;
	GUI_COLOR SliderUpColor1;
	GUI_COLOR SliderTextColor;
	GUI_COLOR SliderBackColor;
	GUI_COLOR SliderDownColor;
	char *Unit;
	int BackShowValNum;
	int SliderWidth;
	int CurrValue;
	int MinValue;
	int MaxValue;

};





#endif
