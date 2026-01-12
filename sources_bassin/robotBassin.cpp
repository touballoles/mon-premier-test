 /**
 * \brief     Definition de la classe RobotBassin 
 *
 * \details   Cette classe presente les caracteristiques et comportement
 *				pour un modele de robot
 *
 * \file      RobotBassin.cpp
 * \author    cgil 
 * \version   1.0
 * \date      jan. 2020
 */
   

#include "robotBassin.h"


#include <iostream>
#include <sstream>
using namespace std;


/**
* \brief	Constructeur de la classe RobotBassin
*
* \details  un constructeur n a JAMAIS de type
*
* \return   JAMAIS
*/
RobotBassin :: RobotBassin()
{
	//! genere un bassin des dimensions demandees
	positionX = 0;
	positionY = 0;
	positionZ = 0;
	
	yMin = 0;
	xMin = 0;
	xMax = 0;
	yMax = 0;
}


/**
* \brief	Init position et dimensions
*
* \param  position _xOrigineBassin, _yOrigineBassin 
*    et _longueurBassin, _largeurBassin
*/
void RobotBassin::initBassin (
	int _xOrigineBassin, 
	int _yOrigineBassin, 
	int _longueurBassin, 
	int _largeurBassin )
{
	//! Init bassin et curses 2D
	laVueRobotBassin.initBassin (_xOrigineBassin, _yOrigineBassin, _longueurBassin, _largeurBassin);
	
	xMin = _xOrigineBassin;
	yMin = _yOrigineBassin;
	xMax = _xOrigineBassin+_longueurBassin;
	yMax = _yOrigineBassin+_largeurBassin;
}

/**
* \brief	Init position et dimensions
*
* \param  position de depart du Robot  _xDepart, _yDepart
*/
void RobotBassin::placerDepart (int _xDepart, int _yDepart) 
{
	//! Placer le robot au depart
	laVueRobotBassin.placerDepart (_xDepart, _yDepart);
}



//! se presenter
void RobotBassin::sePresenter()
{
	cout << "Je suis un RobotBassin\n";
}

//! parler
void RobotBassin::parler (const std::string message)
{
	//cout << message << endl;
	laVueRobotBassin.informe (message);
}

//! Methodes pour donner et recuperer un nom
void RobotBassin::setNom (string _nom) {
	this->nom = _nom;
}
string RobotBassin::getNom () {
	return this->nom;
}


/**
* \brief	accesseurs 
*/
void RobotBassin::setVitesse (int _vitesse) {
	this->vitesse = _vitesse;
}
int RobotBassin::getVitesse () {
	return this->vitesse;
}

//! Positions
void RobotBassin::setPositionX (int x) {
	this->positionX = x;
}
int RobotBassin::getPositionX () {
	return this->positionX;
}
void RobotBassin::setPositionY (int y) {
	this->positionY = y;
}
int RobotBassin::getPositionY () {
	return this->positionY;
}
void RobotBassin::setPositionZ (int z) {
	this->positionZ = z;
}
int RobotBassin::getPositionZ () {
	return this->positionZ;
}


/**
* \brief	deplace le robot en mode auto
*
*	 le deplacement effectue un parcours en mode haut/bas
*  du coin bas droit au coin haut gauche
*
*  Donc dans un premier temps il se positionne en bas a droite
*/
void RobotBassin::deplacerEnModeAuto (){
	int ret = 0;
	
	parler ("Demarrage mode auto...");
	
	
	//! Etape 1 : position en haut a gauche 
	//! on va tout a gauche puis tout en haut
	parler ("recherche position coin gauche...");
	while (gauche(1));
	while (avance(1));
	
	parler ("Mode auto start");
	
	//! Etape 2 : de haut en bas, puis a droite, de bas en haut
	
	while (!detecterCoinDroitHaut()) {
		
		//! de haut en bas
		while (recule(1)){
			if (detecterCoinDroitHaut())
				break;
		}
		
		//! pause pour affichage joli
		laVueRobotBassin.pause(200);
	
		// deplacement a droite, de bas en haut
		if (droite(1)) {
			if (detecterCoinDroitHaut())
				break;
		}
		
		
		// de bas en haut
		while (avance(1)){
			if (detecterCoinDroitHaut())
				break;
		}
		
		//! pause pour affichage joli
		laVueRobotBassin.pause(200);
		
		// a droite
		if (droite(1)) {
			if (detecterCoinDroitHaut())
				break;
		}
	
	} //! tant que position robot != coin droit bas	
	
	parler("Mode auto termine... A votre service");
	laVueRobotBassin.pause(10000);
}		
 


/**
* \brief	deplace le robot a une nouvelle position
*
* \return : 1 si deplacement effectue - <=0 si pas de deplacement
*/
int RobotBassin::deplacer (int _x, int _y, int _z) 
{
	//this->parler ("Demande de changement de position...");
	
	//! Avant de deplacer on verifie la presence d un obstacle
	//this->parler ("\tdetection d un obstacle...");
	if (this->detecterObstacle() == false)  //! plus tard...
	{
			
		if (laVueRobotBassin.deplacer(_x, _y) != 1) {
			//this->parler ("\t\t  deplacement impossible");
			
			return -1;
		}
	
		this->positionX = _x;
		this->positionY = _y;
		this->positionZ = _z;
    
		
		 
		
		//! parle pour indiquer le changement de position
		//this->parler (informerPosition());
		
		return 1; // Deplacement effectue
		
		
	} else {
			//this->parler ("Changement de position impossible : obstacle !");
	}
	
	return 0; // pas de deplacement
}



/**
* \brief	deplace le robot en avant de distance 
*/
int RobotBassin::avance (int distance) 
{
	//this->parler ("RobotBassin avance...");
	
  //! vue du robot en 2D : on avance en haut de 1
	bool bRet = laVueRobotBassin.deplacerAvant(distance);
	if (bRet != true)
		return 0;
	
	this->positionY -= 1;
	
	return 1; // OK
}

/**
* \brief	deplace le robot en arriere de distance 
*/
int RobotBassin::recule (int distance) 
{
	//this->parler ("RobotBassin recule ...");
	
  //! vue du robot en 2D 
  bool bRet = laVueRobotBassin.deplacerArriere(distance);
	if (bRet != 1)
		return 0;
	
	this->positionY += 1;
	
	return 1; // OK
}

/**
* \brief	deplace le robot a droite de distance 
*/
int RobotBassin::droite (int distance) 
{
	//this->parler ("RobotBassin va a droite ...");
	
	//! pause pour simulation de rotation du robot
	laVueRobotBassin.pause(3000);
	
	//! vue du robot en 2D 
	bool bRet = laVueRobotBassin.deplacerDroite(distance);
	if (bRet != true)
		return 0;

	this->positionX += 1;
	
	//! pause pour simulation de rotation du robot
	laVueRobotBassin.pause(3000);
	return 1; // OK
}

/**
* \brief	deplace le robot a gauche de distance 
*/
int RobotBassin::gauche (int distance) 
{
	//this->parler ("RobotBassin va a gauche ...");
	
	//! pause pour simulation de rotation du robot
	laVueRobotBassin.pause(200);
	
	//! vue du robot en 2D 
	bool bRet = laVueRobotBassin.deplacerGauche(distance);
	if (bRet != true)
		return 0;
	
	this->positionX -=1;
	
	//! pause pour simulation de rotation du robot
	laVueRobotBassin.pause(200);
	
	
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
const std::string RobotBassin::informerPosition ()
{
	std::string msg = "x,y [";
	msg += intToString(this->positionX) + ",";
	msg += intToString(this->positionY) + "]";
	//sg += intToString(this->positionZ) + "]";
	return msg;
}

/**
* \brief	detecte la presence d un obstacle avant de deplacer
*/
bool RobotBassin::detecterObstacle ()
{
	
	//! Traitement des capteurs
	
	//! Mesurer distance avec capteur infrarouge par exemple
	
	//! On retourne aucun obstacle pour le moment
	return false;
}


/**
* \brief	detecte la position coin droit Haut
*/
bool RobotBassin::detecterCoinDroitHaut ()
{
	//! si position robot est a cette position
	if (positionX == (xMax) && positionY == (yMin))
		return true;
	
	
	return false;
}



