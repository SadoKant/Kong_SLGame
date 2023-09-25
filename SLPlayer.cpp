#include "SLPlayer.h"

#include "SLGameSystem.h"
#include "SLItemBase.h"

SLPlayer::SLPlayer(CharacterType jobType)
	:SLCharacterBase(jobType)
{
	InitSkillList(jobType);
	InitStartItem();
}

std::shared_ptr<SLSkillBase> SLPlayer::GetSkillAtList(int index)
{
	if (index >= 0 && index < _skillList.size()) {
		return _skillList[index];
	}

	return nullptr;
}

void SLPlayer::AddNewItem(const ItemInfo& newItemInfo)
{
	_inventory[_inventory.size()] = std::make_shared<SLItemBase>(newItemInfo);
	if (newItemInfo._type == ItemType::Equip) {

		SLDrawManager& drawManager = SLDrawManager::GetDrawManager();
		std::string itemGetStr = "야호! " + newItemInfo._name + "를 손에 넣었다!!!";
		drawManager.DrawNewDialogue(itemGetStr);

		for (const auto& pair : newItemInfo._spec) {
			StatType type = pair.first;
			int value = pair.second;

			switch (type)
			{
			case StatType::HP_Max:
				ChangeStat(type, _characterStat._HP_Max + value);
				break;
			case StatType::MP_Max:
				ChangeStat(type, _characterStat._MP_Max + value);
				break;
			case StatType::ATK:
				ChangeStat(type, _characterStat._ATK + value);
				break;
			case StatType::DEF:
				ChangeStat(type, _characterStat._DEF + value);
				break;
			default:
				break;
			}
		}
	}
}

bool SLPlayer::UseItem(int itemIndex)
{
	auto foundItem = _inventory.find(itemIndex);
	if (foundItem != _inventory.end()) {
		if (foundItem->second->ConsumeItem() == false) {
			return false;
		}

		SLDrawManager& drawManager = SLDrawManager::GetDrawManager();
		
		std::map<StatType, int> itemEffect = foundItem->second->GetInfo()._spec;
		for (const auto& pair : itemEffect) {
			StatType type = pair.first;
			int value = pair.second;

			std::string effectStr;

			switch (type)
			{
			case StatType::HP:
				ChangeStat(type, _characterStat._HP + value);
				effectStr = "체력을 " + std::to_string(value) + "만큼 회복했다!";
				break;
			case StatType::MP:
				ChangeStat(type, _characterStat._MP + value);
				effectStr = "마나를 " + std::to_string(value) + "만큼 회복했다!";
				break;
			case StatType::ATK:
				break;
			case StatType::DEF:
				break;
			default:
				break;
			}
			drawManager.DrawNewDialogue(effectStr);
		}

		if (foundItem->second->GetInfo()._count == 0) {
			_inventory.erase(foundItem);
		}
	}
	else {
		return false;
	}

	return true;
}

void SLPlayer::Dead()
{
	SLGameSystem::GetGameSystem().End();
}

void SLPlayer::InitSkillList(CharacterType jobType)
{
	switch (jobType)
	{
	case CharacterType::Warrior:
	{
		std::shared_ptr<SLSkillBase> skillTemp = std::make_shared<SLSkillBase>(SkillData_Warrior::_skillFirst);
		_skillList.push_back(skillTemp);

		skillTemp = std::make_shared<SLSkillBase>(SkillData_Warrior::_skillSecond);
		_skillList.push_back(skillTemp);

		skillTemp = std::make_shared<SLSkillBase>(SkillData_Warrior::_skillThird);
		_skillList.push_back(skillTemp);

		break;
	}
	case CharacterType::Thief:
	{
		std::shared_ptr<SLSkillBase> skillTemp = std::make_shared<SLSkillBase>(SkillData_Thief::_skillFirst);
		_skillList.push_back(skillTemp);

		skillTemp = std::make_shared<SLSkillBase>(SkillData_Thief::_skillSecond);
		_skillList.push_back(skillTemp);

		skillTemp = std::make_shared<SLSkillBase>(SkillData_Thief::_skillThird);
		_skillList.push_back(skillTemp);

		break;
	}
	case CharacterType::Mage:
	{
		std::shared_ptr<SLSkillBase> skillTemp = std::make_shared<SLSkillBase>(SkillData_Mage::_skillFirst);
		_skillList.push_back(skillTemp);

		skillTemp = std::make_shared<SLSkillBase>(SkillData_Mage::_skillSecond);
		_skillList.push_back(skillTemp);

		skillTemp = std::make_shared<SLSkillBase>(SkillData_Mage::_skillThird);
		_skillList.push_back(skillTemp);

		break;
	}
	default:
		break;
	}
}

void SLPlayer::InitStartItem()
{
	std::map<StatType, int> Itemspec;

	Itemspec[StatType::HP] = 100;
	ItemInfo hpPotion(ItemType::Consume, 1, Itemspec, "체력 포션", "HP 100 회복");

	Itemspec.clear();
	Itemspec[StatType::MP] = 10;
	ItemInfo mpPotion(ItemType::Consume, 1, Itemspec, "마나 포션", "MP 10 회복");

	AddNewItem(hpPotion);
	AddNewItem(mpPotion);
}
