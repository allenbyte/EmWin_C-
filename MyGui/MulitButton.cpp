#include "MulitButton.h"

MulitButton::MulitButton(MWidget *Parent, int number, int x, int y, int Buttonwidth, int Buttonhigh)
:MHideWidget(Parent, x, y, number * Buttonwidth, Buttonhigh)
{
	for (int i = 0; i < number; i++)
	{
		Button.push_back(new MButton(this, i * Buttonwidth, 0, Buttonwidth, Buttonhigh));
	}
	Button[0]->SetText("Button0");
	Button[1]->SetText("button1");
	Button[2]->SetText("Button2");

	
}

void MulitButton::SetButtonXSize(int num, int x)
{
	Button[num]->SetXSize(x);
	
}


void MulitButton::UpdateWinSize(void)
{
	int wsize = 0, hsize = 0, num = Button.size();
	for (int i = 0; i < num; i++)
	{
		wsize += Button[i]->GetWindowSizeX();
	}
	for (int i = 0; i < num; i ++)
	{
		int tmp;
		tmp = Button[i]->GetWindowSizeY();
		if (hsize < tmp)
			hsize = tmp;
	}
	SetSize(wsize, hsize);
	//ÐÞ¸Ä°´Å¥Î»ÖÃ
	{
		int x = Button[0]->GetWindowSizeX(), width;
		for (int i = 1; i < num; i++)
		{
			width = Button[i]->GetWindowSizeX();
			Button[i]->SetPos(x, 0, width, hsize);
			x += width;
		}
	}
	
	
}

MulitButton::~MulitButton(void)
{
	Button.clear();
	//MulitButton::BroadcastMessage((WM_MESSAGE *)0);
}

