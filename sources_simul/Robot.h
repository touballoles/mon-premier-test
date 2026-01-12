 /**
 * \brief     	Coder une classe  : 
 *                      Declaration de la classe Robot
 * \file    	Robot.h
 * \author		cgil 
 * \version		7.0
 * \date      fev 2019
 */

/**
* \brief      Ne pas redefinir la classe
*/
#ifndef ROBOT_H
#define ROBOT_H


/**
* \brief Utilisation de la classe pour une vue du robot en 2D 
*  
*/
#include "vueRobot.h"


#include <string>

/** \class  	Robot
 *                      
 * \brief		Classe Robot 
 * \author		cgil 
 * \date  		fev. 2019
*/
class Robot 
{
	private:
		//! attributs
		std::string nom;
		int vitesse;
		int positionX;
		int positionY;
		int positionZ;
		
		/**
		* \brief	Methode parler interne
		*/
		void parler (const std::string message);
    
    
		//! vue du robot en 2D
		VueRobot laVueRobot;
		
	public:
		/**
		* \brief	Constructeur de la classe Robot
		*
		* \details  pas de parametre
		*/
		Robot ();
		
				
		/**
		* \brief	Methode pour se presenter
		*/
		void sePresenter();
		
		
		//! Methodes pour donner et recuperer un nom
		//!...
		/**
		* \brief	Methode pour donner un nom
		*/
		void setNom (std::string _nom);
		
		/**
		* \brief	Methode pour obtenir le nom
		*/
		std::string getNom ();
		
		/**
		* \brief	accesseurs 
		*/
		int getVitesse ();
		void setVitesse (int);
		int getPositionX ();
		void setPositionX (int);
		int getPositionY ();
		void setPositionY (int);
		int getPositionZ ();
		void setPositionZ (int);
		
		/**
		* \brief	informe la position du robot x,y,z
		*/
		const std::string informerPosition ();

		/**
		* \brief	deplace le robot a une nouvelle position
		*/
		void deplacer (int, int, int);
		
		/**
		* \brief	detecte la presence d un obstacle avant de deplacer
		*/
		bool detecterObstacle ();
		
		/**
		* \brief	deplace le robot en avant ou en arriere de la distance D 
		*/
		int avance (int distanceD);
		int recule (int distanceD);
		int droite (int distanceD);
		int gauche (int distanceD);
		
};

/**
* \brief      Ne pas redefinir la classe
*/
#endif // ROBOT_H