#pragma once

#include <boost/shared_ptr.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <map>

class CharReader
{
private:
  std::vector<int> _preread;
  boost::shared_ptr<std::ifstream> _file;
  bool IsWhitespace(int c);
public:
  CharReader(const boost::shared_ptr<std::ifstream>& file);
  int Next();
  int Peek();
  int NextNoWhitespace();
  int PeekNoWhitespace();
  bool IsEOF() const;
  static bool IsChar(int c);
};

class ParamEntry
{
private:
  std::map<std::string, std::string> _pairs;
  std::vector<boost::shared_ptr<ParamEntry> > _entries;
  static boost::shared_ptr<ParamEntry> _root;
  bool LoadEntry(CharReader& charReader);
  bool LoadSubEntry(CharReader& charReader);
  ParamEntry() { }

public:
  static void Reload();
  bool Load(CharReader& charReader);
  std::vector<boost::shared_ptr<ParamEntry> >& Entries() { return _entries; }
  const std::vector<boost::shared_ptr<ParamEntry> >& Entries() const { return _entries; }
  bool Contains(const std::string& name) const;
  std::string operator [] (const std::string& name) const;
  void PrintOn(std::ostream& os);
};
