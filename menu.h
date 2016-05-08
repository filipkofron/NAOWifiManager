#pragma once

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

class IMenuHandler
{
public:
  virtual void Handle() = 0;
};

class MenuItem
{
private:
  boost::shared_ptr<IMenuHandler> _handler;
  std::string _name;

public:
  const boost::shared_ptr<IMenuHandler>& Handler() const { return _handler; }
  const std::string& Name() const { return _name; }

  boost::shared_ptr<IMenuHandler>& Handler() { return _handler; }
  std::string& Name() { return _name; }
  virtual void Announce();
};

class Menu
{
private:
  std::vector<boost::shared_ptr<MenuItem> > _items;
  int _index;
public:
  Menu() : _index(0) { _items.clear(); }
  void ClearItems();
  void AddItem(const boost::shared_ptr<MenuItem>& item);
  void OnUp();
  void OnDown();
  void OnEnter();
};
