//
// Render.hpp for Epitech in /home/french_g//PROJETS/Gomoku/Graphique/Include
//
// Made by george french
// Login   <french_g@pc-french-g>
//
// Started on Mon Nov 26 18:41:20 2012 george french
// Last update Thu Jan 17 16:27:20 2013 fabien de-vienne
//

#ifndef RENDER_HPP_
# define RENDER_HPP_

#include <iostream>
#include <time.h>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.hpp"

typedef enum
{
  NONE,
  BLUE,
  RED
}	content;


class Render
{

public :

  Render(Game *);
  ~Render();

  void	drawGrid(void);
  void	drawCoin(void);
  void	drawPlayers(void);
  void	drawScore(void);
  void	drawEnd();

  bool	eventPoller(unsigned int, int);
  bool	init(void);

  bool	getRunning(void);
  void	setRunning(bool);

  void	refresh(void);

  sf::RenderWindow		App;

private :


  sf::Image			Background;
  sf::Image			Red;
  sf::Image			Blue;
  sf::Image			Machine;
  sf::Image			None;
  sf::Image                     RedPlayer;
  sf::Image                     RedPlayerS;
  sf::Image                     BluPlayer;
  sf::Image                     BluPlayerS;
  sf::Image			loader;
  sf::Image			GameOver;
  sf::Image			option1;

  sf::Sprite			Wallpaper;
  sf::Sprite			RedCoin;
  sf::Sprite			BluCoin;
  sf::Sprite			AiCoin;
  sf::Sprite			NoneCoin;
  sf::Sprite			Coin;
  sf::Sprite                    RedP;
  sf::Sprite                    RedPs;
  sf::Sprite                    BluP;
  sf::Sprite                    BluPs;
  sf::Sprite			LoaderIm;
  sf::Sprite			_gameOver;
  sf::Sprite			_option;
  sf::Sprite			RedScore;
  sf::Sprite			BluScore;

  sf::Music			_ambiant;
  sf::SoundBuffer		_buf;
  sf::Sound			_sand;

  sf::Font			MyFont;

  sf::String			Text;

  bool				running;
  bool				wait;
  Game				*_game;
};

#endif /* RENDER_HPP_ */
