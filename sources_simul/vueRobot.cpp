 /**
 * \brief     Definition de la classe vueRobot 
 *
 * \details   Cette classe presente les caracteristiques et comportement
 *				pour un modele de vue de deplacement du robot
 *
 *      
 *						! Compiler avec l'option -lncurses 
 *						
 *            ! Compiler win32 avec l'option -lpdcurses 
 *
 * \file      vueRobot.cpp
 * \author    cgil 
 * \version   2.0
 * \date      jan. 2020
 */
   
	 
	

#include "vueRobot.h"

#include <iostream>
#include <sstream>
using namespace std;


/**
* \brief	Constructeur de la classe vueRobot
*
* \details  un constructeur n a JAMAIS de type
*
* \return   JAMAIS
*/
VueRobot :: VueRobot()
{
	//! Initialise attributs par defaut
	xRobotInitial=0;
	yRobotInitial=0;
	xRobot=0;
	yRobot=0;
	yMin = 2;
	xMin = 20;
	xMax = 70;
	yMax = 18;
	
	//! Initialise curses
	initscr(); 				// Initialise la fenetre
	noecho(); 				// aucun echo
	curs_set(FALSE); 	// curseur pas affiche
	
	//! zone de deplacement robot => piscine
	creerZoneDeplacementPiscine();
	placerDepart ();  //! par defaut
	
}

/**
* \brief	deplacer en haut de distance
*/
void VueRobot::deplacerAvant (int distance)
{
	deplacer (xRobot, yRobot-distance);
}

/**
* \brief	deplacer en arriere de distance
*/
void VueRobot::deplacerArriere (int distance)
{

  deplacer (xRobot, yRobot+distance);
}

/**
* \brief	deplacer a droite de distance
*/
void VueRobot::deplacerDroite (int distance)
{
  deplacer (xRobot+distance, yRobot);
}

/**
* \brief	deplacer a gauche de distance
*/
void VueRobot::deplacerGauche (int distance)
{
  deplacer (xRobot-distance, yRobot);
}


/**
* \brief	deplace le robot en affichant "R" sur la position demandee
*
* efface position precedente 
*/
void VueRobot::deplacer (int _xRobotPrevu, int _yRobotPrevu)
{
	 

	//! Verifie position possible du robot
	if (detecterLimiteZone(_xRobotPrevu, _yRobotPrevu)) {
		char buffer[50] = "";
		sprintf (buffer, "hors limite [%d,%d]", _xRobotPrevu, _yRobotPrevu);
		mvprintw (yRobot, 0, buffer);
	} else {  //! deplacement complet accepte
	
		//! effectue un affichage progressif
		int delta = 0;
		if (_xRobotPrevu - xRobot > 0) {
			delta = _xRobotPrevu - xRobot;
			for (int i=0; i<delta; i++) 
				raffraichitRobot (xRobot+1, yRobot);
		}
		else if (_xRobotPrevu - xRobot < 0) {
			delta = xRobot - _xRobotPrevu;
			for (int i=0; i<delta; i++) 
				raffraichitRobot (xRobot-1, yRobot);
		}
		if (_yRobotPrevu - yRobot > 0) {
			delta = _yRobotPrevu - yRobot;
			for (int i=0; i<delta; i++) 
				raffraichitRobot (xRobot, yRobot+1);
		}
		else if (_yRobotPrevu - xRobot < 0) {
			delta = yRobot - _yRobotPrevu;
			for (int i=0; i<delta; i++) 
				raffraichitRobot (xRobot, yRobot-1);
		}
		napms (500);
	}
}



void VueRobot::raffraichitRobot (int _xRobotPrevu, int _yRobotPrevu)
{
		//! efface position precedente
		mvprintw (yRobot, xRobot, " "); 
		refresh();
		napms (50);
	
		xRobot = _xRobotPrevu;
		yRobot = _yRobotPrevu;
	

		//! affiche le petit robot
		mvprintw (yRobot, xRobot, "R"); 
		refresh();
		napms (150);
}

/**
* \brief	zone de deplacement robot piscine
*/
void VueRobot::creerZoneDeplacementPiscine()
{
		addstr("\n");
		creerLigneZone (xMin, " ");
		addstr("+");
		creerLigneZone ((xMax-xMin), "-");
		addstr("+\n");
		for (int i=0; i<(yMax-yMin); i++)
		{
			creerLigneZone (xMin, " ");
			addstr("|");
			creerLigneZone ((xMax-xMin), " ");
			addstr("|\n");
		}
		creerLigneZone (xMin, " ");
		addstr("+");
		creerLigneZone ((xMax-xMin), "-");
		addstr("+\n");
}

void VueRobot::creerLigneZone (int taille, std::string carac)
{
		for (int i=0; i<taille; i++) {
			addstr(carac.c_str());
		}
}

/**
* \brief	placer depart robot
*/
void VueRobot::placerDepart (int _xRobotInitial, int _yRobotInitial)
{
	xRobotInitial = _xRobotInitial;
	yRobotInitial = _yRobotInitial;
    
	//! Position en cours du robot
	xRobot = xRobotInitial;
	yRobot = yRobotInitial;

	//! affiche le petit robot
	mvprintw (yRobotInitial, xRobotInitial, "R"); 
	refresh();
	napms (500);
}

/**
* \brief	placer depart robot par defaut
*/
void VueRobot::placerDepart ()
{
	xRobotInitial = xMin + ((xMax-xMin)/2);
	yRobotInitial = yMin + ((yMax-yMin)/2);
    
	placerDepart (xRobotInitial, yRobotInitial);
}

/**
* \brief	Destructeur de la classe vueRobot
*
* \details  ferme le curse
*/
VueRobot :: ~VueRobot ()
{
	endwin(); // Close curses
}




/**
* \brief	detecte la limite de la zone
*/
bool VueRobot::detecterLimiteZone (int xPrevu, int yPrevu)
{
  //! limite haut
	if (yPrevu <= yMin) {
      return true;
  }
  //! limite bas
	if (yPrevu >= yMax) {
      return true;
  }
  
  //! limite gauche
	if (xPrevu <= xMin) {
      return true;
  }
  
  //! limite droite
	if (xPrevu >= xMax) {
      return true;
  }
  
	return false;
}




