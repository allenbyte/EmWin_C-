#ifndef _DESKTOP_H_
#define _DESKTOP_H_

#include "../myGUI/MWidget.h"
#include "../myGUI/MButton.h"
#include "LampControl.h"
#include "JackControl.h"


class Desktop : protected MWidget{
public:
	Desktop(void);
	~Desktop(void);
private:
	
private:
	//slot
	void LampButtonSlot(MButton *Par);
	void JackControlSlot(MButton * par);
	void InfraredControlSlot(MButton * par);
private:
	MButton *ButtonLamp;											//�ƹ����
	MButton *ButtonJack;											//��������
	MButton *ButtonInfrared;										//�������
	MButton *ButtonSetting;											//����
	LampControl *LampControlWin;									
	JackControl *JackControlWin;				
	static void DesktopCallback(WM_MESSAGE *pMsg);
};



#endif
