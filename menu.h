#pragma once

#include <string>
#include <vector>
#include <memory>

class IMenuHandler
{
public:
  virtual void Handle() = 0;
};

class MenuItem
{
private:
  std::shared_ptr<IMenuHandler> _handler;
  std::string _name;

public:
  const std::shared_ptr<IMenuHandler>& Handler() const { return _handler; }
  const std::string& Name() const { return _name; }

  std::shared_ptr<IMenuHandler>& Handler() { return _handler; }
  std::string& Name() { return _name; }
  virtual void Announce();
};

class Menu
{
private:
  std::vector<std::shared_ptr<MenuItem> > _items;
  int _index;
public:
  Menu() : _index(0) { _items.clear(); }
  void ClearItems();
  void AddItem(const std::shared_ptr<MenuItem>& item);
  void OnUp();
  void OnDown();
  void OnEnter();
};
