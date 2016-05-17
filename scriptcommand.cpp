#include "scriptcommand.h"
#include "log.h"
#include <boost/shared_ptr.hpp>
#include <cstdio>
#include <memory>
#include <iostream>

bool ScriptCommand::Execute(std::string& out)
{
  std::string command = GetCommandString();
  Log() << "Executing: '" << command << std::endl;
  boost::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);

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
