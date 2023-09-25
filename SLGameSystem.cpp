#include "SLGameSystem.h"

#include <Windows.h>

#include "SLCommonDefine.h"
#include "SLDrawData.h"
#include "SLBattleSystem.h"
#include "SLDrawManager.h"
#include "SLPlayerController.h"
#include "SLAIController.h"

#include "SLPlayer.h"

SLGameSystem& SLGameSystem::GetGameSystem()
{
	static SLGameSystem gameSystem;
	return gameSystem;
}

void SLGameSystem::Start()
{
	SystemInit();

	int menuStartPosX = 55;
	int menuStartPosY = 16;

	SLDrawManager& drawManager = SLDrawManager::GetDrawManager();
	int selectedMenu = 0;
	while (true) {
		GameInit();

		drawManager.DrawTitle();
		drawManager.DrawMenu(menuStartPosX, menuStartPosY);
		selectedMenu = drawManager.SelectMenu(menuStartPosX, menuStartPosY);

		if (selectedMenu == 0) {
			int selectedJob = drawManager.DrawJobSelect();

			if (selectedJob == 0) {
				_playerController->CreateCharacter(CharacterType::Warrior);
			}
			else if (selectedJob == 1) {
				_playerController->CreateCharacter(CharacterType::Thief);
			}
			else if (selectedJob == 2) {
				_playerController->CreateCharacter(CharacterType::Mage);
			}

			GameLooping(_stage);
		}
		else if (selectedMenu == 1) {
			drawManager.DrawControlInfo();
		}
		else if (selectedMenu == 2) {
			return;
		}

		system("cls");
		drawManager.SetColor(TextColor::White, TextColor::Black);
	}
}

void SLGameSystem::StageClear()
{
	_stage++;

	SLDrawManager& drawManager = SLDrawManager::GetDrawManager();
	drawManager.ResetDialogueData();
}

void SLGameSystem::GameClear()
{
	system("cls");

	SLDrawManager& drawManager = SLDrawManager::GetDrawManager();
	drawManager.DrawClear();

	WorldReset();
}

void SLGameSystem::End()
{
	system("cls");

	SLDrawManager& drawManager = SLDrawManager::GetDrawManager();
	drawManager.DrawEnd();

	WorldReset();
}

void SLGameSystem::WorldReset()
{
	Sleep(6000);

	_playerController = nullptr;
	_aIController = nullptr;

	_bGameEnd = true;
	_stage = 0;

	SLDrawManager& drawManager = SLDrawManager::GetDrawManager();
	drawManager.ResetDialogueData();

	system("cls");
}

void SLGameSystem::SystemInit()
{
	std::string command = "mode con cols=" + std::to_string(MaxScreenSize::x) + " lines=" + std::to_string(MaxScreenSize::y) + " | title SL RPG";
	system(command.c_str());

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO consoleCursor;
	consoleCursor.bVisible = false;
	consoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &consoleCursor);

	SLDrawData& drawDataManager = SLDrawData::GetDrawDataManager();
	_currentMap = drawDataManager.GetDrawData(DrawType::None);
}

void SLGameSystem::GameInit()
{
	_bGameEnd = false;

	_playerController = std::make_shared<SLPlayerController>();
	_aIController = std::make_shared<SLAIController>();
}

void SLGameSystem::GameLooping(int loopMapID)
{
	bool bNowPlaying = true;

	SLDrawData& drawDataManager = SLDrawData::GetDrawDataManager();
	if (loopMapID == 0) {
		_currentMap = drawDataManager.GetDrawData(DrawType::One);
	}
	else if (loopMapID == 1) {
		_currentMap = drawDataManager.GetDrawData(DrawType::Two);
	}
	else if (loopMapID == 2) {
		_currentMap = drawDataManager.GetDrawData(DrawType::Boss);
	}

	SLDrawManager& drawManager = SLDrawManager::GetDrawManager();
	int startPosX = 0;
	int startPosY = 0;

	system("cls");
	drawManager.DrawMap(_currentMap, startPosX, startPosY);

	Position startPos(startPosX, startPosY);
	std::shared_ptr<SLCharacterBase> playerCha = _playerController->GetOwner().lock();
	playerCha->SetCurrentPosition(startPos);
	
	drawManager.DrawUI(playerCha);

	while (bNowPlaying) {
		InputType input = _playerController->KeyMapping();

		Position objectPos;
		char object = _playerController->CheckObject(_currentMap, input, objectPos);

		if (object == '-' || object == 'P') {
			switch (input)
			{
			case InputType::Up:
				_playerController->Move(0, -1);
				break;
			case InputType::Down:
				_playerController->Move(0, 1);
				break;
			case InputType::Right:
				_playerController->Move(1, 0);
				break;
			case InputType::Left:
				_playerController->Move(-1, 0);
				break;
			case InputType::Select:
				break;
			default:
				break;
			}
		}
		else if (object == 'm' || object == 'M' || object == 'B') {
			std::shared_ptr<SLCharacterBase> monster = _aIController->GetSpecificMon(objectPos).lock();

			_currentMap[objectPos.y][objectPos.x] = '-';
			
			bool bBattleEnd = SLBattleSystem::GetBattleSystem().StartBattle(playerCha, monster);
			if (bBattleEnd == true) {
				if (_aIController != nullptr) {
					_aIController->DeleteMonster(monster->GetCurrentPosition());
				}
				monster = nullptr;
			}

			if (_bGameEnd == true) {
				playerCha = nullptr;
				bNowPlaying = false;
			}
		}
		else if (object == 'T') {
			_currentMap[objectPos.y][objectPos.x] = '-';
			drawManager.DrawTextAtPosition(" ", objectPos.x, objectPos.y);

			drawManager.SetColor(TextColor::Yellow, TextColor::Black);
			drawManager.DrawTextAtPosition("◎", playerCha->GetCurrentPosition().x, playerCha->GetCurrentPosition().y);

			drawManager.SetColor(TextColor::White, TextColor::Black);
			EventLegendWeapon(playerCha);
		}
		else if (object == 'S') {
			StageClear();
			bNowPlaying = false;
		}
	}

	if (_bGameEnd == false && _stage <= _lastStage) {
		GameLooping(_stage);
	}
}

void SLGameSystem::EventLegendWeapon(std::weak_ptr<SLCharacterBase> player)
{
	std::shared_ptr<SLPlayer> lPlayer = std::dynamic_pointer_cast<SLPlayer>(player.lock());
	lPlayer->SetHasLegendaryWeapon(true);

	std::map<StatType, int> Itemspec;
	Itemspec[StatType::ATK] = 30;
	ItemInfo legendWeapon(ItemType::Equip, 1, Itemspec, "전설의 검", "공격력 30 증가");

	lPlayer->AddNewItem(legendWeapon);
}
