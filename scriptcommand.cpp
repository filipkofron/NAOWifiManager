#include "scriptcommand.h"
#include <cstdio>
#include <memory>
#include <iostream>

bool ScriptCommand::Execute(std::string& out)
{
  std::string command = GetCommandString();
  std::cout << "Executing: '" << command << std::endl;
  std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);

  if (!pipe)
    return false;

  char buffer[128];
  out = "";

  while (!feof(pipe.get()))
  {
    if (fgets(buffer, 128, pipe.get()) != NULL)
    {
      out += buffer;
    }
  }

  return true;
}
