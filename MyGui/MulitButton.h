#ifndef MULITBUTTON_H_
#define MULITBUTTON_H_
#include "HideWidget.h"
#include "MButton.h"
#define MULITBUTTON_DEFAULT_BUTTON_NUMBER										3
#define MULITBUTTON_DEFAULT_BUTTON_SIZE_W										80
#define MULITBUTTON_DEFAULT_BUTTON_SIZE_H										30
#define MULITBUTTON_DEFAULT_SIZE_W												(MULITBUTTON_DEFAULT_BUTTON_NUMBER * MULITBUTTON_DEFAULT_BUTTON_SIZE_W)
#define MULITBUTTON_DEFAULT_SZIE_H												(MULITBUTTON_DEFAULT_BUTTON_SIZE_H)

class MulitButton : private MHideWidget{
public:
	MulitButton(MWidget *Parent, int number = MULITBUTTON_DEFAULT_BUTTON_NUMBER, int x = 0, int y = 0, int Buttonwidth = MULITBUTTON_DEFAULT_BUTTON_SIZE_W, int Buttonhigh = MULITBUTTON_DEFAULT_BUTTON_SIZE_H);
	~MulitButton(void);
	void SetButtonXSize(int num, int x);
	void UpdateWinSize(void);												//�ڰ�ť��С���ĺ���Ҫ���ôκ���ˢ�´��ڵĴ�С
private:
	vector <MButton *> Button;
	
};

#endif
