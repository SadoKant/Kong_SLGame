#pragma once

#include <memory>

#include "SLDrawManager.h"

class SLPlayerController;
class SLAIController;

class SLGameSystem
{
public:
	static SLGameSystem& GetGameSystem();
	const std::weak_ptr<SLPlayerController>& GetPlayerController() { return _playerController; };
	const std::weak_ptr<SLAIController>& GetAIController() { return _aIController; };

	void Start();
	void GameClear();
	void End();

private:
	void StageClear();
	void WorldReset();

	void SystemInit();
	void GameInit();

	void GameLooping(int loopMapID);

	void EventLegendWeapon(std::weak_ptr<SLCharacterBase> player);

private:
	std::vector<std::string> _currentMap;
	std::shared_ptr<SLPlayerController> _playerController;
	std::shared_ptr<SLAIController> _aIController;

	bool _bGameEnd = false;
	const int _lastStage = 2;
	int _stage = 0;
};
