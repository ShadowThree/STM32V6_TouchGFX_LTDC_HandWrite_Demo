#include <gui/screen1_screen/Screen1View.hpp>

#ifdef SIMULATOR
#include <touchgfx/Utils.hpp>
#else
#include "main.h"
#include "string.h"
//#include "dbger.h"
#include "cmsis_os2.h"
#include "atk_ncr.h"
extern osEventFlagsId_t eventProcessHandle;
#endif

Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::clear()
{
#ifdef SIMULATOR
    touchgfx_printf("clear\n");
    memset(txtResultBuffer, 0, TXTRESULT_SIZE);
    txtResult.invalidate();
#else
    memset((void*)LTDC_L1_ADDR, 0xFF, LTDC_L1_WIDTH * LTDC_L1_HEIGHT * 2);
		point_num = 0;
#endif
}

void Screen1View::recognize()
{
#ifdef SIMULATOR
    char myStr[] = "ABCDEF";
    touchgfx_printf("recognize\n");
    Unicode::strncpy(txtResultBuffer, myStr, TXTRESULT_SIZE);
    txtResult.invalidate();
#else
		//LOG_DBG((char*)"recognize\n");
		btnRecognize.setTouchable(false);
		osEventFlagsSet(eventProcessHandle, EVT_RECOGNIZE);
#endif
}

void Screen1View::showResult(char* result)
{
#ifndef SIMULATOR
	//LOG_DBG((char*)"view showResult: %s\n", result);
	Unicode::strncpy(txtResultBuffer, result, TXTRESULT_SIZE);
	txtResult.invalidate();
	memset(result, 0, CHAR_NUM + 1);
	btnRecognize.setTouchable(true);
#endif
}