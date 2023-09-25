#include "SLPlayerController.h"

#include <conio.h>

#include "SLGameSystem.h"
#include "SLDrawManager.h"
#include "SLGameData.h"

InputType SLPlayerController::KeyMapping() const
{
	char inputKey = _getch();

	if (inputKey == -32) {
		char inputKey2 = _getch();

		if (inputKey2 == 72) {
			return InputType::Up;
		}
		else if (inputKey2 == 80) {
			return InputType::Down;
		}
		else if (inputKey2 == 75) {
			return InputType::Left;
		}
		else if (inputKey2 == 77) {
			return InputType::Right;
		}
		else {
			return InputType::UnMapping;
		}
	}
	else {
		if (inputKey == 'w' || inputKey == 'W') {
			return InputType::Up;
		}
		else if (inputKey == 's' || inputKey == 'S') {
			return InputType::Down;
		}
		else if (inputKey == 'a' || inputKey == 'A') {
			return InputType::Left;
		}
		else if (inputKey == 'd' || inputKey == 'D') {
			return InputType::Right;
		}
		else if (inputKey == ' ' || inputKey == '\r') {
			return InputType::Select;
		}
		else {
			return InputType::UnMapping;
		}
	}
}

char SLPlayerController::CheckObject(const std::vector<std::string>& targetMap, InputType direction, Position& objectPos)
{
	const Position& curPos = _owner->GetCurrentPosition();

	int moveX = 0;
	int moveY = 0;

	switch (direction)
	{
	case InputType::Up:
		moveY -= 1;
		break;
	case InputType::Down:
		moveY += 1;
		break;
	case InputType::Left:
		moveX -= 1;
		break;
	case InputType::Right:
		moveX += 1;
		break;
	default:
		break;
	}

	objectPos.x = curPos.x + moveX;
	objectPos.y = curPos.y + moveY;

	char object = targetMap[objectPos.y][objectPos.x];

	return object;
}

void SLPlayerController::Move(int moveX, int moveY)
{
	const Position& curPos = _owner->GetCurrentPosition();
	SLDrawManager& drawManager = SLDrawManager::GetDrawManager();

	drawManager.SetColor(TextColor::White, TextColor::Black);
	drawManager.DrawTextAtPosition(" ", curPos.x, curPos.y);

	if (_owner->GetHasLegendaryWeapon() == true) {
		drawManager.SetColor(TextColor::Yellow, TextColor::Black);
	}
	else {
		drawManager.SetColor(TextColor::Cyan, TextColor::Black);
	}

	drawManager.DrawTextAtPosition("¡Ý", curPos.x + moveX, curPos.y + moveY);

	Position newPos(curPos.x + moveX, curPos.y + moveY);
	_owner->SetCurrentPosition(newPos);
}