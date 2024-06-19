#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#ifndef SIMULATOR
#include "atk_ncr.h"
extern volatile uint8_t recognize_finish;
extern char result[CHAR_NUM+1];
#endif

Model::Model() : modelListener(0)
{

}

void Model::tick()
{
#ifndef SIMULATOR
	if(recognize_finish) {
		recognize_finish = 0;
		modelListener->showResult(result);
	}
#endif
}
