#pragma once

#include <memory>
#include <string>

#include "SLCommonDefine.h"
#include "SLGameData.h"

class SLCharacterBase;
class SLPlayer;

class SLBattleSystem
{
public:
	static SLBattleSystem& GetBattleSystem();
	bool StartBattle(std::weak_ptr<SLCharacterBase> player, std::weak_ptr<SLCharacterBase> monster);
	bool ActionAttack(std::weak_ptr<SLCharacterBase> attacker, std::weak_ptr<SLCharacterBase> defender, int damage = 0, bool bIgnoreDEF = false);

private:
	BattleActionType DrawBattleMenu();

	bool BattleAction(BattleActionType action, std::weak_ptr<SLCharacterBase> attacker, std::weak_ptr<SLCharacterBase> defender);
	bool SelectSkill(std::weak_ptr<SLCharacterBase> player, std::weak_ptr<SLCharacterBase> monster);
	bool SelectItem(std::weak_ptr<SLCharacterBase> player, std::weak_ptr<SLCharacterBase> monster);
	
	void CachePlayerStatBeforeBattle(std::weak_ptr<SLCharacterBase> player);
	void ApplyBuff(std::weak_ptr<SLCharacterBase> player);
	int DamageCalculate(int damage, int DEF, bool bIgnoreDEF = false);

	void DrawMonsterStat(std::weak_ptr<SLCharacterBase> monster);
	void EraseBattleUI();

	void DrawBattleDialogue(const std::string& text);

private:
	CharacterBasicStat _BeforeBattleStat;

	int _maxTurn = 1;
	int _remainTurn = 0;

	const int _battleUICol = 78;
	const int _battleUIRow = 10;

	const int _skillUIOffset = 7;
};

