 /**
 * \brief     Definition de la classe Robot 
 *
 * \details   Cette classe presente les caracteristiques et comportement
 *				pour un modele de robot
 *
 * \file      Robot.cpp
 * \author    cgil 
 * \version   4.0
 * \date      jan. 2019
 */
   

#include "Robot.h"


#include <iostream>
#include <sstream>
using namespace std;


/**
* \brief	Constructeur de la classe Robot
*
* \details  un constructeur n a JAMAIS de type
*
* \return   JAMAIS
*/
Robot :: Robot()
{
	//! Initialise les positions a 0,0,0
	this->positionX = 0;
	this->positionY = 0;
	this->positionZ = 0;
 
}

//! se presenter
void Robot::sePresenter()
{
	cout << "Je suis un Robot\n";
}

//! parler
void Robot::parler (const std::string message)
{
	cout << message << endl;
}

//! Methodes pour donner et recuperer un nom
void Robot::setNom (string _nom) {
	this->nom = _nom;
}
string Robot::getNom () {
	return this->nom;
}


/**
* \brief	accesseurs 
*/
void Robot::setVitesse (int _vitesse) {
	this->vitesse = _vitesse;
}
int Robot::getVitesse () {
	return this->vitesse;
}

//! Positions
void Robot::setPositionX (int x) {
	this->positionX = x;
}
int Robot::getPositionX () {
	return this->positionX;
}
void Robot::setPositionY (int y) {
	this->positionY = y;
}
int Robot::getPositionY () {
	return this->positionY;
}
void Robot::setPositionZ (int z) {
	this->positionZ = z;
}
int Robot::getPositionZ () {
	return this->positionZ;
}


		
/**
* \brief	deplace le robot a une nouvelle position
*/
void Robot::deplacer (int x, int y, int z) 
{
	//this->parler ("Demande de changement de position...");
	
	//! Avant de deplacer on verifie la presence d un obstacle
	//this->parler ("\tdetection d un obstacle...");
	if (this->detecterObstacle() == false)
	{
		//this->parler ("\t\t  aucun obstacle");
	
		this->positionX = x;
		this->positionY = y;
		this->positionZ = z;
    
    
		
		//! parle pour indiquer le changement de position
		//this->parler (informerPosition());
	} else {
			this->parler ("Changement de position impossible : obstacle !");
	}
}


/**
* \brief	deplace le robot en avant de distance 
*/
int Robot::avance (int distance) 
{
	//this->parler ("Robot avance...");
	
  //! vue du robot en 2D : on avance en haut de 1
  laVueRobot.deplacerAvant(distance);
	
	return 1; // OK
}

/**
* \brief	deplace le robot en arriere de distance 
*/
int Robot::recule (int distance) 
{
	//this->parler ("Robot recule ...");
	
  //! vue du robot en 2D 
  laVueRobot.deplacerArriere(distance);
	
	return 1; // OK
}

/**
* \brief	deplace le robot a droite de distance 
*/
int Robot::droite (int distance) 
{
	//this->parler ("Robot va a droite ...");
	
  //! vue du robot en 2D 
  laVueRobot.deplacerDroite(distance);
	
	return 1; // OK
}

/**
* \brief	deplace le robot a gauche de distance 
*/
int Robot::gauche (int distance) 
{
	//this->parler ("Robot va a gauche ...");
	
  //! vue du robot en 2D 
  laVueRobot.deplacerGauche(distance);
	
	return 1; // OK
}



/**
* \brief	methode statique (non visible) qui permet de convertir 
*	        une valeur entiere en chaine 
*/
static std::string intToString (int val) 
{
    ostringstream temp;
    temp << val;
    return temp.str();
}


/**
* \brief	informe la position du robot x,y,z
*/
const std::string Robot::informerPosition ()
{
	std::string msg = "Position du robot [";
	msg += intToString(this->positionX) + ",";
	msg += intToString(this->positionY) + ",";
	msg += intToString(this->positionZ) + "]";
	return msg;
}

/**
* \brief	detecte la presence d un obstacle avant de deplacer
*/
bool Robot::detecterObstacle ()
{
	//! Traitement des capteurs
	
	//! Mesurer distance avec capteur infrarouge par exemple
	
	//! On retourne aucun obstacle pour le moment
	return false;
}

