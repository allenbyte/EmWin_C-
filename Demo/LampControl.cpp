#include "LampControl.h"

#define WIN_BACK_COLOR																							GUI_RGB_COLOR(255,255,255)
#define BUTTON_OFFSET_Y																							24
#define BUTTON_RETURN_UNPRESSURE_BACK_COLOR																		WIN_BACK_COLOR
#define BUTTON_PRESSURE_VALUE																					20
#define BUTTON_RETURN_TEXT																						"Back"
#define BUTTON_RETURN_TEXT_COLOR																				GUI_RGB_COLOR(150,150,150)

LampControl::LampControl(MWidget *hWinParent, int x, int y, int width, int height)
	:MWidget(hWinParent, width, height, x, y),
	ButtonReturn(new MButton(this, 0, 0, 50, 32))
{
	SetBkColor(GUI_RGB_COLOR(255,255,255));
	ButtonReturn->SetBkColor(MButton::Unpressed, BUTTON_RETURN_UNPRESSURE_BACK_COLOR);
	ButtonReturn->SetBkColor(MButton::Pressed, MButton::ButtonPressureColor(BUTTON_RETURN_UNPRESSURE_BACK_COLOR));
	ButtonReturn->SetText(BUTTON_RETURN_TEXT);
	ButtonReturn->SetTextColor(MButton::Unpressed, BUTTON_RETURN_TEXT_COLOR);
	ButtonReturn->SetTextColor(MButton::Pressed, BUTTON_RETURN_TEXT_COLOR);
	Show();
	Connect(ButtonReturn, Released, this, &LampControl::ReturnSlot);
}


void LampControl::AddSwitch(Switch *p)
{
	SwitchCon.push_back(p);
	int width = (LAMP_CONTROL_DEFAULT_WIDTH / LAMP_CONTROL_DEFAULT_SWITCH_ROW_UNIT) - LAMP_OCNTROL_DEFAULT_SWITCH_ROW_INTERVAL;
	int height = (LAMP_CONTROL_DEFAULT_HEIGHT / LAMP_CONTROL_DEFAULT_SWITCH_COLUMN_UNIT) - LAMP_OCNTROL_DEFAULT_SWITCH_COLUMN_INTERVAL;
	int x = ((SwitchCon.size() - 1) % LAMP_CONTROL_DEFAULT_SWITCH_ROW_UNIT) * (LAMP_CONTROL_DEFAULT_WIDTH - LAMP_OCNTROL_DEFAULT_SWITCH_ROW_INTERVAL) / LAMP_CONTROL_DEFAULT_SWITCH_ROW_UNIT + LAMP_OCNTROL_DEFAULT_SWITCH_ROW_INTERVAL;
	int y = ((SwitchCon.size() - 1) / LAMP_CONTROL_DEFAULT_SWITCH_ROW_UNIT) * (LAMP_CONTROL_DEFAULT_HEIGHT - LAMP_OCNTROL_DEFAULT_SWITCH_COLUMN_INTERVAL) / LAMP_CONTROL_DEFAULT_SWITCH_COLUMN_UNIT + LAMP_OCNTROL_DEFAULT_SWITCH_COLUMN_INTERVAL + BUTTON_OFFSET_Y;
	
	MButton *button = new MButton(this, x, y, width, height);
	SwitchButton.push_back(button);
	
	button->SetBkColor(MButton::ButtonShowConfig::Unpressed, p->Color);
	button->SetBkColor(MButton::ButtonShowConfig::Pressed, MButton::ButtonPressureColor(p->Color));
	std::string *str = new std::string(p->Name);
	if (p->OpenState) *str += "(open)";
	else *str += "(close)";
	button->SetText((char *)str->c_str());
	
	Connect(button, Released, p, &Switch::ButtonReleasedSolt);
	delete str;
}

void LampControl::ReturnSlot(MButton * par)
{
	Hide();
	for (int i = SwitchCon.size(); i > 0; i--)
	{
		delete SwitchCon[i - 1];
	}
	SwitchCon.clear();
	for (int i = SwitchButton.size(); i > 0; i--)
	{
		delete SwitchButton[i - 1];
	}
	SwitchButton.clear();
}

LampControl::~LampControl(void)
{
	
}

