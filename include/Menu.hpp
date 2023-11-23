//
// Menu.hpp for Epitech in /home/french_g//PROJETS/Gomoku/Graphique
//
// Made by george french
// Login   <french_g@pc-french-g>
//
// Started on Tue Nov 27 18:30:03 2012 george french
// Last update Wed Nov 28 12:58:42 2012 george french
//

#ifndef MENU_HPP_
# define MENU_HPP_

class Menu
{

public :

  Menu();
  ~Menu();

  uint		launchMenu();
  uint		eventPoller();

  int		chooseMode(int, int);

  void		drawBreaking();
  void		drawDoubleThree();
  void		drawMusic();

  void		refreshMenuOpts();

private :

  sf::RenderWindow	App;

  sf::Image		MenuIm;
  sf::Image		IconIm;
  sf::Image		OptsIm;
  sf::Image		CrosIm;

  sf::Sprite		MenuAff;
  sf::Sprite		IconAff;
  sf::Sprite		OptsAff;
  sf::Sprite		CrosAff;

  bool			running;
  bool			opt;
  bool			breakingFive;
  bool			doubleThree;
  bool			music;
};

#endif /* MENU_HPP_ */
