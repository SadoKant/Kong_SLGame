#pragma once

namespace MaxScreenSize
{
	const int x = 120;
	const int y = 33;
};

namespace MaxStageSize
{
	const int x = 76;
	const int y = 22;
};

enum class CharacterType : int
{
	None = 0,
	Warrior,
	Thief,
	Mage,

	LowMon = 10,
	MidMon,
	Boss,
};

enum class StatType : int
{
	HP = 0,
	HP_Max,

	MP,
	MP_Max,

	ATK,
	DEF,
};

enum class SkillType : int
{
	None = 0,
	Damage,
	Damage_IgnoreDef,
	Buff_ATK,
	Buff_DEF,
	Buff_DamageImmune,
};

enum class InputType : int
{
	UnMapping = 0,
	Up,
	Down,
	Left,
	Right,
	Select,
};

enum class BattleActionType : int
{
	None = 0,
	Attack,
	Skill,
	Item,
};

enum class ItemType : int
{
	None = 0,
	Consume,
	Equip,
};

enum class TextColor : int
{
	Black = 0,
	Blue,
	Green,
	Cyan,
	Red,
	Purple,
	Brown,
	Lightgray,
	Darkgray,
	Lightblue,
	Lightgreen,
	Lightcyan,
	Lightred,
	Lightpurple,
	Yellow,
	White
};