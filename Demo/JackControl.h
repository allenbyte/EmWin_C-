#ifndef _JACKCONTROL_H_
#define _JACKCONTROL_H_

#include <string>
#include <vector>
#include "../MyGui/MWidget.h"
#include "../MyGui/MButton.h"

#define JACK_CONTROL_DEFAULT_WIDTH																	480
#define JACK_CONTROL_DEFAULT_HEIGHT																	272
#define JACK_CONTROL_DEFAULT_SWITCH_ROW_UNIT														4
#define JACK_CONTROL_DEFAULT_SWITCH_COLUMN_UNIT														5
#define JACK_OCNTROL_DEFAULT_SWITCH_ROW_INTERVAL													20
#define JACK_OCNTROL_DEFAULT_SWITCH_COLUMN_INTERVAL													10

class JackControl : protected MWidget{
public:
	class Jack
	{
	public:
		Jack(std::string name = " ", GUI_COLOR color = MBUTTON_DEFAULT_UNPRESSED_BACK_COLOR, void(*Control)(bool) = 0, bool state = false)
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
	JackControl(MWidget *hWinParent, int x, int y, int width = JACK_CONTROL_DEFAULT_WIDTH, int height = JACK_CONTROL_DEFAULT_HEIGHT);
	~JackControl(void);
	void AddJack(Jack *p);
	void Show(){ MWidget::Show(); }

private:
	//slot
	void ReturnSlot(MButton * par);
private:
	vector <Jack *> JackCon;
	vector <MButton *> SwitchButton;
	MButton *ButtonReturn;
};


#endif
