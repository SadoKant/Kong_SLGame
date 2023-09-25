#pragma once

#include "SLCommonDefine.h"

#include <string>
#include <vector>

enum class DrawType
{
	None = 0,
	Dialogue,
	Battle,
	One,
	Two,
	Boss,
};

class SLDrawData
{
public:
	static SLDrawData& GetDrawDataManager();

public:
	const std::vector<std::string> GetDrawData(DrawType drawType);

private:
	const std::vector<std::string> _defaultStage = {
		{"----------------------------------------------------------------------------"},
		{"----------------------------------------------------------------------------"},
		{"----------------------------------------------------------------------------"},
		{"----------------------------------------------------------------------------"},
		{"----------------------------------------------------------------------------"},
		{"----------------------------------------------------------------------------"},
		{"----------------------------------------------------------------------------"},
		{"----------------------------------------------------------------------------"},
		{"----------------------------------------------------------------------------"},
		{"----------------------------------------------------------------------------"},
		{"----------------------------------------------------------------------------"},
		{"----------------------------------------------------------------------------"},
		{"----------------------------------------------------------------------------"},
		{"----------------------------------------------------------------------------"},
		{"----------------------------------------------------------------------------"},
		{"----------------------------------------------------------------------------"},
		{"----------------------------------------------------------------------------"},
		{"----------------------------------------------------------------------------"},
		{"----------------------------------------------------------------------------"},
		{"----------------------------------------------------------------------------"},
		{"----------------------------------------------------------------------------"},
		{"----------------------------------------------------------------------------"}
	};

	const std::vector<std::string> _dialogueWindow = {
		{"L--------------------------------------------------------------------------L"},
		{"L--------------------------------------------------------------------------L"},
		{"L--------------------------------------------------------------------------L"},
		{"L--------------------------------------------------------------------------L"},
		{"L--------------------------------------------------------------------------L"},
		{"L--------------------------------------------------------------------------L"},
		{"L--------------------------------------------------------------------------L"},
		{"L--------------------------------------------------------------------------L"},
		{"L--------------------------------------------------------------------------L"},
		{"LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL"},
	};

	const std::vector<std::string> _oneStage = {
		{"LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL"},
		{"L--------------------------------------------------------------------------L"},
		{"L--------------------------------------------------------------------------L"},
		{"L--------------------------------------------------------------------------L"},
		{"L--------------------------------------------------------------------------L"},
		{"L--------------------------------------------------------------------------L"},
		{"L--------------------------------------------------------------------------L"},
		{"L--------------------------------------------------------------------------L"},
		{"L------------------------------WWWWWWWWWWWWW-------------------------------L"},
		{"L------------------------------W------W----W-------------------------------L"},
		{"L------------------------------W--P---m--S-W-------------------------------L"},
		{"L------------------------------W------W----W-------------------------------L"},
		{"L------------------------------WWWWWWWWWWWWW-------------------------------L"},
		{"L--------------------------------------------------------------------------L"},
		{"L--------------------------------------------------------------------------L"},
		{"L--------------------------------------------------------------------------L"},
		{"L--------------------------------------------------------------------------L"},
		{"L--------------------------------------------------------------------------L"},
		{"L--------------------------------------------------------------------------L"},
		{"L--------------------------------------------------------------------------L"},
		{"L--------------------------------------------------------------------------L"},
		{"LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL"}
	};

	const std::vector<std::string> _twoStage = {
		{"LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL"},
		{"L--------------------------------------------------------------------------L"},
		{"L--------------------------------------------------------------------------L"},
		{"L---------------------WWWWW------------------------------------------------L"},
		{"L---------------------W---W------------------------------------------------L"},
		{"L---------------------W-P-W------------------------------------------------L"},
		{"L---------------------W---W------WWWWWWW-----------------------------------L"},
		{"L---------------------WW-WW------W--T--W-----------------------------------L"},
		{"L----------------------W-W-------W-----W-----------------------------------L"},
		{"L----------------------W-W-------WW---WW-----------------------------------L"},
		{"L----------------------W-W--------W---W------------------------------------L"},
		{"L----------------------W-W--------W---W------------------------------------L"},
		{"L----------------------W-WWWWWWWWWW---WW-------WWWWWWWWWW------------------L"},
		{"L----------------------W------m--------WWWWWWWWW--m-m---W------------------L"},
		{"L----------------------W----m----------------------M--S-W------------------L"},
		{"L----------------------W------m--------WWWWWWWWW--m-m---W------------------L"},
		{"L----------------------WWWWWWWWWWWWWWWWW-------WWWWWWWWWW------------------L"},
		{"L--------------------------------------------------------------------------L"},
		{"L--------------------------------------------------------------------------L"},
		{"L--------------------------------------------------------------------------L"},
		{"L--------------------------------------------------------------------------L"},
		{"LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL"}
	};

	const std::vector<std::string> _bossStage = {
		{"LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL"},
		{"L--------------------------------------------------------------------------L"},
		{"L--------------------------------------------------------------------------L"},
		{"L------------------------------------WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW-L"},
		{"L------------------------------------WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW-L"},
		{"L------------------------------------WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW-L"},
		{"L------------------------------------WWWW------------------------------WWW-L"},
		{"L--WWWWWWWWWWWWWWWWWWW---------------WWWW-----------------F--F--F--F--FWWW-L"},
		{"L--WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--------F--F--F---------WWWWWWWWW-L"},
		{"L--WW---------------WWWWWWWWWWWWWWWWWWWWW---F-------------------W----TTTWW-L"},
		{"L--WW-------P--------------------------------------------------B----TTTTWW-L"},
		{"L--WW---------------WWWWWWWWWWWWWWWWWWWWW---F-------------------W----TTTWW-L"},
		{"L--WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--------F--F--F---------WWWWWWWWW-L"},
		{"L--WWWWWWWWWWWWWWWWWWW---------------WWWW-----------------F--F--F--F--FWWW-L"},
		{"L------------------------------------WWWW------------------------------WWW-L"},
		{"L------------------------------------WWWW------------------------------WWW-L"},
		{"L------------------------------------WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW-L"},
		{"L------------------------------------WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW-L"},
		{"L------------------------------------WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW-L"},
		{"L--------------------------------------------------------------------------L"},
		{"L--------------------------------------------------------------------------L"},
		{"LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL"}
	};
};