#include "SLItemBase.h"

ItemInfo::ItemInfo(ItemType type, int itemCount, const std::map<StatType, int>& spec, const std::string& name, const std::string& desc)
	: _type(type), _count(itemCount), _spec(spec), _name(name), _desc(desc)
{

}

SLItemBase::SLItemBase(const ItemInfo& info)
	: _info(info)
{

}

bool SLItemBase::ConsumeItem()
{
	if (_info._type != ItemType::Consume) {
		return false;
	}

	_info._count--;

	return true;
}
