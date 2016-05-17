#include <iostream>
#include "config.h"
#include "globals.h"

#define CHAR_READER_PATH "/etc/wifilist"

CharReader::CharReader(const boost::shared_ptr<std::ifstream>& file)
  : _file(file)
{
}

int CharReader::Next()
{
  int ret = -1;

  if (IsEOF())
    return ret;

  if (_preread.size() > 0)
  {
    ret = _preread[_preread.size() - 1];
    _preread.pop_back();
    return ret;
  }

  return _file->get();
}

int CharReader::Peek()
{
  int ret = -1;

  if (IsEOF())
    return ret;

  if (_preread.size() > 0)
  {
    ret = _preread[_preread.size() - 1];
    return ret;
  }

  ret = _file->get();
  _preread.push_back(ret);
  return ret;
}

bool CharReader::IsWhitespace(int c)
{
  return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

bool CharReader::IsChar(int c)
{
  return c != -1;
}

int CharReader::NextNoWhitespace()
{
  int c = Next();
  if (IsWhitespace(c))
    return NextNoWhitespace();

  return c;
}

int CharReader::PeekNoWhitespace()
{
  if (IsWhitespace(Peek()))
  {
    Next();
    return PeekNoWhitespace();
  }
  return Peek();
}

bool CharReader::IsEOF() const
{
  return _preread.size() == 0 && _file->fail();
}

bool ParamEntry::Contains(const std::string& name) const
{
  return _pairs.find(name) != _pairs.end();
}

std::string ParamEntry::operator [] (const std::string& name) const
{
  std::string ret;
  std::map<std::string, std::string>::const_iterator iter(_pairs.find(name));
  if (iter != _pairs.end())
    ret = iter->second;

  return ret;
}

boost::shared_ptr<ParamEntry> ParamEntry::_root;

void ParamEntry::Reload()
{
  _globs->_glob_config = boost::shared_ptr<ParamEntry>(new ParamEntry);
  boost::shared_ptr<std::ifstream> file = boost::shared_ptr<std::ifstream>(new std::ifstream(CHAR_READER_PATH));
  CharReader charReader(file);
  _globs->_glob_config->Load(charReader);
}


bool ParamEntry::LoadEntry(CharReader& charReader)
{
  std::string name;
  std::string value;
  while (CharReader::IsChar(charReader.PeekNoWhitespace()))
  {
    int c = charReader.PeekNoWhitespace();
    if (c == ':')
    {
      charReader.NextNoWhitespace();
      break;
    }
    name += c;
    charReader.NextNoWhitespace();
  }
  if (charReader.NextNoWhitespace() != '"')
  {
    std::cerr << "Error: Invalid entry!" << std::endl;
    return false;
  }

  while (CharReader::IsChar(charReader.PeekNoWhitespace()))
  {
    int c = charReader.PeekNoWhitespace();
    if (c == '"')
    {
      charReader.NextNoWhitespace();
      _pairs[name] = value;
      return true;
    }
    value += c;
    charReader.NextNoWhitespace();
  }
  std::cerr << "Error: Invalid entry " << name << std::endl;
  return false;
}

bool ParamEntry::LoadSubEntry(CharReader& charReader)
{
  boost::shared_ptr<ParamEntry> entry = boost::shared_ptr<ParamEntry>(new ParamEntry);
  bool res = entry->Load(charReader);
  if (res)
    _entries.push_back(entry);
  return res;
}

bool ParamEntry::Load(CharReader& charReader)
{
  while (CharReader::IsChar(charReader.PeekNoWhitespace()))
  {
    int c = charReader.PeekNoWhitespace();
    if (c == '{')
    {
      charReader.NextNoWhitespace();
      if (!LoadSubEntry(charReader))
        return false;
    }
    else if (c == '}')
    {
      charReader.NextNoWhitespace();
      return true;
    }
    else
    {
      if (!LoadEntry(charReader))
        return false;
    }
  }
  return true;
}

void ParamEntry::PrintOn(std::ostream& os)
{
  for (std::map<std::string, std::string>::iterator it = _pairs.begin(); it != _pairs.end(); it++)
  {
    Log() << it->first << ": " << it->second << std::endl;
  }
  for (std::vector<boost::shared_ptr<ParamEntry> >::iterator it = _entries.begin(); it != _entries.end(); it++)
  {
    Log() << "{" << std::endl;
    (*it)->PrintOn(os);
    Log() << "}" << std::endl;
  }
}
