#ifndef _LAMP_CONTROL_H_
#define _LAMP_CONTROL_H_

#include <string>
#include <vector>
#include "../MyGui/MWidget.h"
#include "../MyGui/MButton.h"

#define LAMP_CONTROL_DEFAULT_WIDTH																	480
#define LAMP_CONTROL_DEFAULT_HEIGHT																	272
#define LAMP_CONTROL_DEFAULT_SWITCH_ROW_UNIT														4
#define LAMP_CONTROL_DEFAULT_SWITCH_COLUMN_UNIT														5
#define LAMP_OCNTROL_DEFAULT_SWITCH_ROW_INTERVAL													20
#define LAMP_OCNTROL_DEFAULT_SWITCH_COLUMN_INTERVAL													10

class LampControl : protected MWidget{
public:
	class Switch
	{
	public:
		Switch(std::string name = " ", GUI_COLOR color = MBUTTON_DEFAULT_UNPRESSED_BACK_COLOR, void(*Control)(bool) = 0, bool state = false)
			:Name(name),
			OpenState(state),
			Color(color),
			Control(0)
		{
			
		}
		std::string Name;
		bool OpenState;
		GUI_COLOR Color;
		void(*Control)(bool Open);
	//Solt
		void ButtonReleasedSolt(MButton *p)
		{
			OpenState = !OpenState;
			std::string *str = new std::string(Name);
			if (OpenState) *str += "(open)";
			else *str += "(close)";
			p->SetText((char *)str->c_str());
			if (Control != 0)
				Control(OpenState);
			delete str;
		}
	};
	
public:
	LampControl(MWidget *hWinParent, int x, int y, int width = LAMP_CONTROL_DEFAULT_WIDTH, int height = LAMP_CONTROL_DEFAULT_HEIGHT);
	~LampControl(void);
	void AddSwitch(Switch *p);
	void Show(){ MWidget::Show(); }
	

private:
	//slot
	void ReturnSlot(MButton * par);
private:
	vector <Switch *> SwitchCon;
	vector <MButton *> SwitchButton;
	MButton *ButtonReturn;
};



#endif
