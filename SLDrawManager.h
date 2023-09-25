#pragma once

#include <string>
#include <vector>
#include <memory>

#include "SLCommonDefine.h"
#include "SLCharacterBase.h"

class SLDrawManager
{
public:
	SLDrawManager();

public:
	static SLDrawManager& GetDrawManager();
	void SetCursorPosition(int x, int y);
	void DrawTitle();
	void DrawClear();
	void DrawEnd();
	void DrawMenu(int posX, int posY);
	int SelectMenu(int posX, int posY);
	void DrawControlInfo();
	int DrawJobSelect();

	void DrawJobInfoWarrior(int posX, int posY);
	void DrawJobInfoThief(int posX, int posY);
	void DrawJobInfoMage(int posX, int posY);

	void DrawMap(const std::vector<std::string>& targetMap, int& outPlayerPosX, int& outPlayerPosY);
	void DrawUI(std::weak_ptr<SLCharacterBase> playerCha);
	void DrawDialogueWindow();

	void DrawCharacterStat(std::weak_ptr<SLCharacterBase> character, int posX, int posY);
	void RefreshCharacterStat(std::weak_ptr<SLCharacterBase> character);
	Position EraseStatByType(CharacterType type);

	void DrawNewDialogue(const std::string& text);
	void ResetDialogueData();

	int MenuSelect(int posX, int posY, int menuCount);
	void SetColor(TextColor foreGround, TextColor backGround);
	void DrawTextAtPosition(const std::string& text, int posX, int posY);
	void DrawTextAtPositionByList(const std::vector<std::string>& text, int posX, int posY);
	void EraseTextAtPosition(int posX, int posY, int length, int row = 1);

private:
	void Init();
	std::vector<std::string> _dialogueList;

	const int _playerStatPosX = 79;
	const int _playerStatPosY = 1;
	const int _playerStatWidth = 14;

	const int _statRow = 7;

	const int _monStatPosOffset = 17;
};