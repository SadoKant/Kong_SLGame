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
		"���Ž�",
		"20�� �������� ��",
		SkillType::Damage,
		5,
		20,
		0,
	};

	static const SkillBasicInfo _skillSecond = {
		"��Ƽ��",
		"3�ϰ� ���� 20 ����",
		SkillType::Buff_DEF,
		5,
		20,
		3,
	};

	static const SkillBasicInfo _skillThird = {
		"�ʻ��",
		"(�׽�Ʈ ������)���� óġ��",
		SkillType::Damage_IgnoreDef,
		0,
		777,
		0,
	};
}

namespace SkillData_Thief
{
	static const SkillBasicInfo _skillFirst = {
		"ġ��Ÿ",
		"��� ������ 10 �������� ��",
		SkillType::Damage_IgnoreDef,
		2,
		10,
		0,
	};

	static const SkillBasicInfo _skillSecond = {
		"�긮��",
		"���� ������ ȸ����",
		SkillType::Buff_DamageImmune,
		5,
		0,
		1,
	};

	static const SkillBasicInfo _skillThird = {
		"ó  ��",
		"(�׽�Ʈ ������)���� óġ��",
		SkillType::Damage_IgnoreDef,
		0,
		777,
		0,
	};
}

namespace SkillData_Mage
{
	static const SkillBasicInfo _skillFirst = {
		"����ź",
		"20�� �������� ��",
		SkillType::Damage_IgnoreDef,
		10,
		20,
		0,
	};

	static const SkillBasicInfo _skillSecond = {
		"���溮",
		"�̹� �������� ���ظ� ����",
		SkillType::Buff_DamageImmune,
		5,
		0,
		-1,
	};

	static const SkillBasicInfo _skillThird = {
		"��  ��",
		"(�׽�Ʈ ������)���� óġ��",
		SkillType::Damage_IgnoreDef,
		0,
		777,
		0,
	};
}