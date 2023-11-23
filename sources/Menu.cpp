#include <unistd.h>
#include "Game.hpp"
#include "Render.hpp"
#include "Menu.hpp"

extern bool		option[3];

Menu::Menu()
  : App(sf::VideoMode(880, 880, 32), "Bromoku", sf::Style::Close)
{
  if (!this->MenuIm.LoadFromFile("./Textures/Menu.png"))
    {
      std::cout << "Cannot find Menu.png." << std::endl;
      exit(EXIT_FAILURE);
    }
  if (!this->IconIm.LoadFromFile("./Textures/WaterIcon.png"))
    {
      std::cout << "Cannot find WaterIcon.png" << std::endl;
      exit(EXIT_FAILURE);
    }
  if (!this->OptsIm.LoadFromFile("./Textures/Option.png"))
    {
      std::cout << "Cannot find Option.png" << std::endl;
      exit(EXIT_FAILURE);
    }
  if (!this->CrosIm.LoadFromFile("./Textures/Cross.png"))
    {
      std::cout << "Cannot find Cross.png" << std::endl;
      exit(EXIT_FAILURE);
    }

  this->MenuAff.SetImage(this->MenuIm);
  this->IconAff.SetImage(this->IconIm);
  this->OptsAff.SetImage(this->OptsIm);
  this->CrosAff.SetImage(this->CrosIm);

  this->running = true;
  this->opt = false;
  this->breakingFive = true;
  this->doubleThree = true;
  this->music = true;
}

Menu::~Menu()
{

}

int		Menu::chooseMode(int x, int y)
{
  if (((x >= 200 && x <= 680) && (y >= 560 && y <= 649)) && this->opt == false)
    return (1);
  else if (((x >= 200 && x <= 680) && (y >= 650 && y <= 730)) && this->opt == false)
    return (2);
  else if (((x >= 700 && x <= 880) && (y >= 0 && y <= 50)) && this->opt == false)
    {
      this->App.Draw(this->OptsAff);
      this->App.Display();
      this->opt = true;
    }
  else if (((x >= 650 && x <= 880) && (y >= 820 && y <= 850)) && this->opt == true)
    {
      this->App.Draw(this->MenuAff);
      this->App.Display();
      this->opt = false;
    }
  else if (((x >= 125 && x <= 750) && (y >= 475 && y <= 550)) && this->opt == true)
    {
      //      ~(this->doubleThree);
      if (this->doubleThree == true)
	this->doubleThree = false;
      else if (this->doubleThree == false)
	this->doubleThree = true;
      this->drawDoubleThree();
      option[0] = this->doubleThree;
    }
  else if (((x >= 125 && x <= 750) && (y >= 551 && y <= 626)) && this->opt == true)
    {
      //      ~(this->breakingFive);
      if (this->breakingFive == true)
	this->breakingFive = false;
      else if (this->breakingFive == false)
	this->breakingFive = true;
      this->drawBreaking();
      option[1] = this->breakingFive;
    }
  else if (((x >= 0 && x <= 100) && (y >= 825 && y <= 880)) && this->opt == true)
    {
      //	~(this->music);
      if (this->music == true)
	this->music = false;
      else if (this->music == false)
	this->music = true;
      this->drawMusic();
      option[2] = this->music;
    }

  if (this->opt == true)
    refreshMenuOpts();

  return 0;
}

uint            Menu::eventPoller()
{
  sf::Event             Event;

  while ((this->App).GetEvent(Event))
    {
      uint		mode = 0;

      switch (Event.Type)
	{
	case sf::Event::Closed :
	  (this->App).Close();
          exit(EXIT_SUCCESS);
	  break;
	case sf::Event::KeyPressed :
	  switch (Event.Key.Code)
	    {
	    case sf::Key::Escape :
	      (this->App).Close();
	      exit(EXIT_SUCCESS);
	      break;
	    default:
	      break;
	    }
	  break;
	case sf::Event::MouseButtonReleased :
	  mode = this->chooseMode(Event.MouseButton.X, Event.MouseButton.Y);
	  break;	  
	default:
	  break;
	}

      if (mode != 0)
	{
	  this->running = false;
	  (this->App).Close();
	  return mode;
	}
    }
}

uint		Menu::launchMenu()
{
  uint		mode;

  this->App.Draw(this->MenuAff);
  this->App.Display();
  while (this->running)
    mode = this->eventPoller();
  return mode;
}

void		Menu::drawDoubleThree()
{
  if (this->doubleThree == true)
    {
      this->CrosAff.SetX(677);
      this->CrosAff.SetY(491);
      this->App.Draw(this->CrosAff);
      this->App.Display();
    }
}

void		Menu::drawBreaking()
{
  if (this->breakingFive == true)
    {
      this->CrosAff.SetX(677);
      this->CrosAff.SetY(602);
      this->App.Draw(this->CrosAff);
      this->App.Display();
    }
}

void		Menu::drawMusic()
{
  if (this->music == true)
    {
      this->CrosAff.SetX(77);
      this->CrosAff.SetY(860);
      this->App.Draw(this->CrosAff);
      this->App.Display();
    }
}

void		Menu::refreshMenuOpts()
{
  this->App.Draw(this->OptsAff);

  if (this->breakingFive == true)
    {
      this->CrosAff.SetX(677);
      this->CrosAff.SetY(602);
      this->App.Draw(this->CrosAff);
    }
  if (this->doubleThree == true)
    {
      this->CrosAff.SetX(677);
      this->CrosAff.SetY(491);
      this->App.Draw(this->CrosAff);
    }
  if (this->music == true)
    {
      this->CrosAff.SetX(77);
      this->CrosAff.SetY(860);
      this->App.Draw(this->CrosAff);
    }
  this->App.Display();
}
