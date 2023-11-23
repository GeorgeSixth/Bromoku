//
// alphaBeta.cpp for  in /home/de-vie_f//Bromoku/AlphaBeta
//
// Made by fabien de-vienne
// Login   <de-vie_f@epitech.net>
//
// Started on Wed Jan 16 13:25:51 2013 fabien de-vienne
// Last update Thu Jan 17 18:45:19 2013 fabien de-vienne
//

#include "Game.hpp"

Game::Ia::Ia(const int& id, Map m)
  : map(m), level(0)
{
  this->_id = id;
  this->_nbPawnsEat = 0;
  this->_nbRows = 0;
  if (this->_id == (-1))
    this->_color = RED;
  else
    this->_color = BLUE;
  this->bestMove = std::make_pair(std::make_pair(0, 0), 0);
  this->state = CON;
}

Game::Ia::~Ia()
{

}

uint			Game::Ia::getPawns() const
{
  return this->_nbPawnsEat;
}

void			Game::Ia::setPawns(const uint &p)
{
  this->_nbPawnsEat = p;
}

uint			Game::Ia::getRows() const
{
  return this->_nbRows;
}

void			Game::Ia::setRows(const uint &r)
{
  this->_nbRows = r;
}

Game::Case		Game::Ia::getColor() const
{
  return this->_color;
}

std::vector<Game::Ia::Move>	Game::Ia::getMove(const uint x, const uint y)
{
  std::vector<Game::Ia::Move>	m;

  int	i = 1;
  int	j = 1;
  for (int t = 0; t < 4; t++)
    {
      for (int tt = 0; tt < 2; tt++)
	{
	  if (((x + i >= 0) && (x + i < 19)) &&
	      ((y + j >= 0) && (y + j < 19)) &&
	      !map.getPoint(x + i, y + j))
	    m.push_back(std::make_pair(std::make_pair(x + i, y + j), 0));
	  i = i * (-1);
	  j = j * (-1);
	}
      if (i == (-1))
	j = j - 1;
      else
	i = i - 1;
    }
  return m;
}

void			Game::Ia::delMove(Game::Ia::Move move)
{
  this->map.setPoint(move.first.first, move.first.second, NONE);
}

void			Game::Ia::doMove(Game::Ia::Move move, Case color)
{
  this->map.setPoint(move.first.first, move.first.second, color);
}

void			Game::Ia::getLine(int *value, Case color, const uint x, const uint y)
{
  int	tab[4];
  
  tab[0] = tab[1] = tab[2] = tab[3] = 1;
  for (int i = 0; i < 4; i++)
    {
      for (int k = 0; k < 2; k++)
	{
	  for (int j = 0; (j < 4) && 
		 ((tab[0] + x) < 19) && ((tab[0] + x) >= 0) && 
		 ((tab[1] + y) < 19) && ((tab[1] + y) >= 0) &&
		 (this->map.getPoint(tab[0] + x, tab[1] + y) == color); j++)
	    {
	      *value += 1;
	      tab[0] += tab[2];
	      tab[1] += tab[3];
	      // if (j == 0)
	      // 	*value -= 25;
	      if (j == 1)
		*value += 40;
	      else if (j == 2)
		*value += 15;
	      else if (j == 3)
		*value += 60;
	    }
	  tab[2] *= (-1);
	  tab[3] *= (-1);
	  tab[0] = tab[2];
	  tab[1] = tab[3];
	}
      switch (i)
	{
	case 0:
	  tab[0] = tab[2] = 0;
	  tab[1] = tab[3] = 1;
	  break;
	case 1:
	  tab[0] = tab[2] = (-1);
	  tab[1] = tab[3] = 1;
	  break;
	case 2:
	  tab[0] = tab[2] = 1;
	  tab[1] = tab[3] = 0;
	  break;
	default:
	  tab[0] = tab[1] = tab[2] = tab[3] = 1;
	  break;
	}
    }


  for (int i = 0; i < 4; i++)
    {
      for (int k = 0; k < 2; k++)
	{
	  for (int j = 0; (j < 4) && 
		 ((tab[0] + x) < 19) && ((tab[0] + x) >= 0) && 
		 ((tab[1] + y) < 19) && ((tab[1] + y) >= 0) &&
		 (this->map.getPoint(tab[0] + x, tab[1] + y) == ((Case)(color * (-1)))); j++)
	    {
	      *value += 1;
	      tab[0] += tab[2];
	      tab[1] += tab[3];
	      if (j == 1)
		*value += 10;
	      else if (j == 2)
		*value += 45;
	      else if (j == 3)
		*value += 40;
	    }
	  tab[2] *= (-1);
	  tab[3] *= (-1);
	  tab[0] = tab[2];
	  tab[1] = tab[3];
	}
      switch (i)
	{
	case 0:
	  tab[0] = tab[2] = 0;
	  tab[1] = tab[3] = 1;
	  break;
	case 1:
	  tab[0] = tab[2] = (-1);
	  tab[1] = tab[3] = 1;
	  break;
	case 2:
	  tab[0] = tab[2] = 1;
	  tab[1] = tab[3] = 0;
	  break;
	default:
	  tab[0] = tab[1] = tab[2] = tab[3] = 1;
	  break;
	}
    }
}

void				Game::Ia::checkMiamDiagonal(int *value, Case color,
					  const uint x, const uint y)
{
  uint pos_x = x + 1;
  uint pos_y = y + 1;

  if ((pos_x >= 0 && pos_x <= 18) && (pos_y >= 0 && pos_y <= 18) &&
      this->map.getPoint(pos_x, pos_y) == (Case)(color * (-1)) &&
      this->map.getPoint(pos_x + 1, pos_y + 1) == (Case)(color * (-1)) &&
      this->map.getPoint(pos_x + 2, pos_y + 2) == color)
    (*value) += 35;

  pos_x = x - 1;
  pos_y= y - 1;

  if ((pos_x >= 0 && pos_x <= 18) && (pos_y >= 0 && pos_y <= 18) &&
      this->map.getPoint(pos_x, pos_y) == (Case)(color * (-1)) &&
      this->map.getPoint(pos_x - 1, pos_y - 1) == (Case)(color * (-1)) &&
      this->map.getPoint(pos_x - 2, pos_y - 2) == color)
    (*value) += 35;
}

void				Game::Ia::checkMiamX(int *value, Case color, const uint x, const uint y)
{
  uint pos_x = x + 1;

  if ((pos_x >= 0 && pos_x <= 18) &&
      this->map.getPoint(pos_x, y) == (Case)(color * -1) &&
      this->map.getPoint(pos_x + 1, y) == (Case)(color * -1) &&
      this->map.getPoint(pos_x + 2, y) == color)
    (*value) += 35;

  pos_x = x - 1;

  if ((pos_x >= 0 && pos_x <= 18) &&
      this->map.getPoint(pos_x, y) == (Case)(color * -1) &&
      this->map.getPoint(pos_x - 1, y) == (Case)(color * -1) &&
      this->map.getPoint(pos_x - 2, y) == color)
    (*value) += 35;
}

void				Game::Ia::checkMiamY(int *value, Case color, const uint x, const uint y)
{
  uint pos_y = y + 1;

  if ((x >= 0 && x <= 18) &&
      this->map.getPoint(x, pos_y) == (Case)(color * -1) &&
      this->map.getPoint(x, pos_y + 1) == (Case)(color * -1) &&
      this->map.getPoint(x, pos_y + 2) == color)
    (*value) += 35;

  pos_y = y - 1;

  if ((x >= 0 && x <= 18) &&
      this->map.getPoint(x, pos_y) == (Case)(color* -1) &&
      this->map.getPoint(x, pos_y - 1) == (Case)(color * -1) &&
      this->map.getPoint(x, pos_y - 2) == color)
    (*value) += 35;
}

void				Game::Ia::checkMiam(int *value, Case color, const uint x, const uint y)
{
  checkMiamX(value, color, x, y);
  checkMiamY(value, color, x, y);
  checkMiamDiagonal(value, color, x, y);

}

int				Game::Ia::Value(Case color,
					const uint x, const uint y)
{
  int	value = 0;

  getLine(&value, color, x, y);
  checkMiam(&value, color, x, y);
  return value;
}

static bool			compare(Game::Ia::Move m1, Game::Ia::Move m2)
{
  return (m1.second > m2.second);
}

std::vector<Game::Ia::Move>	Game::Ia::sortMoves()
{
  std::sort(this->bestMoves.begin(), this->bestMoves.end(), compare);
  return this->bestMoves;
}

Game::Ia::Move		Game::Ia::algoIa(int x, int y)
{
  Game::Ia::Move better;
  better.first.first = x;
  better.first.second = y;
  better.second = Value(this->getColor(), x, y);
  return better;
}

std::vector<Game::Ia::Move>	Game::Ia::startAlgo(Map _map)
{
  vpair point;
  this->map = _map;
  for (int j = 0; j < 19; j++)
    {
      for (int i = 0; i < 19; i++)
	if (this->map.getPoint(i, j) != NONE)
	  point.push_back(std::pair<uint, uint>(i, j));
    }
  
  if (point.size() == 0)
    {
      Game::Ia::Move				better;
      better.first.first = 9;
      better.first.second = 9;
      better.second = 0;
      this->bestMoves.push_back(better);
      return this->bestMoves;
    }
  for (int k = 0; k < point.size(); k++)
    {
      std::vector<Game::Ia::Move>	moves = getMove(point[k].first, point[k].second);
      for (int l = 0; l < moves.size(); l++)
	this->bestMoves.push_back(this->algoIa(moves[l].first.first, moves[l].first.second));
    }
  this->sortMoves();
  return this->bestMoves;
}

bool			Game::Ia::play(const uint &X, const uint &Y, Map *map,
				       Arbiter *arbiter, bool *t)
{
  std::vector<Game::Ia::Move>	m;
  uint				x, y;
  t_result			*res;

  (void)X;
  (void)Y;
  m = startAlgo((*map));
  x = m.front().first.first;
  y = m.front().first.second;
  res = arbiter->verifArbiter(x, y, this->_color);
  while (!(res->_move))
    {
      delete res;
      x = m.front().first.first;
      y = m.front().first.second;
      res = arbiter->verifArbiter(x, y, this->_color);
      m.erase(m.begin(), m.begin()+1);
    }
  this->bestMoves.clear();
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

void		Game::Ia::win()
{
}
