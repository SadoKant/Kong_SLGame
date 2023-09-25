#pragma once
#include "SLController.h"

class SLPlayerController : public SLController
{
public:
	InputType KeyMapping() const;
	char CheckObject(const std::vector<std::string>& targetMap, InputType direction, Position& outObjectPos);
	void Move(int moveX, int moveY);
};
