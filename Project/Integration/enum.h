#pragma once
#include <string>
#ifndef  _ENUM_
#define _ENUM_

enum ProcessState
{
	NEW,
	RDY,
	RUN,
	BLK,
	TRM,
	ORPH
};

struct IO
{
	int IO_R, IO_D;
};

struct SIGKILL
{
	int killTime, killID;
};

enum Mode
{
	InteractiveMode,  //phase 1
	StepByStep, //phase 2
	SilentMode  //phase 2
};

#endif 