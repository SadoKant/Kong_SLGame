#include "SLAIController.h"

void SLAIController::CreateMonster(CharacterType type, Position createdPos)
{
	static int monID = 0;

	SLController::CreateCharacter(type);

	_owner->SetCurrentPosition(createdPos);
	_monsterPool[createdPos] = _owner;

	_owner = nullptr;
}

void SLAIController::DeleteMonster(Position pos)
{
	auto it = _monsterPool.find(pos);
	if (it != _monsterPool.end()) {
		_monsterPool.erase(it);
	}
}

const std::weak_ptr<SLCharacterBase> SLAIController::GetSpecificMon(Position monsPos)
{
	return _monsterPool[monsPos];
}

void SLAIController::ResetMonsters()
{
	_monsterPool.clear();
}
