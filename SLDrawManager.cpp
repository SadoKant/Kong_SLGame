#include "SLDrawManager.h"

#include <iostream>
#include <string>
#include <vector>
//#include <algorithm>
#include <Windows.h>

#include "SLCommonDefine.h"
#include "SLGameData.h"
#include "SLDrawData.h"
#include "SLGameSystem.h"
#include "SLPlayerController.h"
#include "SLAIController.h"

SLDrawManager::SLDrawManager()
{
	Init();
}

SLDrawManager& SLDrawManager::GetDrawManager()
{
	static SLDrawManager drawManager;
	return drawManager;
}

void SLDrawManager::SetCursorPosition(int x, int y)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;
	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(consoleHandle, position);
}

void SLDrawManager::DrawTitle()
{
	std::vector<std::string> title = {
		{"      :dBBBB:  vbU            .KbgZPY:    YKZgEIi      .YRBBBRr"},
		{"    LQBBPKBB.  BBr            BBBPZQBB2  .BBRDBBBB   LBQBQEEBBJ"},
		{"   LBB        QBQ            7BB   .BB.  BBu   PBB  BBg        "},
		{"   sBBBs     :BB             BBJ  sQB.  rBB   uQB  BB:         "},
		{"    .XBBQB   BQs            PBBBBBQ     BBBBBBBU  QBK   BBBBB. "},
		{"       SBB  JBB             BB  :QB.   PBB        BBr     BQv  "},
		{" BX. .7BBv  BBq:rvv        BBg   BBB  .BB.        BBB2: BBB    "},
		{".BBBBBB2   PBBBBBBB       iBB    :BQr QBd          SBBBBBBX    "}
	};

	DrawTextAtPositionByList(title, 30, 4);
}

void SLDrawManager::DrawClear()
{
	std::vector<std::string> MSG = {
		{"      .ir:    iB:                                               "},
		{"   .gBQBBBBQ  .B.                                 BB    gB    uB"},
		{"  BBD.     :  iB:                                 BQ    BB    PB"},
		{" gB.          :B:     7dE1      :IbEs     :i ib2  QB    QB    1B"},
		{"JB7           iB:   sBBJJMBX   KBdjLBB7   BBgQgE  BB    QB    uB"},
		{"BB            :B:  7Q.    :B:        BB   BBr     BB    MB    JB"},
		{"BB            iB:  BBPQBBQBQZ   vDBQQQB   BB      BB    BB    2B"},
		{".BB           :B:  BQ .:::..  .BBi.  BB   BB      SX    Lg    :X"},
		{" :BB          iB:  YB.        gB     BB   BB                    "},
		{"   gBBPSSZBM  .B.   rBRuv2QM   BBs7X2BB   QB      BB    BB    DB"},
		{"                                                                "},
		{"   플레이 해주셔서 감사합니다! 잠시 후 메인 화면으로 돌아 갑니다!"}
	};

	DrawTextAtPositionByList(MSG, 30, 8);
}

void SLDrawManager::DrawEnd()
{
	std::vector<std::string> MSG = {
		{":rr:.i7r UQ                     :r777                B          "},
		{"71LZBL1J SB                    jBLsIY                B          "},
		{"   :B    PB 7s.    .Lv:        dB      . :s7     rJi B          "},
		{"   rB    5BsivB2  bQ::gB       KB:i7.  BBvigB  .Bdr7gB          "},
		{"   rB    KB   sB :BriisQ.      IB7UXr  B:   Bi Qq    B          "},
		{"   rQ    dB   vB rB..::.       bB      B.   Br Br    B          "},
		{"   :B    XB   7B  BY  ..       UB.:ii  B    B: .B: .XB  vv .q  5"},
		{"                                                                "},
		{"                                                                "},
		{"  당신은 패배했습니다... 잠시 후 메인 화면으로 돌아 갑니다...  "}
	};

	DrawTextAtPositionByList(MSG, 35, 8);
}

void SLDrawManager::DrawMenu(int posX, int posY)
{
	DrawTextAtPosition("> 게 임 시 작", posX - 1, posY);
	DrawTextAtPosition(" 조 작 방 법 ", posX, posY + 1);
	DrawTextAtPosition("    종 료    ", posX, posY + 2);
}

int SLDrawManager::SelectMenu(int posX, int posY)
{
	int selectedRow = MenuSelect(posX, posY, 3);

	return selectedRow;
}

void SLDrawManager::DrawControlInfo()
{
	system("cls");

	std::vector<std::string> MSG = {
		{"                            [ 조 작 방 법 ]             "},
		{"                                                        "},
		{"                  이 동 : 화살표 방향키 or W, A, S, D   "},
		{"                  선 택 : 스페이스바 or 앤터키          "},
		{"                                                        "},
		{"                                                        "},
		{"                선택키를 누르면 메인화면으로 이동합니다."},
	};

	DrawTextAtPositionByList(MSG, 28, 8);

	std::shared_ptr<SLPlayerController> controller = SLGameSystem::GetGameSystem().GetPlayerController().lock();
	while (true) {
		InputType input = controller->KeyMapping();
		switch (input)
		{
		case InputType::Select:
			return;
			break;
		}
	}
}

int SLDrawManager::DrawJobSelect()
{
	int x = 31;
	int y = 6;

	int minYPos = y;
	int maxYPos = y + 2;
	int firstXPos = x;
	int firstYPos = y;

	system("cls");
	std::cout << "\n\n";
	std::cout << "                            [ 직 업 선 택 ]\n\n";

	DrawTextAtPosition("> 전 사", x - 1, y);
	DrawTextAtPosition(" 도 적", x, y + 1);
	DrawTextAtPosition(" 마 법 사", x, y + 2);

	int chracterInfoPosX = firstXPos + 30;
	int chracterInfoPosY = firstYPos;

	DrawJobInfoWarrior(chracterInfoPosX, chracterInfoPosY);

	std::shared_ptr<SLPlayerController> controller = SLGameSystem::GetGameSystem().GetPlayerController().lock();
	while (true) {
		InputType input = controller->KeyMapping();
		switch (input)
		{
		case InputType::UnMapping:
			break;
		case InputType::Up:
			if (y > minYPos) {
				DrawTextAtPosition(" ", x - 1, y);
				DrawTextAtPosition(">", x - 1, --y);
			}
			break;
		case InputType::Down:
			if (y < maxYPos) {
				DrawTextAtPosition(" ", x - 1, y);
				DrawTextAtPosition(">", x - 1, ++y);
			}
			break;
		case InputType::Select:
			return (y - firstYPos);
			break;
		default:
			break;
		}

		EraseTextAtPosition(chracterInfoPosX, chracterInfoPosY, 50, 20);

		if (y == firstYPos) {
			DrawJobInfoWarrior(chracterInfoPosX, chracterInfoPosY);
		}
		else if (y == firstYPos + 1) {
			DrawJobInfoThief(chracterInfoPosX, chracterInfoPosY);
		}
		else if (y == firstYPos + 2) {
			DrawJobInfoMage(chracterInfoPosX, chracterInfoPosY);
		}
	}
}

void SLDrawManager::DrawJobInfoWarrior(int posX, int posY)
{
	DrawTextAtPosition("전 사", posX, posY);
	++posY;
	DrawTextAtPosition("가장 기본적인 튼튼한 직업입니다.", posX, ++posY);
	++posY;
	++posY;

	DrawTextAtPosition("기본 능력치", posX, ++posY);
	++posY;

	std::string infoTemp = "HP  : " + std::to_string(BasicStatData::_warriorBasicStat._HP) + " ";
	DrawTextAtPosition(infoTemp, posX, ++posY);

	infoTemp = "MP  : " + std::to_string(BasicStatData::_warriorBasicStat._MP) + " ";
	DrawTextAtPosition(infoTemp, posX, ++posY);

	infoTemp = "ATK : " + std::to_string(BasicStatData::_warriorBasicStat._ATK) + " ";
	DrawTextAtPosition(infoTemp, posX, ++posY);

	infoTemp = "DEF : " + std::to_string(BasicStatData::_warriorBasicStat._DEF) + " ";
	DrawTextAtPosition(infoTemp, posX, ++posY);
	++posY;
	++posY;

	DrawTextAtPosition("보유 스킬", posX, ++posY);
	++posY;

	infoTemp = SkillData_Warrior::_skillFirst._name + " : " + SkillData_Warrior::_skillFirst._desc;
	DrawTextAtPosition(infoTemp, posX, ++posY);

	infoTemp = SkillData_Warrior::_skillSecond._name + " : " + SkillData_Warrior::_skillSecond._desc;
	DrawTextAtPosition(infoTemp, posX, ++posY);

	infoTemp = SkillData_Warrior::_skillThird._name + " : " + SkillData_Warrior::_skillThird._desc;
	DrawTextAtPosition(infoTemp, posX, ++posY);
}

void SLDrawManager::DrawJobInfoThief(int posX, int posY)
{
	DrawTextAtPosition("도 적", posX, posY);
	++posY;
	DrawTextAtPosition("빠르게 움직여, 한 턴에 2번의 행동을 합니다.", posX, ++posY);
	++posY;
	++posY;

	DrawTextAtPosition("기본 능력치", posX, ++posY);
	++posY;

	std::string infoTemp = "HP  : " + std::to_string(BasicStatData::_thiefBasicStat._HP) + " ";
	DrawTextAtPosition(infoTemp, posX, ++posY);

	infoTemp = "MP  : " + std::to_string(BasicStatData::_thiefBasicStat._MP) + " ";
	DrawTextAtPosition(infoTemp, posX, ++posY);

	infoTemp = "ATK : " + std::to_string(BasicStatData::_thiefBasicStat._ATK) + " ";
	DrawTextAtPosition(infoTemp, posX, ++posY);

	infoTemp = "DEF : " + std::to_string(BasicStatData::_thiefBasicStat._DEF) + " ";
	DrawTextAtPosition(infoTemp, posX, ++posY);
	++posY;
	++posY;

	DrawTextAtPosition("보유 스킬", posX, ++posY);
	++posY;

	infoTemp = SkillData_Thief::_skillFirst._name + " : " + SkillData_Thief::_skillFirst._desc;
	DrawTextAtPosition(infoTemp, posX, ++posY);

	infoTemp = SkillData_Thief::_skillSecond._name + " : " + SkillData_Thief::_skillSecond._desc;
	DrawTextAtPosition(infoTemp, posX, ++posY);

	infoTemp = SkillData_Thief::_skillThird._name + " : " + SkillData_Thief::_skillThird._desc;
	DrawTextAtPosition(infoTemp, posX, ++posY);
}

void SLDrawManager::DrawJobInfoMage(int posX, int posY)
{
	DrawTextAtPosition("마 법 사", posX, posY);
	++posY;
	DrawTextAtPosition("유리 대포입니다. 모든 공격이 방어를 무시합니다. ", posX, ++posY);
	++posY;
	++posY;

	DrawTextAtPosition("기본 능력치", posX, ++posY);
	++posY;

	std::string infoTemp = "HP  : " + std::to_string(BasicStatData::_mageBasicStat._HP) + " ";
	DrawTextAtPosition(infoTemp, posX, ++posY);

	infoTemp = "MP  : " + std::to_string(BasicStatData::_mageBasicStat._MP) + " ";
	DrawTextAtPosition(infoTemp, posX, ++posY);

	infoTemp = "ATK : " + std::to_string(BasicStatData::_mageBasicStat._ATK) + " ";
	DrawTextAtPosition(infoTemp, posX, ++posY);

	infoTemp = "DEF : " + std::to_string(BasicStatData::_mageBasicStat._DEF) + " ";
	DrawTextAtPosition(infoTemp, posX, ++posY);
	++posY;
	++posY;

	DrawTextAtPosition("보유 스킬", posX, ++posY);
	++posY;

	infoTemp = SkillData_Mage::_skillFirst._name + " : " + SkillData_Mage::_skillFirst._desc;
	DrawTextAtPosition(infoTemp, posX, ++posY);

	infoTemp = SkillData_Mage::_skillSecond._name + " : " + SkillData_Mage::_skillSecond._desc;
	DrawTextAtPosition(infoTemp, posX, ++posY);

	infoTemp = SkillData_Mage::_skillThird._name + " : " + SkillData_Mage::_skillThird._desc;
	DrawTextAtPosition(infoTemp, posX, ++posY);
}

void SLDrawManager::DrawMap(const std::vector<std::string>& targetMap, int& outPlayerPosX, int& outPlayerPosY)
{
	std::shared_ptr<SLAIController> controller = SLGameSystem::GetGameSystem().GetAIController().lock();
	Position monPos(0, 0);

	int mapX = 0;
	int mapY = 0;

	size_t mapMaxX = targetMap[0].length();
	size_t mapMaxY = targetMap.size();
		
	for (mapY = 0; mapY < mapMaxY; mapY++) {
		for (mapX = 0; mapX < mapMaxX; mapX++) {
			char curMapData = targetMap[mapY][mapX];
			if (curMapData == 'L') {
				SetColor(TextColor::Darkgray, TextColor::Darkgray);
				std::cout << curMapData;
			}
			else if (curMapData == '-') {
				SetColor(TextColor::Black, TextColor::Black);
				std::cout << " ";
			}
			else if (curMapData == 'W') {
				SetColor(TextColor::Lightgray, TextColor::Lightgray);
				std::cout << curMapData;
			}
			else if (curMapData == 'P') {
				outPlayerPosX = mapX;
				outPlayerPosY = mapY;

				bool bHasLegendary = SLGameSystem::GetGameSystem().GetPlayerController().lock()->GetOwner().lock()->GetHasLegendaryWeapon();
				if (bHasLegendary == true) {
					SetColor(TextColor::Yellow, TextColor::Black);
				}
				else {
					SetColor(TextColor::Cyan, TextColor::Black);
				}
				std::cout << "◎";
			}
			else if (curMapData == 'S') {
				SetColor(TextColor::Lightblue, TextColor::Black);
				std::cout << "▧";
			}
			else if (curMapData == 'T') {
				SetColor(TextColor::Yellow, TextColor::Black);
				std::cout << "▣";
			}
			else if (curMapData == 'F') {
				SetColor(TextColor::Lightred, TextColor::Black);
				std::cout << "♨";
			}
			else if (curMapData == 'm') {
				SetColor(TextColor::Lightgreen, TextColor::Black);
				std::cout << "m";

				monPos.x = mapX;
				monPos.y = mapY;

				controller->CreateMonster(CharacterType::LowMon, monPos);
			}
			else if (curMapData == 'M') {
				SetColor(TextColor::Purple, TextColor::Black);
				std::cout << "O";

				monPos.x = mapX;
				monPos.y = mapY;

				controller->CreateMonster(CharacterType::MidMon, monPos);
			}
			else if (curMapData == 'B') {
				SetColor(TextColor::Red, TextColor::Black);
				std::cout << "D";

				monPos.x = mapX;
				monPos.y = mapY;

				controller->CreateMonster(CharacterType::Boss, monPos);
			}
			else {
				SetColor(TextColor::White, TextColor::Black);
				std::cout << curMapData;
			}
		}
		SetColor(TextColor::White, TextColor::Black);
		std::cout << "\n";
	}
}

void SLDrawManager::DrawUI(std::weak_ptr<SLCharacterBase> playerCha)
{
	DrawDialogueWindow();
	DrawCharacterStat(playerCha, _playerStatPosX, _playerStatPosY);
}

void SLDrawManager::DrawDialogueWindow()
{
	std::vector<std::string> dialogueWindow = SLDrawData::GetDrawDataManager().GetDrawData(DrawType::Dialogue);

	int startY = MaxStageSize::y;

	size_t maxX = dialogueWindow[0].length();
	size_t maxY = dialogueWindow.size();

	SetColor(TextColor::Darkgray, TextColor::Darkgray);

	for (int mapY = 0; mapY < maxY; mapY++) {
		for (int mapX = 0; mapX < maxX; mapX++) {

			char curMapData = dialogueWindow[mapY][mapX];
			if (curMapData == 'L') {
				SetColor(TextColor::Darkgray, TextColor::Darkgray);
				std::cout << curMapData;
			}
			else if (curMapData == '-') {
				SetColor(TextColor::Black, TextColor::Black);
				std::cout << " ";
			}
		}
		SetColor(TextColor::White, TextColor::Black);
		if (mapY < maxY - 1) {
			std::cout << "\n";
		}
	}

	SetColor(TextColor::White, TextColor::Black);
}

void SLDrawManager::DrawCharacterStat(std::weak_ptr<SLCharacterBase> character, int posX, int posY)
{
	std::shared_ptr<SLCharacterBase> shared = character.lock();
	CharacterBasicStat drawStat = shared->GetStat();
	
	const int statX = posX;
	int statY = posY;

	SetColor(TextColor::White, TextColor::Black);
	std::string Job = shared->GetName();
	DrawTextAtPosition(Job, statX, statY);

	++statY;
	std::string digitBuffer;

	SetColor(TextColor::Red, TextColor::Black);
	drawStat._HP < 10 ? digitBuffer = " " : digitBuffer = "";
	std::string HP = "HP  : " + digitBuffer + std::to_string(drawStat._HP) + " / " + std::to_string(drawStat._HP_Max);
	DrawTextAtPosition(HP, statX, ++statY);

	SetColor(TextColor::Blue, TextColor::Black);
	drawStat._MP < 10 ? digitBuffer = " " : digitBuffer = "";
	std::string MP = "MP  : " + digitBuffer + std::to_string(drawStat._MP) + " / " + std::to_string(drawStat._MP_Max);
	DrawTextAtPosition(MP, statX, ++statY);

	++statY;

	SetColor(TextColor::Lightred, TextColor::Black);
	std::string ATK = "ATK : " + std::to_string(drawStat._ATK);
	DrawTextAtPosition(ATK, statX, ++statY);

	SetColor(TextColor::Yellow, TextColor::Black);
	std::string DEF = "DEF : " + std::to_string(drawStat._DEF);
	DrawTextAtPosition(DEF, statX, ++statY);

	SetColor(TextColor::White, TextColor::Black);
}

void SLDrawManager::RefreshCharacterStat(std::weak_ptr<SLCharacterBase> character)
{
	std::shared_ptr<SLCharacterBase> shared = character.lock();
	CharacterType type = shared->GetCharacterType();

	Position statPos = EraseStatByType(type);
	DrawCharacterStat(character, statPos.x, statPos.y);
}

Position SLDrawManager::EraseStatByType(CharacterType type)
{
	int statPosX = 0;
	int statPosY = 0;
	int statWidth = 0;

	switch (type)
	{
	case CharacterType::None:
		break;
	case CharacterType::Warrior:
	case CharacterType::Thief:
	case CharacterType::Mage:
		statPosX = _playerStatPosX;
		statPosY = _playerStatPosY;
		statWidth = _playerStatWidth;
		break;
	case CharacterType::LowMon:
	case CharacterType::MidMon:
	case CharacterType::Boss:
		statPosX = _playerStatPosX + _monStatPosOffset;
		statPosY = _playerStatPosY;
		statWidth = _playerStatWidth;
		break;
	default:
		break;
	}

	EraseTextAtPosition(statPosX, statPosY, statWidth, _statRow);

	Position statPos(statPosX, statPosY);

	return statPos;
}

void SLDrawManager::DrawNewDialogue(const std::string& text)
{
	int maxDialogueCount = MaxScreenSize::y - MaxStageSize::y - 2;

	if (maxDialogueCount - 1 < _dialogueList.size()) {
		if (_dialogueList.empty() == false) {
			_dialogueList.erase(_dialogueList.begin()); 
		}
	}

	_dialogueList.emplace_back(text);

	SetColor(TextColor::White, TextColor::Black);

	EraseTextAtPosition(1, MaxStageSize::y, MaxStageSize::x - 2, maxDialogueCount);

	int listSize = static_cast<int>(_dialogueList.size());
	for (int i = 0; i < listSize; i++) {
		DrawTextAtPosition(_dialogueList[i], 2, MaxScreenSize::y - 2 - listSize + i );
	}
}

void SLDrawManager::ResetDialogueData()
{
	_dialogueList.clear();
}

int SLDrawManager::MenuSelect(int posX, int posY, int menuCount)
{
	int minYPos = posY;
	int maxYPos = posY + menuCount - 1;
	int firstYPos = posY;

	std::shared_ptr<SLPlayerController> controller = SLGameSystem::GetGameSystem().GetPlayerController().lock();
	while (true) {
		InputType input = controller->KeyMapping();
		switch (input)
		{
		case InputType::UnMapping:
			break;
		case InputType::Up:
			if (posY > minYPos) {
				DrawTextAtPosition(" ", posX - 1, posY);
				DrawTextAtPosition(">", posX - 1, --posY);
			}
			break;
		case InputType::Down:
			if (posY < maxYPos) {
				DrawTextAtPosition(" ", posX - 1, posY);
				DrawTextAtPosition(">", posX - 1, ++posY);
			}
			break;
		case InputType::Select:
			return (posY - firstYPos);
			break;
		default:
			break;
		}
	}

	return 0;
}

void SLDrawManager::SetColor(TextColor foreGround, TextColor backGround)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	int code = static_cast<int>(foreGround) + static_cast<int>(backGround) * 16;
	SetConsoleTextAttribute(consoleHandle, code);
}

void SLDrawManager::DrawTextAtPosition(const std::string& text, int posX, int posY)
{
	SetCursorPosition(posX, posY);
	std::cout << text;
}

void SLDrawManager::DrawTextAtPositionByList(const std::vector<std::string>& text, int posX, int posY)
{
	for (int i = 0; i < text.size(); i++) {
		SetCursorPosition(posX, posY + i);
		std::cout << text[i];
	}
}

void SLDrawManager::EraseTextAtPosition(int posX, int posY, int length, int row /* = 1 */)
{
	SetColor(TextColor::White, TextColor::Black);
	SetCursorPosition(posX, posY);

	std::string eraser;
	for (size_t i = 0; i < length; i++) {
		eraser += " ";
	}

	for (size_t i = 0; i < row; i++) {
		std::cout << eraser;
		SetCursorPosition(posX, ++posY);
	}
}

void SLDrawManager::Init()
{
	//_mapBase = SLMapBase();
}
