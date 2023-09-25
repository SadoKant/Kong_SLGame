#pragma once

#include <string>
#include <memory>
#include <map>

#include "SLCommonDefine.h"
#include "SLGameData.h"
#include "SLItemBase.h"

struct Position
{
	Position() : x(0), y(0) { };
	Position(int x, int y) : x(x), y(y) { };

	bool operator==(const Position& otherPos) const
	{
		if (this->x == otherPos.x && this->y == otherPos.y) return true;
		else return false;
	}

	struct HashFunction
	{
		size_t operator()(const Position& pos) const
		{
			size_t xHash = std::hash<int>()(pos.x);
			size_t yHash = std::hash<int>()(pos.y) << 1;
			return xHash ^ yHash;
		}
	};

	int x = 0;
	int y = 0;
};

class SLCharacterBase : public std::enable_shared_from_this<SLCharacterBase>
{
public:
	SLCharacterBase(CharacterType type);

public:
	const Position& GetCurrentPosition() { return _currentPos; };
	void SetCurrentPosition(Position pos) { _currentPos = pos; };

	CharacterType GetCharacterType() { return _characterType; };

	CharacterBasicStat& GetStat() { return _characterStat; };
	void ChangeStat(StatType statType, int value);

	const std::string& GetName() { return _name; };

	bool IsDead() { return _characterStat._HP <= 0; };
	virtual void Dead();

	const std::map<SkillType, std::vector<int>>& GetBuffList() { return _buffList; };
	void AddBuffAtList(SkillBasicInfo skillInfo);
	void UpdateBuffDuration(const CharacterBasicStat& originStat);
	void RemoveAllBuff(const CharacterBasicStat& originStat);

	void SetHasLegendaryWeapon(bool yaHoo) { bHasLegendaryWeapon = yaHoo; };
	bool GetHasLegendaryWeapon() { return bHasLegendaryWeapon; };

protected:
	Position _currentPos;
	CharacterType _characterType;
	CharacterBasicStat _characterStat;
	std::string _name;
	std::map<SkillType, std::vector<int>> _buffList;

	bool bHasLegendaryWeapon = false;
};

