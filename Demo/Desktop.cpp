#include "Desktop.h"
#include "../MyGui/MulitButton.h"

#define DESKTOP_WIDTH																				480
#define DESKTOP_HIGH																				272
#define DESKTOP_BACK_COLOR																			0//GUI_RGB_COLOR(0, 150, 250)

#define BUTTON_DEFAULT_COLOR																		GUI_RGB_COLOR(0, 150, 250)
#define BUTTON_DEFAULT_TEXT_COLOR																	GUI_RGB_COLOR(250, 250, 250)
#define BUTTON_LAMP_POS_X																			20
#define BUTTON_LAMP_POS_Y																			20
#define BUTTON_LAMP_WIDTH																			150
#define BUTTON_LAMP_HIGH																			80
#define BUTTON_LAMP_COLOR																			BUTTON_DEFAULT_COLOR
#define BUTTON_LAMP_TEXT																			"Lamp Control"
#define BUTTON_JACK_POS_X																			(20 + BUTTON_LAMP_POS_X + BUTTON_LAMP_WIDTH)
#define BUTTON_JACK_POS_Y																			20//(20 + BUTTON_LAMP_POS_Y + BUTTON_LAMP_HIGH)
#define BUTTON_JACK_WIDTH																			100
#define BUTTON_JACK_HIGH																			50
#define BUTTON_JACK_COLOR																			BUTTON_DEFAULT_COLOR
#define BUTTON_JACK_TEXT																			"Jack Control"
#define BUTTON_INFRARED_POS_X																		(20 + BUTTON_JACK_POS_X + BUTTON_JACK_WIDTH)
#define BUTTON_INFRARED_POS_Y																		20
#define BUTTON_INFRARED_WIDTH																		100
#define BUTTON_INFRARED_HIGH																		50
#define BUTTON_INFRARED_COLOR																		BUTTON_DEFAULT_COLOR
#define BUTTON_INFRARED_TEXT																		"Infrared Control"

#define BUTTON_SETTING_POS_X																		20
#define BUTTON_SETTING_POS_Y																		(20 + BUTTON_LAMP_POS_Y + BUTTON_LAMP_HIGH)
#define BUTTON_SETTING_WIDTH																		100
#define BUTTON_SETTING_HIGH																			50
#define BUTTON_SETTING_COLOR																		BUTTON_DEFAULT_COLOR
#define BUTTON_SETTING_TEXT																			"Setting Control"

static Desktop *mDesktop = 0;

static void DesktopCallback(WM_MESSAGE *pMsg);

Desktop::Desktop(void)
	:MWidget(WM_GetDesktopWindow()),
	ButtonLamp(new MButton(this, BUTTON_LAMP_POS_X, BUTTON_LAMP_POS_Y, BUTTON_LAMP_WIDTH, BUTTON_LAMP_HIGH)),
	ButtonJack(new MButton(this, BUTTON_JACK_POS_X, BUTTON_JACK_POS_Y, BUTTON_JACK_WIDTH, BUTTON_JACK_HIGH)),
	ButtonInfrared(new MButton(this, BUTTON_INFRARED_POS_X, BUTTON_INFRARED_POS_Y, BUTTON_INFRARED_WIDTH, BUTTON_INFRARED_HIGH)),
	ButtonSetting(new MButton(this, BUTTON_SETTING_POS_X, BUTTON_SETTING_POS_Y, BUTTON_SETTING_WIDTH, BUTTON_SETTING_HIGH)),
	LampControlWin(0),
	JackControlWin(0)
{
	mDesktop = this;
	SetCallback(this, DesktopCallback);
	SetBkColor(DESKTOP_BACK_COLOR);
	SetSize(DESKTOP_WIDTH, DESKTOP_HIGH);
	
	ButtonLamp->SetBkColor(MButton::Pressed, MButton::ButtonPressureColor(BUTTON_LAMP_COLOR));
	ButtonLamp->SetBkColor(MButton::Unpressed, BUTTON_LAMP_COLOR);
	ButtonLamp->SetTextColor(MButton::Unpressed, BUTTON_DEFAULT_TEXT_COLOR);
	ButtonLamp->SetTextColor(MButton::Pressed, BUTTON_DEFAULT_TEXT_COLOR);
	ButtonLamp->SetText(BUTTON_LAMP_TEXT);
	Connect(ButtonLamp, Released, this, &Desktop::LampButtonSlot);

	ButtonJack->SetBkColor(MButton::Pressed, MButton::ButtonPressureColor(BUTTON_JACK_COLOR));
	ButtonJack->SetBkColor(MButton::Unpressed, BUTTON_JACK_COLOR);
	ButtonJack->SetTextColor(MButton::Unpressed, BUTTON_DEFAULT_TEXT_COLOR);
	ButtonJack->SetTextColor(MButton::Pressed, BUTTON_DEFAULT_TEXT_COLOR);
	ButtonJack->SetText(BUTTON_JACK_TEXT);
	Connect(ButtonJack, Released, this, &Desktop::JackControlSlot);

	ButtonInfrared->SetBkColor(MButton::Pressed, MButton::ButtonPressureColor(BUTTON_INFRARED_COLOR));
	ButtonInfrared->SetBkColor(MButton::Unpressed, BUTTON_INFRARED_COLOR);
	ButtonInfrared->SetTextColor(MButton::Unpressed, BUTTON_DEFAULT_TEXT_COLOR);
	ButtonInfrared->SetTextColor(MButton::Pressed, BUTTON_DEFAULT_TEXT_COLOR);
	ButtonInfrared->SetText(BUTTON_INFRARED_TEXT);
	Connect(ButtonInfrared, Released, this, &Desktop::InfraredControlSlot);

	ButtonSetting->SetBkColor(MButton::Pressed, MButton::ButtonPressureColor(BUTTON_SETTING_COLOR));
	ButtonSetting->SetBkColor(MButton::Unpressed, BUTTON_SETTING_COLOR);
	ButtonSetting->SetTextColor(MButton::Unpressed, BUTTON_DEFAULT_TEXT_COLOR);
	ButtonSetting->SetTextColor(MButton::Pressed, BUTTON_DEFAULT_TEXT_COLOR);
	ButtonSetting->SetText(BUTTON_SETTING_TEXT);

	MulitButton *Mulitbuttontest = new MulitButton(this);
	Mulitbuttontest->SetButtonXSize(1, 150);
	Mulitbuttontest->UpdateWinSize();
	Show();
}


void Desktop::LampButtonSlot(MButton * Par)
{
	if (LampControlWin == 0)
		LampControlWin = new LampControl(this, 0, 20);
	else
		LampControlWin->Show();
	for (int i = 0; i < 8; i++)
	{
		LampControl::Switch *p = new LampControl::Switch();
		p->Name = "test" + std::to_string(i);
		p->Color = GUI_RGB_COLOR(0, 128, 240);
		
		LampControlWin->AddSwitch(p);
	}
}

void Desktop::JackControlSlot(MButton * par)
{
	if (JackControlWin == 0)
		JackControlWin = new JackControl(this, 0, 20);
	else
		JackControlWin->Show();
	for (int i = 0; i < 8; i++)
	{
		JackControl::Jack *p = new JackControl::Jack();
		p->Name = "test" + std::to_string(i);
		p->Color = GUI_RGB_COLOR(0, 128, 240);

		JackControlWin->AddJack(p);
	}
}

void Desktop::InfraredControlSlot(MButton * par)
{
	
}




void Desktop::DesktopCallback(WM_MESSAGE *pMsg)
{
	if (mDesktop != 0)
	{
		mDesktop->Callback(pMsg);
	}
}

Desktop::~Desktop(void)
{
	delete ButtonLamp;
	delete ButtonJack;
	delete ButtonInfrared;
	delete ButtonSetting;
}


