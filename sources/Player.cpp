//
// Player.cpp for  in /home/de-vie_f//Gomoku
//
// Made by fabien de-vienne
// Login   <de-vie_f@epitech.net>
//
// Started on Mon Nov 26 17:17:36 2012 fabien de-vienne
// Last update Wed Jan 16 20:19:51 2013 fabien de-vienne
//

#include "Game.hpp"

Game::Player::Player(const int& id)
{
  this->_id = id;
  this->_nbPawnsEat = 0;
  this->_nbRows = 0;
  if (this->_id == (-1))
    this->_color = RED;
  else
    this->_color = BLUE;
}

Game::Player::~Player(void)
{
}

uint		Game::Player::getPawns() const
{
  return this->_nbPawnsEat;
}

void		Game::Player::setPawns(const uint &i)
{
  this->_nbPawnsEat = i;
}

uint		Game::Player::getRows() const
{
  return this->_nbRows;
}

void		Game::Player::setRows(const uint &i)
{
  this->_nbRows = i;
}

Game::Case	Game::Player::getColor() const
{
  return this->_color;
}

bool		Game::Player::play(const uint &x, const uint &y, Map *map, Arbiter *arbiter, bool *t)
{
  t_result	*res;

  res = arbiter->verifArbiter(x, y, this->_color);
  if (res->_move)
    {
      map->setPoint(x, y, this->_color);
      if (res->_eat)
	{
	  this->_nbPawnsEat += res->_eatingPoint.size();
	  for (int i = 0; i != res->_eatingPoint.size(); ++i)
	    map->deletePawn(res->_eatingPoint[i].first, res->_eatingPoint[i].second);
	}
      if (this->_nbPawnsEat >= 10 || res->_win)
	{
	  delete res;
	  this->win();
	  return false;
	}
      delete res;
      (*t) = true;
      return true;
    }
  delete res;
  (*t) = false;
  return true;
}

void		Game::Player::win()
{
}
