#pragma once
#include <string>
#include <memory>

#include "SLCommonDefine.h"

class SLCharacterBase;

struct SkillBasicInfo
{
	SkillBasicInfo(const std::string& name, const std::string& desc, SkillType skillType, int cost, int effectValue, int duration);

	std::string _name;
	std::string _desc;

	SkillType _skillType;

	int _cost = 0;
	int _effectValue = 0;

	int _duration = 0;
};

class SLSkillBase
{
public:
	SLSkillBase(SkillBasicInfo skillInfo);

public:
	const SkillBasicInfo& GetSkillInfo() { return _skillInfo; };
	virtual bool Effect(std::weak_ptr<SLCharacterBase> caster, std::weak_ptr<SLCharacterBase> target);

protected:
	SkillBasicInfo _skillInfo;
};

