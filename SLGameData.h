#pragma once

#include <vector>

#include "SLSkillBase.h"

struct CharacterBasicStat
{
	CharacterBasicStat();
	CharacterBasicStat(int HP, int MP, int ATK, int DEF);

	int _HP = 0;
	int _HP_Max = 0;

	int _MP = 0;
	int _MP_Max = 0;

	int _ATK = 0;
	int _DEF = 0;
};

namespace BasicStatData
{
	// Player Chracter
	static const CharacterBasicStat _warriorBasicStat = {
		50, 20, 10, 7
	};

	static const CharacterBasicStat _thiefBasicStat = {
		30, 30, 8, 5
	};

	static const CharacterBasicStat _mageBasicStat = {
		10, 60, 5, 2
	};

	// Monster
	static const CharacterBasicStat _lowMonStat = {
		20, 10, 10, 2
	};

	static const CharacterBasicStat _midMonStat = {
		30, 20, 20, 5
	};

	static const CharacterBasicStat _bossMonStat = {
		60, 60, 30, 10
	};
}

namespace SkillData_Warrior
{
	static const SkillBasicInfo _skillFirst = {
		"스매시",
		"20의 데미지를 줌",
		SkillType::Damage,
		5,
		20,
		0,
	};

	static const SkillBasicInfo _skillSecond = {
		"버티기",
		"3턴간 방어력 20 증가",
		SkillType::Buff_DEF,
		5,
		20,
		3,
	};

	static const SkillBasicInfo _skillThird = {
		"필살기",
		"(테스트 데이터)적을 처치함",
		SkillType::Damage_IgnoreDef,
		0,
		777,
		0,
	};
}

namespace SkillData_Thief
{
	static const SkillBasicInfo _skillFirst = {
		"치명타",
		"방어 무시의 10 데미지를 줌",
		SkillType::Damage_IgnoreDef,
		2,
		10,
		0,
	};

	static const SkillBasicInfo _skillSecond = {
		"흘리기",
		"다음 공격을 회피함",
		SkillType::Buff_DamageImmune,
		5,
		0,
		1,
	};

	static const SkillBasicInfo _skillThird = {
		"처  형",
		"(테스트 데이터)적을 처치함",
		SkillType::Damage_IgnoreDef,
		0,
		777,
		0,
	};
}

namespace SkillData_Mage
{
	static const SkillBasicInfo _skillFirst = {
		"마력탄",
		"20의 데미지를 줌",
		SkillType::Damage_IgnoreDef,
		10,
		20,
		0,
	};

	static const SkillBasicInfo _skillSecond = {
		"마방벽",
		"이번 전투에서 피해를 무시",
		SkillType::Buff_DamageImmune,
		5,
		0,
		-1,
	};

	static const SkillBasicInfo _skillThird = {
		"데  스",
		"(테스트 데이터)적을 처치함",
		SkillType::Damage_IgnoreDef,
		0,
		777,
		0,
	};
}