#pragma once

#include <string>

class ScriptCommand
{
private:

public:
  virtual std::string GetCommandString() = 0;
  bool Execute(std::string& out);
};
