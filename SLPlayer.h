#pragma once

#include <memory>
#include <vector>

#include "SLCharacterBase.h"
#include "SLSkillBase.h"

class SLItemBase;

class SLPlayer : public SLCharacterBase
{
public:
	SLPlayer(CharacterType jobType);

public:
	std::shared_ptr<SLSkillBase> GetSkillAtList(int index);
	std::map<int, std::shared_ptr<SLItemBase>>& GetInventory() { return _inventory; };

	void AddNewItem(const ItemInfo& newItemInfo);
	bool UseItem(int itemIndex);

	virtual void Dead() override;

private:
	void InitSkillList(CharacterType jobType);
	void InitStartItem();

private:
	std::vector<std::shared_ptr<SLSkillBase>> _skillList;
	std::map<int, std::shared_ptr<SLItemBase>> _inventory;
};
