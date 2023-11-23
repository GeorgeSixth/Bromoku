//
// Arbiter.cpp for  in /home/de-vie_f//Bromoku/sources
//
// Made by fabien de-vienne
// Login   <de-vie_f@epitech.net>
//
// Started on Wed Nov 28 12:02:50 2012 fabien de-vienne
// Last update Thu Jan 17 16:23:30 2013 fabien de-vienne
//

#include "Game.hpp"

extern bool option[3];

Game::Arbiter::Arbiter(Game *goban)
{
  this->_game = goban;
}

Game::Arbiter::~Arbiter()
{
}

int		Game::Arbiter::checkFreePos(const uint &x, const uint &y)
{
  if (this->_game->getMap()->getPoint(x, y) == NONE)
    return 0;
  return (-1);
}

Game::t_result	*Game::Arbiter::verifArbiter(const uint &x, const uint &y, const Case &playerColor)
{
  uint i = 0;
  uint j = 0;
  int poss = 0;
  t_result *ret = new t_result;

  poss = checkFreePos(x, y);
  if (poss >= 0)
    {
      this->_game->getMap()->setPoint(x, y, playerColor);
      while ((j < 19) && (poss >= 0))
	{
	  if (this->getColor(i, j) == playerColor)
	    if (option[0] == true)
	      poss += checkDouble3(i, j, playerColor);
	  ++i;
	  if (i == 19)
	    {
	      j += 1;
	      i = 0;
	    }
	}
      this->_game->getMap()->deletePawn(x, y);
    }
  if (poss < 0)
    {
      ret->_move = false;
      return (ret);
    }
  ret->_move = true;
  ret->_eat = checkDestroy(x, y, &(ret->_eatingPoint), playerColor);
  this->_game->getMap()->setPoint(x, y, playerColor);
  ret->_win = checkVictory(x, y, playerColor);
  this->_game->getMap()->deletePawn(x, y);
  return (ret);
}

Game::Case	Game::Arbiter::getColor(const uint &x, const uint &y) const
{
  return this->_game->getMap()->getPoint(x, y);
}

int		Game::Arbiter::checkDouble3(const uint &x, const uint &y, const Case &color)
{
  int i, j, nb, tmp, test;

  i = nb = tmp = test = 0;
  j = 1;
  while (test < 4 && nb < 2)
    {
      while (tmp < 2 && nb < 2)
	{
	  if (((x + i) >= 0) && ((x + i) < 19) && ((y + j) >= 0) && ((y +j) < 19))
	    {
	      if (this->getColor(x + i, y + j) == color)
		{
		  if (((((x + i+i) >= 0) && ((x + i+i) < 19) && ((y + j+j) >= 0) && ((y +j+j) < 19)) && (this->getColor(x + i+i, y + j+j) == color)) &&
		      ((((x + i+i+i) >= 0) && ((x + i+i+i) < 19) && ((y + j+j+j) >= 0) && ((y +j+j+j) < 19)) && (this->getColor(x + i+i+i, y + j+j+j) == NONE) &&
		       (((x - i) >= 0) && ((x - i) < 19) && ((y - j) >= 0) && ((y -j) < 19)) && (this->getColor(x - i, y - j) == NONE)))
		    nb += 1;
		  else if (((((x + i+i) >= 0) && ((x + i+i) < 19) && ((y + j+j) >= 0) && ((y +j+j) < 19)) && (this->getColor(x + i+i, y + j+j) == NONE)) &&
			   ((((x + i+i+i) >= 0) && ((x + i+i+i) < 19) && ((y + j+j+j) >= 0) && ((y +j+j+j) < 19)) && (this->getColor(x + i+i+i, y + j+j+j) == color)) &&
			   ((((x + i+i+i+i) >= 0) && ((x + i+i+i+i) < 19) && ((y + j+j+j+j) >= 0) && ((y +j+j+j+j) < 19)) && (this->getColor(x + i+i+i+i, y + j+j+j+j) == NONE) &&
			    (((x - i) >= 0) && ((x - i) < 19) && ((y - j) >= 0) && ((y -j) < 19)) && (this->getColor(x - i, y - j) == NONE)))
		    nb += 1;
		}
	      else if (this->getColor(x + i, y + j) == NONE)
		if (((((x + i+i) >= 0) && ((x + i+i) < 19) && ((y + j+j) >= 0) && ((y +j+j) < 19)) && (this->getColor(x + i+i, y + j+j) == color)) &&
		    ((((x + i+i+i) >= 0) && ((x + i+i+i) < 19) && ((y + j+j+j) >= 0) && ((y +j+j+j) < 19)) && (this->getColor(x + i+i+i, y + j+j+j) == color)) &&
		    ((((x + i+i+i+i) >= 0) && ((x + i+i+i+i) < 19) && ((y + j+j+j+j) >= 0) && ((y +j+j+j+j) < 19)) && (this->getColor(x + i+i+i+i, y + j+j+j+j) == NONE) &&
		     (((x - i) >= 0) && ((x - i) < 19) && ((y - j) >= 0) && ((y -j) < 19)) && (this->getColor(x - i, y - j) == NONE)))
		  nb += 1;
	    }
	  i = i * (-1);
	  j = j * (-1);
	  ++tmp;
	}
      tmp = 0;
      if (nb < 2)
	{
	  if (((x + i) >= 0) && ((x + i) < 19) && ((y + j) >= 0) && ((y +j) < 19) && (this->getColor(x + i, y + j) == color))
	    {
	      if ((((x - i) >= 0) && ((x - i) < 19) && ((y - j) >= 0) && ((y - j) < 19) && (this->getColor(x - i, y - j) == color)) &&
		  (((x - i-i) >= 0) && ((x - i-i) < 19) && ((y - j-j) >= 0) && ((y - j-j) < 19) && (this->getColor(x - i-i, y - j-j) == NONE) &&
		   ((x + i+i) >= 0) && ((x + i+i) < 19) && ((y + j+j) >= 0) && ((y + j+j) < 19) && (this->getColor(x + i+i, y + j+j) == NONE)))
		nb += 1;
	      else if ((((x - i) >= 0) && ((x - i) < 19) && ((y - j) >= 0) && ((y - j) < 19) && (this->getColor(x - i, y - j) == NONE)) &&
		       (((x - i-i) >= 0) && ((x - i-i) < 19) && ((y - j-j) >= 0) && ((y - j-j) < 19) && (this->getColor(x - i-i, y - j-j) == color)) &&
		       (((x - i-i-i) >= 0) && ((x - i-i-i) < 19) && ((y - j-j-j) >= 0) && ((y - j-j-j) < 19) && (this->getColor(x - i-i-i, y - j-j-j) == NONE) &&
			((x + i+i) >= 0) && ((x + i+i) < 19) && ((y + j+j) >= 0) && ((y + j+j) < 19) && (this->getColor(x + i+i, y + j+j) == NONE)))
		nb += 1;
	    }
	  else if ((((x + i) >= 0) && ((x + i) < 19) && ((y + j) >= 0) && ((y +j) < 19) && (this->getColor(x + i, y + j) == NONE)) &&
		   (((x + i+i) >= 0) && ((x + i+i) < 19) && ((y + j+j) >= 0) && ((y +j+j) < 19) && (this->getColor(x + i+i, y + j+j) == color)) &&
		   (((x - i) >= 0) && ((x - i) < 19) && ((y - j) >= 0) && ((y - j) < 19) && (this->getColor(x - i, y - j) == color)) &&
		   (((x + i+i+i) >= 0) && ((x + i+i+i) < 19) && ((y + j+j+j) >= 0) && ((y + j+j+j) < 19) && (this->getColor(x + i+i+i, y + j+j+j) == NONE) &&
		    ((x - i-i) >= 0) && ((x - i-i) < 19) && ((y - j-j) >= 0) && ((y - j-j) < 19) && (this->getColor(x - i-i, y - j-j) == NONE)))
	    nb += 1;
	}
      ++test;
      if (i == -1)
	j = j - 1;
      if (i != (-1))
	i = i - 1;
    }
  if (nb < 2)
    return 0;
  return (-1);
}

bool		Game::Arbiter::checkDestroy(const uint &x, const uint &y, vpair *eat, const Case &color)
{
  bool          ifEat = false;
  int           i, j;

  i = j = -1;
  while (i < 2)
    {
      if (i == 0 && j == 0)
        ++j;
      if ((((x + i+i+i) >= 0) && ((x + i+i+i) < 19) && ((y + j+j+j) >= 0) && ((y +j+j+j) < 19)) &&
          (this->getColor(x + i+i+i, y + j+j+j) == color) &&
          ((this->getColor(x + i+i, y + j+j) != NONE) && (this->getColor(x + i+i, y + j+j) != color)) &&
          ((this->getColor(x + i, y + j) != NONE) && (this->getColor(x + i, y + j) != color)))
        {
          eat->push_back(std::pair<uint, uint>(x + i, y + j));
          eat->push_back(std::pair<uint, uint>(x + i+i, y + j+j));
          ifEat = true;
        }
      if (j == 1)
        {
          ++i;
          j = -1;
        }
      else
        ++j;
    }
  return ifEat;
}

bool		Game::Arbiter::checkVictory(const uint &x, const uint &y, const Case &color)
{
  int k,l, nb, tmp, test, x1, y1;

  long i;
  long j;

  i = 0;
  j = 1;
  k = nb = tmp = test = 0;
  l = 1;

  while (test < 4)
    {
      std::vector<std::pair<uint, uint> > tr;
      this->tab.push_back(tr);
      while (tmp < 2)
	{
	  k = i;
	  l = j;
	  while ((((x + k) >= 0) && ((x + k) < 19) && ((y + l) >= 0) && ((y + l) < 19)) && (this->getColor(x + k, y + l) == color) && (nb < 4))
	    {
	      if (this->tab[this->tab.size() - 1].size() != 0)
		{
		  this->tab[this->tab.size() - 1].push_back(std::pair<uint, uint>(x+k, y+l));
		  if ((this->tab[this->tab.size() - 1][this->tab[this->tab.size() - 1].size() - 1].first +
		       this->tab[this->tab.size() - 1][this->tab[this->tab.size() - 1].size() - 1].second) >
		      (this->tab[this->tab.size() - 1][0].first + this->tab[this->tab.size() - 1][0].second))
		    std::rotate(this->tab[this->tab.size() - 1].begin(), this->tab[this->tab.size() - 1].end() -1, this->tab[this->tab.size() - 1].end());
		}
	      else
		this->tab[this->tab.size() - 1].push_back(std::pair<uint, uint>(x+k, y+l));
	      ++nb;
	      k = k + i;
	      l = l + j;
	    }
	  nb = 0;
	  i = i * (-1);
	  j = j * (-1);
	  if (tmp == 0)
	    {
	      this->tab[this->tab.size() - 1].push_back(std::pair<uint, uint>(x, y));
	      if ((this->tab[this->tab.size() - 1][this->tab[this->tab.size() - 1].size() - 1].first +
		   this->tab[this->tab.size() - 1][this->tab[this->tab.size() - 1].size() - 1].second) >
		  (this->tab[this->tab.size() - 1][0].first + this->tab[this->tab.size() - 1][0].second))
		std::rotate(this->tab[this->tab.size() - 1].begin(), this->tab[this->tab.size() - 1].end() -1, this->tab[this->tab.size() - 1].end());
	    }
	  ++tmp;
	}
      if (this->tab[this->tab.size() - 1].size() < 5)
	this->tab.pop_back();
      if (i == (-1))
	j = j - 1;
      if (i != (-1))
	i = i - 1;
      test++;
      tmp = 0;
    }

  //-----------------------------------------------------------------------------------------------------------

  tmp = 0;
  while (tmp < this->tab.size())
    {
      i = 0;
      while (i < this->tab[tmp].size())
	{
	  if (this->getColor(this->tab[tmp][i].first, this->tab[tmp][i].second) == color)
	    {
	      i = 0;
	      while (i < this->tab[tmp].size())
		{
		  if ((this->getColor(this->tab[tmp][i].first, this->tab[tmp][i].second) == NONE) && ((this->tab[tmp][i].first != x) && (this->tab[tmp][i].second != y)))
		    {

		      if (i < ((this->tab[tmp].size() / 2) + (this->tab[tmp].size() % 2)))
			this->tab[tmp].erase(this->tab[tmp].begin(), this->tab[tmp].begin() + (i+1));
		      else if (i > ((this->tab[tmp].size() / 2) + (this->tab[tmp].size() % 2)))
			this->tab[tmp].erase(this->tab[tmp].begin() + i, this->tab[tmp].end());
		      else
			for (int a = 0; this->tab[tmp].size() > 0; a++)
			  this->tab[tmp].pop_back();
		      i = 0;
		    }
		  else
		    ++i;
		}
	      i = this->tab[tmp].size();
	    }
	  ++i;
	}
      if (this->tab[tmp].size() < 5)
	this->tab.erase(this->tab.begin() + tmp);
      ++tmp;
    }


  //-----------------------------------------------------------------------------------------------------------

  int ta;
  i = 0;
  j = 1;
  k = nb = tmp = test = 0;
  l = 1;

  for (int pos = 0; pos < this->tab.size(); pos++)
    {
      for (int ver = 0; ((this->tab[pos].size() - ver) > 4) && (this->getColor(this->tab[pos][0].first, this->tab[pos][0].second) == color) ; ver++)
	{
	  ta = ver;
	  nb = 0;
	  for (int tt = 0; ((tt < 5) && (nb == 0)); tt++)
	    {
	      i = 0;
	      j = 1;
	      x1 = this->tab[pos][ta].first;
	      y1 = this->tab[pos][ta].second;
	      while (test < 4 && nb == 0 && option[1] == true)
		{
		  tmp = 0;
		  while (tmp < 2)
		    {
		      if (((x1 + i) >= 0) && ((x1 + i) < 19) && ((y1 + j) >= 0) && ((y1 +j) < 19) &&
			  (this->getColor(x1 + i, y1 + j) == color))
			{
			  if (((x1 + i+i) >= 0) && ((x1 + i+i) < 19) && ((y1 + j+j) >= 0) && ((y1 +j+j) < 19) &&
			      (this->getColor(x1 + i+i, y1 + j+j) != color) && (this->getColor(x1 + i+i, y1 + j+j) != NONE) &&
			      ((x1 - i) >= 0) && ((x1 - i) < 19) && ((y1 - j) >= 0) && ((y1 -j) < 19) &&
			      (this->getColor(x1 - i, y1 - j) == NONE))
			  {
			    ++nb;
			  }
			  if (((x1 + i+i) >= 0) && ((x1 + i+i) < 19) && ((y1 + j+j) >= 0) && ((y1 +j+j) < 19) &&
			      ((this->getColor(x1 + i+i, y1 + j+j) == NONE) && 
			       ((x1 - i) >= 0) && ((x1 - i) < 19) && ((y1 - j) >= 0) && ((y1 -j) < 19) &&
			       (this->getColor(x1 - i, y1 - j) != NONE) && (this->getColor(x1 - i, y1 - j) != color)))
			  {
			    ++nb;
			  }
			}
		      i = i * (-1);
		      j = j * (-1);
		      ++tmp;
		    }
		  if (i == (-1))
		    j = j - 1;
		  if (i != (-1))
		    i = i - 1;
		  ++test;
		}
	      test = 0;
	      ++ta;
	    }
	  if (nb == 0)
	    {
	      return true;
	    }
	}
    }

  return false;
}
