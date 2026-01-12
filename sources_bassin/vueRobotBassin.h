 /**
 * \brief     	Coder une classe  : 
 *                      Declaration de la classe vueRobotBassin
 * \file    	vueRobotBassin.h
 * \author		cgil 
 * \version		2.0
 * \date      jan 2020
 */
 
 
 
/** Infos de compilation librairie ncurses (2D)
 
			LINUX 
				
				Compilation :
					g++ vueRobot.cpp Robot.cpp robotTest.cpp -o robotTest -lncurses
					
				Pré-requis : librairie installee UBUNTU 20.04
					sudo apt-get install libncurses5-dev libncursesw5-dev
 
			WINDOWS 
				Librairie curses pour Mingw (WINDOWS) : 
				
				! Compiler avec l'option -lpdcurses
				
				g++  vueRobotBassin.cpp RobotBassin.cpp robotBassinTest.cpp -o robot_simu.exe -lpdcurses
				
				pdc34w.dllw (64 bits) ou pdc33w.dllw (32 bits
				curses.h, panel.h dans : Mingw /include
				pdcurses.dll : dans Mingw /bin
				pdcurses.lib : dans Mingw /lib
 */


/**
* \brief      Ne pas redefinir la classe
*/
#ifndef VUE_ROBOT_BASSIN_H
#define VUE_ROBOT_BASSIN_H

#include <iostream>
#include <string>

#include <curses.h>
#include <unistd.h>
#include <stdlib.h>


//! Couleurs 
#define COULEUR_PELOUSE_PAIR     	1		//! ext pelouse
#define COULEUR_VIDE_PAIR     		1		
#define COULEUR_EAU_PROPRE_PAIR     2		//! eau propre 
#define COULEUR_EAU_SALE_PAIR  		3		//! eau sale
#define COULEUR_ROBOT		  		4		

//! Constante taux de  ref de temps d'attente pour raffraichissement
#define REF_NAPMS		100   //! par defaut le taux de pause est de 50
//#define REF_NAPMS		1 	  //! pour debug en accelere

/** \class  	VueRobotBassin
 *                      
 * \brief		Classe vueRobotBassin : afficher une vue du deplacement du robot
 * \author		cgil 
 * \date  		fev. 2019
*/
class VueRobotBassin 
{
	private:
		
		/**
		* \brief	position initial de depart
		*/
		int xDepart;
		int yDepart;
    
		/**
		* \brief	position en cours
		*/
		int x;
		int y;
		

		/**
		* \brief	zone de deplacement robot
		*/
		int yMin;
		int xMin;
		int xMax;
		int yMax;
		
		/**
			\brief	Initialisation des parametres Curses
		*/
		WINDOW * win;
		void initCurses();
		
		//! Sous fenetre bassin en bleu bien sur
		WINDOW *fenBassin;
		

		/** 
		* \brief Methodes internes a la classe
		*/
		void creerZoneDeplacementPiscine();
		void creerLigneZone (int, std::string);
		bool detecterLimiteZone (int, int);
				
		void raffraichitRobotBassin (int _xPrevu, int _yPrevu);

	public:
		/**
		* \brief	Constructeur de la classe vueRobotBassin
		*
		* \details  pas de parametre
		*/
		VueRobotBassin ();
			
		/**
		* \brief	Destructeur de la classe vueRobotBassin
		*
		* \details  ferme le curse
		*/
		~VueRobotBassin ();
		
		/**
		* \brief	Initialisation des dimensions du bassin (piscine)
		* \param   position bassin : x, y et longueur, largeur
		*/
		void initBassin (
			int xOrigineBassin, 
			int yOrigineBassin, 
			int longueurBassin, 	
			int largeurBassin );
	
		
		/**
		* \brief	placer depart robot 
		* \param   position robot : xDepart, yDepart 
		*/
		void placerDepart (int _xDepart, int _yDepart);
	
		/**
		* \brief	placer depart robot par defaut plein milieu du cadre
		*/
		void placerDepart ();  
   
	 
    
		/**
		* \brief	deplacer en avant ou arriere ou droite ou gauche
		*/
		int deplacerAvant (int);
		int deplacerArriere (int);
		int deplacerDroite (int);
		int deplacerGauche (int);
		
		/**
		* \brief	deplacer en coordonnes
		*/
		int deplacer(int _x, int _y);
		
		/**
		* \brief permet d'informer 
		* \param   message et position x y sinon par defaut
		*/
		void informe (const std::string msg, int _x=0, int _y=0);
		
		/**
		* \brief permet d'afficher un msg en debug
		* \param   message 
		*/
		void debug (const std::string msg);
		
		
		/**
		* \brief permet de faire une pause affichage
		*/
		void pause (unsigned long millisec);
};

/**
* \brief      Ne pas redefinir la classe
*/
#endif // VUE_ROBOT_BASSIN_H