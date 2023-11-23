//
// Map.cpp for  in /home/de-vie_f//Gomoku
//
// Made by fabien de-vienne
// Login   <de-vie_f@epitech.net>
//
// Started on Mon Nov 26 19:53:48 2012 fabien de-vienne
// Last update Mon Nov 26 22:22:24 2012 fabien de-vienne
//

#include "Game.hpp"

Game::Map::Map()
{
  int i = 0;
  while (i < 12)
    {
      this->_pawns[i] = 0;
      // *(this->_pawns) &= ~(1 << i);
      ++i;
    }
  i = 0;
  while (i < 12)
    {
      this->_presence[i] = 0;
      // *(this->_presence) &= ~(1 << i);
      ++i;
    }
}

Game::Map::~Map()
{
}

Game::Case	Game::Map::getPoint(const uint &x, const uint &y) const
{
  int i = (y * 19) + x;
  int j = i / 32;

  i = i % 32;
  if ((this->_presence[j] & (1 << i)))
    {
      if ((this->_pawns[j] & (1 << i)))
	return RED;
      return BLUE;
    }
  return NONE;
}

void		Game::Map::setPoint(const uint &x, const uint &y, Case point)
{
  int i = (y * 19) + x;
  int j = i / 32;

  i = i % 32;
  switch (point)
    {
    case NONE:
      this->_presence[j] &= ~(1 << i);
      break;
    case RED:
      this->_presence[j] |= (1 << i);
      this->_pawns[j] |= (1 << i);
      break;
    case BLUE:
      this->_presence[j] |= (1 << i);
      this->_pawns[j] &= ~(1 << i);
      break;
    }
}

void		Game::Map::deletePawn(const uint &x, const uint &y)
{
  this->setPoint(x, y, NONE);
}
