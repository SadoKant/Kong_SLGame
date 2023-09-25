
#include <iostream>
#include "SLGameSystem.h"

int main()
{
    SLGameSystem& gameSystem = SLGameSystem::GetGameSystem();
    gameSystem.Start();
}