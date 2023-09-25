#include "SLBattleSystem.h"

#include <windows.h>

#include "SLDrawManager.h"
#include "SLCharacterBase.h"
#include "SLPlayer.h"

SLBattleSystem& SLBattleSystem::GetBattleSystem()
{
	static SLBattleSystem battleSystem;
	return battleSystem;
}

bool SLBattleSystem::StartBattle(std::weak_ptr<SLCharacterBase> player, std::weak_ptr<SLCharacterBase> monster)
{
	std::shared_ptr<SLPlayer> lPlayer = std::dynamic_pointer_cast<SLPlayer>(player.lock());
	std::shared_ptr<SLCharacterBase> lMonster = monster.lock();

	if (lPlayer->GetCharacterType() == CharacterType::Thief) {
		_maxTurn = 2;
	}

	_remainTurn = _maxTurn;

	std::string text = "'" + monster.lock()->GetName() + "'" + "와 마주쳤다!";
	DrawBattleDialogue(text);
	DrawMonsterStat(monster);
	
	CachePlayerStatBeforeBattle(player);

	while (true) {
		if (_remainTurn) {
			BattleActionType selectedAction = DrawBattleMenu();
			bool bSuccessAction = BattleAction(selectedAction, lPlayer, lMonster);
			if (bSuccessAction == true) {
				_remainTurn--;
			}
		}
		else {
			Sleep(500);
			bool bSuccessAction = BattleAction(BattleActionType::Attack, lMonster, lPlayer);
			if (bSuccessAction == true) {
				_remainTurn = _maxTurn;
				lPlayer->UpdateBuffDuration(_BeforeBattleStat);
			}
		}

		EraseBattleUI();

		if (lPlayer->IsDead() || lMonster->IsDead()) {
			lPlayer->RemoveAllBuff(_BeforeBattleStat);
			break;
		}
	}

	EraseBattleUI();

	return true;
}

bool SLBattleSystem::ActionAttack(std::weak_ptr<SLCharacterBase> attacker, std::weak_ptr<SLCharacterBase> defender, int damage /* = 0 */, bool bIgnoreDEF /* = false */)
{
	std::shared_ptr<SLCharacterBase> lPlayer = nullptr;
	std::shared_ptr<SLCharacterBase> lMonster = nullptr;

	if (static_cast<int>(attacker.lock()->GetCharacterType()) < 10) {
		lPlayer = attacker.lock();
		lMonster = defender.lock();
	}
	else {
		lPlayer = defender.lock();
		lMonster = attacker.lock();
	}

	if (attacker.lock()->GetCharacterType() == CharacterType::Mage) {
		bIgnoreDEF = true;
	}

	const CharacterBasicStat& attackerStat = attacker.lock()->GetStat();
	const CharacterBasicStat& defenderStat = defender.lock()->GetStat();

	if (damage == 0) {
		damage = DamageCalculate(attackerStat._ATK, defenderStat._DEF, bIgnoreDEF);
	}
	else {
		damage = DamageCalculate(damage, defenderStat._DEF, bIgnoreDEF);
	}

	defender.lock()->ChangeStat(StatType::HP, defenderStat ._HP -1 * damage);
	bool bBattleEnd = defender.lock()->IsDead();

	std::string attackStr;
	if (_remainTurn) {
		if (damage == 0) {
			attackStr = "이런! 아무런 피해를 입히지 못했다..";
		}
		else {
			attackStr = "'" + lMonster->GetName() + "'에게 '" + std::to_string(damage) + "' 만큼의 피해를 입혔다!";
		}
	}
	else {
		if (damage == 0) {
			attackStr = "와우! 아무런 피해를 입지 않았다!";
		}
		else {
			attackStr = "'" + lMonster->GetName() + "'에게 '" + std::to_string(damage) + "'의 피해를 입었다..";
		}
	}

	DrawBattleDialogue(attackStr);

	if (bBattleEnd) {
		if (_remainTurn) {
			std::string battleResultStr = "'" + lMonster->GetName() + "'를 쓰러뜨렸다!!!";
			Sleep(500);
			lMonster->Dead();

			if (defender.lock()->GetCharacterType() != CharacterType::Boss) {
				DrawBattleDialogue(battleResultStr);
			}
		}
		else {
			lPlayer->Dead();
		}
	}

	return true;
}

BattleActionType SLBattleSystem::DrawBattleMenu()
{
	SLDrawManager& drawmanager = SLDrawManager::GetDrawManager();
	drawmanager.SetColor(TextColor::White, TextColor::Black);

	int uiStartCol = _battleUICol;
	int uiStartRow = _battleUIRow;
	int menuCount = 3;

	drawmanager.DrawTextAtPosition("> 공격", uiStartCol - 1, uiStartRow);
	drawmanager.DrawTextAtPosition(" 스킬", uiStartCol, uiStartRow + 1);
	drawmanager.DrawTextAtPosition(" 아이템", uiStartCol, uiStartRow + 2);

	int selectedRow = drawmanager.MenuSelect(uiStartCol, uiStartRow, menuCount);

	return static_cast<BattleActionType>(selectedRow + 1);
}

bool SLBattleSystem::BattleAction(BattleActionType action, std::weak_ptr<SLCharacterBase> attacker, std::weak_ptr<SLCharacterBase> defender)
{
	bool bSuccessAction = false;

	switch (action)
	{
	case BattleActionType::None:
		break;
	case BattleActionType::Attack:
		bSuccessAction = ActionAttack(attacker, defender);
		break;
	case BattleActionType::Skill:
		bSuccessAction = SelectSkill(attacker, defender);
		break;
	case BattleActionType::Item:
		bSuccessAction = SelectItem(attacker, defender);
		break;
	default:
		break;
	}

	return bSuccessAction;
}

bool SLBattleSystem::SelectSkill(std::weak_ptr<SLCharacterBase> player, std::weak_ptr<SLCharacterBase> monster)
{
	std::shared_ptr<SLPlayer> lPlayer = std::dynamic_pointer_cast<SLPlayer>(player.lock());

	SLDrawManager& drawmanager = SLDrawManager::GetDrawManager();
	drawmanager.SetColor(TextColor::White, TextColor::Black);

	int uiStartCol = _battleUICol;
	int uiStartRow = _battleUIRow + _skillUIOffset;
	int menuCount = 3;

	SkillBasicInfo skillInfo = lPlayer->GetSkillAtList(0)->GetSkillInfo();

	drawmanager.DrawTextAtPosition(" MP  이름    효과", uiStartCol, uiStartRow - 2);
	
	std::string digitBuffer;
	skillInfo._cost < 10 ? digitBuffer = "  " : digitBuffer = " ";

	std::string skillInfoStr = ">" + digitBuffer + std::to_string(skillInfo._cost) + "  " + skillInfo._name + "  " + skillInfo._desc;
	drawmanager.DrawTextAtPosition(skillInfoStr, uiStartCol - 1, uiStartRow);

	skillInfo = lPlayer->GetSkillAtList(1)->GetSkillInfo();
	skillInfo._cost < 10 ? digitBuffer = "  " : digitBuffer = " ";
	skillInfoStr = digitBuffer + std::to_string(skillInfo._cost) + "  " + skillInfo._name + "  " + skillInfo._desc;
	drawmanager.DrawTextAtPosition(skillInfoStr, uiStartCol, uiStartRow + 1);

	skillInfo = lPlayer->GetSkillAtList(2)->GetSkillInfo();
	skillInfo._cost < 10 ? digitBuffer = "  " : digitBuffer = " ";
	skillInfoStr = digitBuffer + std::to_string(skillInfo._cost) + "  " + skillInfo._name + "  " + skillInfo._desc;
	drawmanager.DrawTextAtPosition(skillInfoStr, uiStartCol, uiStartRow + 2);

	int selectedRow = drawmanager.MenuSelect(uiStartCol, uiStartRow, menuCount);
	
	bool bSuccessSkillCast = lPlayer->GetSkillAtList(selectedRow)->Effect(lPlayer, monster.lock());

	ApplyBuff(lPlayer);

	return bSuccessSkillCast;
}

bool SLBattleSystem::SelectItem(std::weak_ptr<SLCharacterBase> player, std::weak_ptr<SLCharacterBase> monster)
{
	std::shared_ptr<SLPlayer> lPlayer = std::dynamic_pointer_cast<SLPlayer>(player.lock());

	SLDrawManager& drawmanager = SLDrawManager::GetDrawManager();
	drawmanager.SetColor(TextColor::White, TextColor::Black);

	int uiStartCol = _battleUICol;
	int uiStartRow = _battleUIRow + _skillUIOffset;

	drawmanager.DrawTextAtPosition(" 보유  이름       효과", uiStartCol, uiStartRow - 2);

	std::map<int, std::shared_ptr<SLItemBase>>& inventory = lPlayer->GetInventory();

	int itemCount = 0;
	std::string itemInfoStr;
	std::string digitBuffer;
	
	for (const auto& pair : inventory) {
		const ItemInfo& itemInfo = pair.second->GetInfo();
		if (itemInfo._type == ItemType::Consume) {
			if (itemCount == 0) {
				itemInfoStr += ">";
				uiStartCol = _battleUICol - 1;
			}
			else {
				uiStartCol = _battleUICol;
			}

			itemInfo._count < 10 ? digitBuffer = "    " : digitBuffer = "   ";

			itemInfoStr += digitBuffer + std::to_string(itemInfo._count) + "  " + itemInfo._name + "  " + itemInfo._desc;
			drawmanager.DrawTextAtPosition(itemInfoStr, uiStartCol, uiStartRow + itemCount);
			itemInfoStr = "";

			itemCount++;
		}
	}

	if (itemCount == 0) {
		drawmanager.DrawNewDialogue("사용 가능한 아이템이 없다!");
		return false;
	}

	int selectedRow = drawmanager.MenuSelect(uiStartCol, uiStartRow, itemCount);
	lPlayer->UseItem(selectedRow);

	return true;
}

void SLBattleSystem::CachePlayerStatBeforeBattle(std::weak_ptr<SLCharacterBase> player)
{
	_BeforeBattleStat = player.lock()->GetStat();
}

void SLBattleSystem::ApplyBuff(std::weak_ptr<SLCharacterBase> player)
{
	std::shared_ptr<SLPlayer> lPlayer = std::dynamic_pointer_cast<SLPlayer>(player.lock());

	std::map<SkillType, std::vector<int>> buffList = lPlayer->GetBuffList();
	for (auto it = buffList.begin(); it != buffList.end(); it++) {
		switch (it->first)
		{
		case SkillType::None:
			break;
		case SkillType::Buff_DEF:
			lPlayer->ChangeStat(StatType::DEF, _BeforeBattleStat._DEF + it->second[0]);
			break;
		case SkillType::Buff_DamageImmune:
			lPlayer->ChangeStat(StatType::DEF, 999);
			break;
		default:
			break;
		}
	}
}

int SLBattleSystem::DamageCalculate(int damage, int DEF, bool bIgnoreDEF /* = false */)
{
	if (bIgnoreDEF == true) {
		return damage;
	}

	if (damage > DEF) {
		return damage - DEF;
	}
	else {
		return 0;
	}
}

void SLBattleSystem::DrawMonsterStat(std::weak_ptr<SLCharacterBase> monster)
{
	SLDrawManager& drawmanager = SLDrawManager::GetDrawManager();

	drawmanager.RefreshCharacterStat(monster.lock());
}

void SLBattleSystem::EraseBattleUI()
{
	SLDrawManager& drawmanager = SLDrawManager::GetDrawManager();

	drawmanager.EraseTextAtPosition(_battleUICol - 1, _battleUIRow, 40, 20);
}

void SLBattleSystem::DrawBattleDialogue(const std::string& text)
{
	SLDrawManager& drawmanager = SLDrawManager::GetDrawManager();
	drawmanager.DrawNewDialogue(text);
}
