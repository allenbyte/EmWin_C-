/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2015  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.32 - Graphical user interface for embedded applications **
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only  be used  in accordance  with  a license  and should  not be  re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : GUIDEMO_Start.c
Purpose     : GUIDEMO initialization
----------------------------------------------------------------------
*/

#include "../Application/GUIDEMO.h"
#include "../mygui/mwidget.h"
#include "../mygui/Mtext.h"
#include "MButton.h"
#include "MSlider.h"
#include "HideWidget.h"
#include "MulitButton.h"
#include "../Demo/Desktop.h"

/*********************************************************************
*
*       MainTask
*/

void MainTask(void) {
  #if GUI_WINSUPPORT
    WM_SetCreateFlags(WM_CF_MEMDEV);
  #endif
  GUI_Init();
  #if GUI_WINSUPPORT
    WM_MULTIBUF_Enable(1);
  #endif
	GUI_EnableAlpha(0);
  //GUIDEMO_Main()
	MText *text;
	MText *text2;
	MButton *button;
	MSlider *Slider;
	
	/*text = new MText(MainWindow, 0, 0, 200, 200);
	text2 = new MText(MainWindow, 0, 200, 200, 200);
	button = new MButton(MainWindow, 25, 340, 100, 50);
	Slider = new MSlider(MainWindow, 20, 400);*/
	
	/*//text->SetBackColor(0x80000000);
	text->SetText("test success!!");
	text2->SetText("test success!");
	//text2->SetTextColor(GUI_RGB_COLOR(149, 149, 150));
	text2->TextAutoColor(true);
	button->SetText("Button");*/
	//MHideWidget topsss(0, 0, 0, 800, 20);
	/*MulitButton Mulitbuttontest(MainWindow);
	Mulitbuttontest.SetButtonXSize(1, 150);
	Mulitbuttontest.UpdateWinSize();*/
	Desktop *desktop = new Desktop();
	
	while (1)
	{
		GUI_Exec();
	}
}

/*************************** End of file ****************************/

