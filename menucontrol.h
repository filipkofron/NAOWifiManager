#pragma once

#include "eventhandler.h"

class MenuController : public IInputEventHandler
{
public:
  virtual void OnUp();
  virtual void OnDown();
  virtual void OnEnter();
};
