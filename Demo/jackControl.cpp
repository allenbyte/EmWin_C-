#include "JackControl.h"

#define WIN_BACK_COLOR																							GUI_RGB_COLOR(255,255,255)
#define BUTTON_OFFSET_Y																							24
#define BUTTON_RETURN_UNPRESSURE_BACK_COLOR																		WIN_BACK_COLOR
#define BUTTON_PRESSURE_VALUE																					20
#define BUTTON_RETURN_TEXT																						"Back"
#define BUTTON_RETURN_TEXT_COLOR																				GUI_RGB_COLOR(150,150,150)

JackControl::JackControl(MWidget *hWinParent, int x, int y, int width, int height)
	:MWidget(hWinParent, width, height, x, y),
	ButtonReturn(new MButton(this, 0, 0, 50, 32))
{
	SetBkColor(GUI_RGB_COLOR(255, 255, 255));
	ButtonReturn->SetBkColor(MButton::Unpressed, BUTTON_RETURN_UNPRESSURE_BACK_COLOR);
	ButtonReturn->SetBkColor(MButton::Pressed, MButton::ButtonPressureColor(BUTTON_RETURN_UNPRESSURE_BACK_COLOR));
	ButtonReturn->SetText(BUTTON_RETURN_TEXT);
	ButtonReturn->SetTextColor(MButton::Unpressed, BUTTON_RETURN_TEXT_COLOR);
	ButtonReturn->SetTextColor(MButton::Pressed, BUTTON_RETURN_TEXT_COLOR);
	Show();
	Connect(ButtonReturn, Released, this, &JackControl::ReturnSlot);
}


void JackControl::AddJack(Jack *p)
{
	JackCon.push_back(p);
	int width = (JACK_CONTROL_DEFAULT_WIDTH / JACK_CONTROL_DEFAULT_SWITCH_ROW_UNIT) - JACK_OCNTROL_DEFAULT_SWITCH_ROW_INTERVAL;
	int height = (JACK_CONTROL_DEFAULT_HEIGHT / JACK_CONTROL_DEFAULT_SWITCH_COLUMN_UNIT) - JACK_OCNTROL_DEFAULT_SWITCH_COLUMN_INTERVAL;
	int x = ((JackCon.size() - 1) % JACK_CONTROL_DEFAULT_SWITCH_ROW_UNIT) * (JACK_CONTROL_DEFAULT_WIDTH - JACK_OCNTROL_DEFAULT_SWITCH_ROW_INTERVAL) / JACK_CONTROL_DEFAULT_SWITCH_ROW_UNIT + JACK_OCNTROL_DEFAULT_SWITCH_ROW_INTERVAL;
	int y = ((JackCon.size() - 1) / JACK_CONTROL_DEFAULT_SWITCH_ROW_UNIT) * (JACK_CONTROL_DEFAULT_HEIGHT - JACK_OCNTROL_DEFAULT_SWITCH_COLUMN_INTERVAL) / JACK_CONTROL_DEFAULT_SWITCH_COLUMN_UNIT + JACK_OCNTROL_DEFAULT_SWITCH_COLUMN_INTERVAL + BUTTON_OFFSET_Y;

	MButton *button = new MButton(this, x, y, width, height);
	SwitchButton.push_back(button);

	button->SetBkColor(MButton::ButtonShowConfig::Unpressed, p->Color);
	button->SetBkColor(MButton::ButtonShowConfig::Pressed, MButton::ButtonPressureColor(p->Color));
	std::string *str = new std::string(p->Name);
	if (p->OpenState) *str += "(open)";
	else *str += "(close)";
	button->SetText((char *)str->c_str());

	Connect(button, Released, p, &Jack::ButtonReleasedSolt);
	delete str;
}

void JackControl::ReturnSlot(MButton * par)
{
	Hide();
	for (int i = JackCon.size(); i > 0; i--)
	{
		delete JackCon[i - 1];
	}
	JackCon.clear();
	for (int i = SwitchButton.size(); i > 0; i--)
	{
		delete SwitchButton[i - 1];
	}
	SwitchButton.clear();
}

JackControl::~JackControl(void)
{

}

