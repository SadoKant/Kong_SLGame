#pragma once

#include <unordered_map>

#include "SLController.h"
#include "SLCharacterBase.h"

class SLAIController : public SLController
{
public:
	void CreateMonster(CharacterType type, Position createdPos);
	void DeleteMonster(Position pos);
	const std::weak_ptr<SLCharacterBase> GetSpecificMon(Position monsPos);
	void ResetMonsters();

private:
	std::unordered_map<Position, std::shared_ptr<SLCharacterBase>, Position::HashFunction> _monsterPool;
};
