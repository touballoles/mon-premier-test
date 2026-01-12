 /**
 * \brief     Definition de la classe vueRobotBassin 
 *
 * \details   Cette classe presente les caracteristiques et comportement
 *				pour un modele de vue de deplacement du robot
 *
 *      
 *						! Compiler avec l'option -lncurses 
 *						
 *            ! Compiler win32 avec l'option -lpdcurses 
 *
 * \file      vueRobotBassin.cpp
 * \author    cgil 
 * \version   2.0
 * \date      jan. 2020
 */
   
	 
	

#include "vueRobotBassin.h"

#include <iostream>
#include <sstream>


using namespace std;


/**
* \brief	Constructeur de la classe vueRobotBassin
*
* \details  un constructeur n a JAMAIS de type
*
* \return   JAMAIS
*/
VueRobotBassin :: VueRobotBassin()
{
	//! Initialise curses : attention version 32 bits ou 64 bits
	initCurses();
	
	
	//! Initialise attributs par defaut
	xDepart=0;
	yDepart=0;
	x=0;
	y=0;
	
	//! Position par defaut du bassin dans la vue 2D
	xMin = 20;
	yMin = 2;
		
}

/**
* \brief	Destructeur de la classe vueRobotBassin
*
* \details  ferme le curse
*/
VueRobotBassin :: ~VueRobotBassin ()
{
	//! sous fenetre bassin
	//! hauteur, largeur et coin gauche
	if (this->fenBassin !=  (WINDOW *)NULL)
		delwin(this->fenBassin);
	
	endwin(); // Close curses
}

/**
* \brief	Initialisation des dimensions du bassin (piscine)
* \param   position xOrigine, yOrigine et longueur, largeur
*/
void VueRobotBassin::initBassin (
	int xOrigineBassin, 
	int yOrigineBassin, 
	int longueurBassin, 
	int largeurBassin )
{
	//! position origine du bassin
	xMin = xOrigineBassin;
	yMin = yOrigineBassin;
	
	//! Dimensions du bassin demande
	xMax = xMin + longueurBassin;
	yMax = yMin + largeurBassin;
		
		
	//! zone de deplacement robot => piscine
	creerZoneDeplacementPiscine();
	
	//! sous fenetre bassin : eau sale
	//! hauteur, largeur et coin gauche
	this->fenBassin = subwin(win,largeurBassin,longueurBassin, yMin, xMin+1);
	wbkgd(this->fenBassin, COLOR_PAIR(COULEUR_EAU_SALE_PAIR));
	wrefresh(this->fenBassin);
}




/**
* \brief	deplacer en haut de distance
*/
int VueRobotBassin::deplacerAvant (int distance)
{
	int ret = 0;
	ret = deplacer (x, y-distance);
	if (ret != 1)
		return 0;
	
	return 1;
}

/**
* \brief	deplacer en arriere de distance
*/
int VueRobotBassin::deplacerArriere (int distance)
{
	int ret = 0;
	ret = deplacer (x, y+distance);
	if (ret != 1)
		return 0;
	
	return 1;
}

/**
* \brief	deplacer a droite de distance
*/
int VueRobotBassin::deplacerDroite (int distance)
{
	int ret = 0;
	ret = deplacer (x+distance, y);
	if (ret != 1)
		return 0;
	
	return 1;
}

/**
* \brief	deplacer a gauche de distance
*/
int VueRobotBassin::deplacerGauche (int distance)
{
	int ret = 0;
	ret = deplacer (x-distance, y);
	if (ret != 1)
		return 0;
	
	return 1;
}


/**
* \brief	deplace le robot en affichant "R" sur la position demandee
*
* efface position precedente 
*/
int VueRobotBassin::deplacer (int _xPrevu, int _yPrevu)
{
	//debug("VueRobotBassin::deplacer...");
	
	 //! Verifie position possible du robot
	//debug("detecterLimiteZone ?", _xPrevu, _yPrevu);
	 
	if (detecterLimiteZone(_xPrevu, _yPrevu)) {
		/*char buffer[50] = "";
		sprintf (buffer, "hors limite [%d,%d]", _xPrevu, _yPrevu);
		mvprintw (y, 0, buffer);*/
		
		//debug("hors limite");
		
		return -1;  // impossible de deplacer
		
	} else {  //! deplacement complet accepte
	
		//debug("deplacement complet accepte");
	
		//! effectue un affichage progressif
		int delta = 0;
		if (_xPrevu - x > 0) {
			delta = _xPrevu - x;
			for (int i=0; i<delta; i++) 
				raffraichitRobotBassin (x+1, y);
		}
		else if (_xPrevu - x < 0) {
			delta = x - _xPrevu;
			for (int i=0; i<delta; i++) 
				raffraichitRobotBassin (x-1, y);
		}
		if (_yPrevu - y > 0) {
			delta = _yPrevu - y;
			for (int i=0; i<delta; i++) 
				raffraichitRobotBassin (x, y+1);
		}
		else if (_yPrevu - x < 0) {
			delta = y - _yPrevu;
			for (int i=0; i<delta; i++) 
				raffraichitRobotBassin (x, y-1);
		}
	}
	
	return 1;
}



void VueRobotBassin::raffraichitRobotBassin (int _xPrevu, int _yPrevu)
{
		//! efface position precedente
	
		//mvprintw (y, x, " "); 
		attron(COLOR_PAIR(COULEUR_EAU_PROPRE_PAIR));
		mvaddch(y, x, ' ');
		attroff(COLOR_PAIR(COULEUR_EAU_PROPRE_PAIR));
		
		refresh();
		napms (1*REF_NAPMS);
	
		x = _xPrevu;
		y = _yPrevu;
	

		//! affiche le petit robot
		mvprintw (y, x, "R"); 
		/*attron(COLOR_PAIR(COULEUR_ROBOT));
		mvaddch(y, x, ' ');
		attroff(COLOR_PAIR(COULEUR_ROBOT));
		move(y, x);*/
		refresh();
		napms (5*REF_NAPMS);
}

/**
* \brief	zone de deplacement robot piscine
*/
void VueRobotBassin::creerZoneDeplacementPiscine()
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

void VueRobotBassin::creerLigneZone (int taille, std::string carac)
{
		for (int i=0; i<taille; i++) {
			addstr(carac.c_str());
		}
}

/**
* \brief	placer depart robot
* \param   position robot : _xDepart, _yDepart 
*/
void VueRobotBassin::placerDepart (int _xDepart, int _yDepart)
{
	xDepart = _xDepart;
	yDepart = _yDepart;
    
	//! Position en cours du robot
	x = xDepart;
	y = yDepart;

	//! affiche le petit robot
	mvprintw (yDepart, xDepart, "R"); 
	refresh();
	napms (10*REF_NAPMS);
}

/**
* \brief	placer depart robot par defaut
*/
void VueRobotBassin::placerDepart ()
{
	xDepart = xMin + ((xMax-xMin)/2);
	yDepart = yMin + ((yMax-yMin)/2);
    
	placerDepart (xDepart, yDepart);
}






/**
* \brief	detecte la limite de la zone
*/
bool VueRobotBassin::detecterLimiteZone (int _xPrevu, int _yPrevu)
{
  //! limite haut
	if (_yPrevu < yMin) {
      return true;
  }
  //! limite bas
	if (_yPrevu >= yMax) {
      return true;
  }
  
  //! limite gauche
	if (_xPrevu <= xMin) {
      return true;
  }
  
  //! limite droite
	if (_xPrevu > xMax) {
      return true;
  }
  
	return false;
}


/**
* \brief permet d'afficher un message
* \param   message et position x y sinon par defaut
*/
void VueRobotBassin::informe (const std::string msg, int _x, int _y)
{
	int posX = 0;
	int posY = 0;
		
	if (_x!=0 && _y!=0) {
		posX = _x;
		posY = _y;
	} else {
		//! par defaut
		posX = xMin+1;
		posY = yMax+1;
	}
	
	//! on efface le message d avant
	for (int i=xMin+1; i< xMax; i++)
		mvprintw (posY, i, " ");
	
	//! On affiche a la position demande
	mvprintw (posY, posX, ( char*)msg.c_str()); //! affichage en bas
	refresh();
	
	//! pause pour affichage visible
	napms(1000);
	
}

/**
* \brief permet d'afficher un texte en debug
* \param   message 
*/
void VueRobotBassin::debug (const std::string msg)
{
	int posX = 2;
	int posY = 2;

	//! on efface le message d avant
	for (int i=2+1; i< xMin-2; i++)
		mvprintw (posY, i, " ");

	mvprintw (posY, posX, ( char*)msg.c_str());
	refresh();
	pause(1000);
}


/**
* \brief permet de faire une pause affichage
*/
void VueRobotBassin::pause (unsigned long millisec){
	napms (millisec/100*REF_NAPMS);
}

//////////////////////////////////////////////////////////////////
/**
	Liens : 
http://www.tldp.org/pub/Linux/docs/ldp-archived/linuxfocus/Francais/Archives/lf-2002_03-0233.pdf
*/
//////////////////////////////////////////////////////////////////

/**
	\brief	Initialisation des parametres Curses
	
	\details https://stackoverflow.com/questions/22469877/how-can-i-add-new-ncurses-subwindows-in-response-to-user-demand
	
*/

void VueRobotBassin::initCurses()
{
	win = initscr();
	start_color();
	init_pair (COULEUR_PELOUSE_PAIR, COLOR_BLACK, COLOR_GREEN);	//! ext pelouse
    init_pair (COULEUR_EAU_PROPRE_PAIR, COLOR_CYAN, COLOR_BLUE);	//! eau propre 
    init_pair (COULEUR_EAU_SALE_PAIR, COLOR_BLACK, COLOR_WHITE);	//! eau sale 
	init_pair (COULEUR_ROBOT, COLOR_WHITE, COLOR_BLACK);		
	curs_set(0);
	noecho();
	keypad(stdscr,TRUE);
	
	bkgd(COLOR_PAIR(COULEUR_PELOUSE_PAIR));
	
}


/**
 Pour debug : attente touche escape
*/
/*#define ESCAPE 27
void VueRobotBassin::escape()
{
	int key;
	do {
		key=getch();
	} while (key!=ESCAPE);  
}
*/
