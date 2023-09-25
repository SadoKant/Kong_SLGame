#include "SLSkillBase.h"

#include "SLBattleSystem.h"
#include "SLDrawManager.h"
#include "SLCharacterBase.h"

SkillBasicInfo::SkillBasicInfo(const std::string& name, const std::string& desc, SkillType skillType, int cost, int effectValue, int duration)
	: _name(name), _desc(desc), _skillType(skillType), _cost(cost), _effectValue(effectValue), _duration(duration)
{
}

SLSkillBase::SLSkillBase(SkillBasicInfo skillInfo)
	: _skillInfo(skillInfo)
{
}

bool SLSkillBase::Effect(std::weak_ptr<SLCharacterBase> caster, std::weak_ptr<SLCharacterBase> target)
{
	std::shared_ptr<SLCharacterBase> lCaster = caster.lock();

	const CharacterBasicStat& casterStat = lCaster->GetStat();
	bool bCanUseSkill = casterStat._MP >= _skillInfo._cost;
	if (bCanUseSkill == false) {
		SLDrawManager::GetDrawManager().DrawNewDialogue("마나가 부족해서 스킬을 쓸 수 없다!");
		return false;
	}

	lCaster->ChangeStat(StatType::MP, casterStat._MP -1 * _skillInfo._cost);

	SLBattleSystem& battleSystem = SLBattleSystem::GetBattleSystem();

	switch (_skillInfo._skillType)
	{
	case SkillType::None:
		break;
	case SkillType::Damage:
		battleSystem.ActionAttack(caster, target, _skillInfo._effectValue);
		break;
	case SkillType::Damage_IgnoreDef:
		battleSystem.ActionAttack(caster, target, _skillInfo._effectValue, true);
		break;
	case SkillType::Buff_ATK:
		break;
	case SkillType::Buff_DEF:
	case SkillType::Buff_DamageImmune:
		lCaster->AddBuffAtList(_skillInfo);
		break;
	default:
		break;
	}

	return true;
}