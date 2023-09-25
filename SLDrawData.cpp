#include "SLDrawData.h"

SLDrawData& SLDrawData::GetDrawDataManager()
{
	static SLDrawData drawDataManager;
	return drawDataManager;
}

const std::vector<std::string> SLDrawData::GetDrawData(DrawType drawType)
{
	switch (drawType)
	{
	case DrawType::None:
		return _defaultStage;
		break;
	case DrawType::Dialogue:
		return _dialogueWindow;
		break;
	case DrawType::One:
		return _oneStage;
		break;
	case DrawType::Two:
		return _twoStage;
		break;
	case DrawType::Boss:
		return _bossStage;
		break;
	default:
		break;
	}

	return std::vector<std::string>();
}
