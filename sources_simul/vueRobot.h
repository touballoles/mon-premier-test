 /**
 * \brief     	Coder une classe  : 
 *                      Declaration de la classe vueRobot
 * \file    	vueRobot.h
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
#ifndef VUE_ROBOT_H
#define VUE_ROBOT_H

#include <iostream>
#include <string>

#include <curses.h>
#include <unistd.h>


/** \class  	VueRobot
 *                      
 * \brief		Classe vueRobot : afficher une vue du deplacement du robot
 * \author		cgil 
 * \date  		fev. 2019
*/
class VueRobot 
{
	private:
		
		/**
		* \brief	position de depart
		*/
		int xRobotInitial;
		int yRobotInitial;
    
		/**
		* \brief	position en cours
		*/
		int xRobot;
		int yRobot;
		

		/**
		* \brief	zone de deplacement robot
		*/
		int yMin;
		int xMin;
		int xMax;
		int yMax;

		/** 
		* \brief Methodes internes a la classe
		*/
		void creerZoneDeplacementPiscine();
		void creerLigneZone (int, std::string);
		bool detecterLimiteZone (int, int);
		void deplacer(int x,int y);
		
		void raffraichitRobot (int _xRobotPrevu, int _yRobotPrevu);

	public:
		/**
		* \brief	Constructeur de la classe vueRobot
		*
		* \details  pas de parametre
		*/
		VueRobot ();
		
		/**
		* \brief	Destructeur de la classe vueRobot
		*
		* \details  ferme le curse
		*/
		~VueRobot ();
		
		/**
		* \brief	placer depart robot 
		*/
		void placerDepart (int _xRobotInitial, int _yRobotInitial);
	
		/**
		* \brief	placer depart robot par defaut plein milieu du cadre
		*/
		void placerDepart ();  
   
    
		/**
		* \brief	deplacer en avant ou arriere ou droite ou gauche
		*/
		void deplacerAvant (int);
		void deplacerArriere (int);
		void deplacerDroite (int);
		void deplacerGauche (int);
		
};

/**
* \brief      Ne pas redefinir la classe
*/
#endif // VUE_ROBOT_H