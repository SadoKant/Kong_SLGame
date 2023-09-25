#include "SLController.h"

#include "SLCommonDefine.h"

#include "SLPlayer.h"

SLController::~SLController()
{
	_owner = nullptr;
}

void SLController::CreateCharacter(CharacterType type)
{
	switch (type)
	{
	case CharacterType::None:
		break;
	case CharacterType::Warrior:
	case CharacterType::Thief:
	case CharacterType::Mage:
		_owner = std::make_shared<SLPlayer>(type);
		break;
	case CharacterType::LowMon:
	case CharacterType::MidMon:
	case CharacterType::Boss:
		_owner = std::make_shared<SLCharacterBase>(type);
		break;
	default:
		break;
	}
}

const std::weak_ptr<SLCharacterBase>& SLController::GetOwner() const
{
	return _owner;
}

