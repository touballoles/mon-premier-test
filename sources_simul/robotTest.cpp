 /**
 * \brief     Coder une classe  : 
 *                      Programme de test de la classe Robot
 * \file      robotTest.cpp
 * \author    cgil 
 * \version   6.0
 * \date      jan. 2020
 * 
 * 
 * Pré-requis : librairie installee UBUNTU 
					sudo apt-get install libncurses5-dev libncursesw5-dev
 * 
 */
 
#include <iostream>
using namespace std;


//! fichier declaration classe Robot.h
#include "Robot.h"



int main ()
{
	cout << "Debut programme robotTest avec vue \n";
	
	//! Instanciation (creation) d un objet Robot
	cout << "Creation du robot ...\n";
	Robot unRobot;
	
	//! On utilise le robot que j ai cree. Il se presente
	//unRobot.sePresenter();
	
	
	//! on donne vie au robot avec son nom
	unRobot.setNom ("MX8");
	
	//! on demande le nom et on affiche
	//cout << "Nom du robot : " << unRobot.getNom() << endl;
	
		
	//! Deplacement des positions
	unRobot.deplacer (3,4,0);
	
  
	//! Deplace le robot en 2D
	unRobot.avance(4);
	unRobot.avance(2);
	unRobot.avance(2);
	unRobot.droite(6);
	unRobot.avance(10);
	unRobot.recule(8);
	unRobot.avance(20);
	unRobot.recule(4);
	unRobot.gauche(12);
	unRobot.recule(6);
	unRobot.recule(20);
  
 
	napms (1000);  //! attente 1 s
	//cout << "\nFin programme\n\n";
 
	return 0;
}

