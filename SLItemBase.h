#pragma once

#include <string>
#include <map>
#include "SLCommonDefine.h"

struct ItemInfo
{
	ItemInfo(ItemType type, int itemCount, const std::map<StatType, int>& spec, const std::string& name, const std::string& desc);

	ItemType _type;
	int _count;

	std::map<StatType, int> _spec;

	std::string _name;
	std::string _desc;
};

class SLItemBase
{
public:
	SLItemBase(const ItemInfo& info);

public:
	const ItemInfo& GetInfo() { return _info; };
	bool ConsumeItem();

private:
	ItemInfo _info;
};
