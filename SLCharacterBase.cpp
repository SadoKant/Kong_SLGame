#include "SLCharacterBase.h"

#include "SLGameData.h"
#include "SLGameSystem.h"
#include "SLDrawManager.h"

SLCharacterBase::SLCharacterBase(CharacterType type)
	: _characterType(type)
{
	switch (type)
	{
	case CharacterType::None:
		break;
	case CharacterType::Warrior:
		_characterStat = BasicStatData::_warriorBasicStat;
		_name = "전사";
		break;
	case CharacterType::Thief:
		_characterStat = BasicStatData::_thiefBasicStat;
		_name = "도적";
		break;
	case CharacterType::Mage:
		_characterStat = BasicStatData::_mageBasicStat;
		_name = "마법사";
		break;
	case CharacterType::LowMon:
		_characterStat = BasicStatData::_lowMonStat;
		_name = "임프";
		break;
	case CharacterType::MidMon:
		_characterStat = BasicStatData::_midMonStat;
		_name = "오우거";
		break;
	case CharacterType::Boss:
		_characterStat = BasicStatData::_bossMonStat;
		_name = "악마";
		break;
	default:
		break;
	}
}

void SLCharacterBase::ChangeStat(StatType statType, int value)
{
	switch (statType)
	{
	case StatType::HP:
		_characterStat._HP = value;
		if (_characterStat._HP < 0) {
			_characterStat._HP = 0;
		}
		if (_characterStat._HP > _characterStat._HP_Max) {
			_characterStat._HP = _characterStat._HP_Max;
		}
		break;
	case StatType::HP_Max:
		_characterStat._HP_Max = value;
		break;
	case StatType::MP:
		_characterStat._MP = value;
		if (_characterStat._MP > _characterStat._MP_Max) {
			_characterStat._MP = _characterStat._MP_Max;
		}
		break;
	case StatType::MP_Max:
		_characterStat._MP_Max = value;
		break;
	case StatType::ATK:
		_characterStat._ATK = value;
		break;
	case StatType::DEF:
		_characterStat._DEF = value;
		break;
	default:
		break;
	}

	SLDrawManager& drawManager = SLDrawManager::GetDrawManager();
	std::shared_ptr<SLCharacterBase> tempShared = shared_from_this();
	
	drawManager.RefreshCharacterStat(tempShared);
}

void SLCharacterBase::Dead()
{
	switch (_characterType)
	{
	case CharacterType::LowMon:
	case CharacterType::MidMon:
	{
		SLDrawManager& drawManager = SLDrawManager::GetDrawManager();
		drawManager.EraseTextAtPosition(_currentPos.x, _currentPos.y, 1);

		drawManager.EraseStatByType(_characterType);
		break;
	}
	case CharacterType::Boss:
		SLGameSystem::GetGameSystem().GameClear();
		break;
	default:
		break;
	}
}

void SLCharacterBase::AddBuffAtList(SkillBasicInfo skillInfo)
{
	std::vector<int> buffInfo = { skillInfo._effectValue, skillInfo._duration };
	_buffList[skillInfo._skillType] = buffInfo;
}

void SLCharacterBase::UpdateBuffDuration(const CharacterBasicStat& originStat)
{
	for (auto it = _buffList.begin(); it != _buffList.end(); ) {
		if (it->second[1] != 0) {
			it->second[1]--;
			if (it->second[1] == 0) {
				switch (it->first)
				{
				case SkillType::Buff_DEF:
				case SkillType::Buff_DamageImmune:
					ChangeStat(StatType::DEF, originStat._DEF);
					break;
				default:
					break;
				}
				it = _buffList.erase(it);
			}
			else {
				++it;
			}
		}
	}
}

void SLCharacterBase::RemoveAllBuff(const CharacterBasicStat& originStat)
{
	ChangeStat(StatType::DEF, originStat._DEF);

	_buffList.clear();
}
