 /**
 * \brief     	Coder une classe  : 
 *                      Declaration de la classe RobotBassin
 * \file    	RobotBassin.h
 * \author		cgil 
 * \version		7.0
 * \date      fev 2019
 */

/**
* \brief      Ne pas redefinir la classe
*/
#ifndef ROBOT_BASSIN_H
#define ROBOT_BASSIN_H


/**
* \brief Utilisation de la classe pour une vue du robot en 2D 
*  
*/
#include "vueRobotBassin.h"


#include <string>

/** \class  	RobotBassin
 *                      
 * \brief		Classe RobotBassin 
 * \author		cgil 
 * \date  		fev. 2019
*/
class RobotBassin 
{
	private:
		//! attributs
		std::string nom;
		int vitesse;
		
		int positionX;
		int positionY;
		int positionZ;
		
		/**
		* \brief	zone de deplacement robot
		*/
		int yMin;
		int xMin;
		int xMax;
		int yMax;
		
		
		/**
		* \brief	Methode parler interne
		*/
		void parler (const std::string message);
    
    
		//! vue du robot en 2D
		VueRobotBassin laVueRobotBassin;
		
	public:
		/**
		* \brief	Constructeur de la classe RobotBassin
		*
		* \details  pas de parametre
		*/
		RobotBassin ();
		
		
			
		/**
		* \brief	Init position et dimensions
		*
		* \param  position _xOrigineBassin, _yOrigineBassin 
		*			et _longueurBassin, _largeurBassin
		*/
		void initBassin (
			int _xOrigineBassin, 
			int _yOrigineBassin, 
			int _longueurBassin, 
			int _largeurBassin );
		
		
		/**
		* \brief	placer depart robot 
		*
		* \param  position de depart du Robot  _xDepart, _yDepart
		*/
		void placerDepart (int _xDepart, int _yDepart);
				
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
		*
		* \return : 1 si deplacement effectue - <=0 si pas de deplacement
		*/
		int deplacer (int, int, int);
		
		/**
		* \brief	deplace le robot a la position par defaut : ici en bas a droite
		*/
		void deplacerEnPositionDefaut ();
		
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
		
		
			
		/**
		* \brief	deplace le robot en mode auto
		*
		*	 le deplacement effectue un parcours en mode haut/bas
		*  du coin bas droit au coin haut gauche
		*/
		void deplacerEnModeAuto ();
		
		/**
		* \brief	detecte la position coin droit haut
		*/
		bool detecterCoinDroitHaut ();
		
		
};

/**
* \brief      Ne pas redefinir la classe
*/
#endif // ROBOT_BASSIN_H