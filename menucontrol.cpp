#include "menucontrol.h"
#include <iostream>

void MenuController::OnUp()
{
  std::cout << "OnUp" << std::endl;
}

void MenuController::OnDown()
{
  std::cout << "OnDown" << std::endl;
}

void MenuController::OnEnter()
{
  std::cout << "OnEnter" << std::endl;
}

void MenuController::OnStart()
{
  std::cout << "OnStart" << std::endl;
}
