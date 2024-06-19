#include <gui/screen1_screen/Screen1View.hpp>

#ifdef SIMULATOR
#include <touchgfx/Utils.hpp>
#else
#include "dbger.h"
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
    LOG_DBG((char*)"clear\n");
    memset(txtResultBuffer, 0, TXTRESULT_SIZE);
    txtResult.invalidate();
#endif
}

void Screen1View::recognize()
{
#ifdef SIMULATOR
    char myStr[] = "ABCDE";
    touchgfx_printf("recognize\n");
    Unicode::strncpy(txtResultBuffer, myStr, TXTRESULT_SIZE);
    txtResult.invalidate();
#else
    LOG_DBG((char*)"recognize\n");
    char myStr[] = "ABCDE";
    Unicode::strncpy(txtResultBuffer, myStr, TXTRESULT_SIZE);
    txtResult.invalidate();
#endif
}