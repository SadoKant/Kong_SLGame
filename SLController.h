#pragma once

#include <memory>
#include <vector>
#include <string>

#include "SLCommonDefine.h"
#include "SLCharacterBase.h"

class SLCharacterBase;

class SLController
{
public:
	~SLController();

public:
	void CreateCharacter(CharacterType type);
	const std::weak_ptr<SLCharacterBase>& GetOwner() const;

protected:
	std::shared_ptr<SLCharacterBase> _owner;
};
