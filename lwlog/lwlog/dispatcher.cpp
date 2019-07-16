#include "dispatcher.h"

void dispatcher::dispatch(std::string message)
{
	lwlog::print("{0} \n", message);
}
