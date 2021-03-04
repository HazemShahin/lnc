#pragma once

#include <vector>
#include <string>

#include <Vec2.h>

#include "ShipPlacement.h"

enum class Cell {
  Unknown,
  Empty,
  Ship
};

class GameGrid {
public:
  GameGrid(const Vec2ui& gridSize=Vec2ui{10,10});

  void setShips(const ShipPlacement& sp);
  
  void addHit(const Vec2ui& pos);
  void addMiss(const Vec2ui& pos);

  bool validate(const std::string& encryptedString, const std::string& password);
  
  Vec2ui getSize() const {return gridSize;}
  Cell getCell(uint32_t x, uint32_t y) const;
  
private:
  Vec2ui gridSize;
  std::vector<Cell> grid;
  std::vector<Vec2ui> hits;
  std::vector<Vec2ui> misses;

  void clearEmpty();
  void clearUnknown();
  
  void addShip(const Vec2ui& pos);
  void setCell(uint32_t x, uint32_t y, Cell c);

};