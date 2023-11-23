//
// main.cpp for Gomoku in /home/french_g//PROJETS/Gomoku/Graphique/srcs
//
// Made by george french
// Login   <french_g@epitech.net>
//
// Started on Mon Nov 26 19:19:09 2012 george french
// Last update Thu Jan 17 14:48:38 2013 fabien de-vienne
//

#include "Game.hpp"
#include "Render.hpp"
#include "Menu.hpp"

bool		option[3];

int		main()
{
  option[0] = option[1] = option[2] = true;
  Menu		MyMenu;
  uint		mode = MyMenu.launchMenu();
  Game		game((Game::Mode) mode);
  Render	field(&game);
  bool		run = true;
  bool		t;

  field.init();
  game.setClick(0, 0);
  game.setFirstTurn();
  while (run)
    {
      run = field.getRunning();
      if (run && field.eventPoller(mode, game.getTurn()))
      	{
	  run = game.getPlayer(game.getTurn())->play(game.getClickX(), game.getClickY(), game.getMap(), game.getArbiter(), &t);
	  if (t)
	    game.setTurn();
      	}
      field.drawCoin();
      field.drawPlayers();
      field.drawScore();
      field.App.Display();
      if (!run)
	{
	  field.drawCoin();
	  field.drawPlayers();
	  field.drawScore();
	  field.drawEnd();
	}
    }
  return 0;
}

