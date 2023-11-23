//
// Game.cpp for  in /home/de-vie_f//Gomoku
//
// Made by fabien de-vienne
// Login   <de-vie_f@epitech.net>
//
// Started on Mon Nov 26 19:13:16 2012 fabien de-vienne
// Last update Thu Jan 17 16:33:05 2013 fabien de-vienne
//

#include "Game.hpp"
#include "Render.hpp"

Game::Game(const Mode &mode)
  : _gameMode(mode)
{
  this->_player1 = new Player(1);
  if (mode == 2)
    this->_player2 = new Player(-1);
  else
    this->_player2 = new Ia(-1, *(this->_map));
  this->_map = new Map();
  this->_arbiter = new Arbiter(this);
}

Game::~Game()
{
  delete this->_player1;
  delete this->_player2;
  delete this->_map;
  delete this->_arbiter;
}

void		Game::setClick(const uint &X, const uint &Y)
{
  this->_clickX = X;
  this->_clickY = Y;
}

Game::APlayer	*Game::getPlayer(const int &player) const
{
  if (player == 1)
    return (this->_player1);
  return (this->_player2);
}

Game::Map	*Game::getMap(void) const
{
  return this->_map;
}

Game::Arbiter	*Game::getArbiter(void) const
{
  return this->_arbiter;
}

Game::Mode		Game::getMode() const
{
  return (this->_gameMode);
}

int		Game::getTurn() const
{
  return (this->_turn);
}

void		Game::setGamemode(Mode const &mode)
{
  this->_gameMode = mode;
}

uint		Game::getClickX() const
{
  return (this->_clickX);
}

uint		Game::getClickY() const
{
  return (this->_clickY);
}

void		Game::setTurn()
{
  this->_turn *= -1;
}

void		Game::setFirstTurn()
{
  srand(time(NULL));
  int		i = rand();

  if (i % 2 == 0)
    this->_turn = -1;
  else
    this->_turn = 1;
}
