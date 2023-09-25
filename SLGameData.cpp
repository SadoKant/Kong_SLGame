#include "SLGameData.h"

CharacterBasicStat::CharacterBasicStat()
{

}

CharacterBasicStat::CharacterBasicStat(int HP, int MP, int ATK, int DEF)
	: _HP(HP), _HP_Max(HP), _MP(MP), _MP_Max(MP), _ATK(ATK), _DEF(DEF)
{

}