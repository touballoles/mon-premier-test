 /**
 * \brief     Coder une classe  : 
 *                      Programme de test de la classe RobotBassin
 * \file      robotBassinTest.cpp
 * \author    cgil 
 * \version   5.0
 * \date      jan. 2019
 */
 
#include <iostream>
using namespace std;


//! fichier declaration classe RobotBassin.h
#include "robotBassin.h"



int main ()
{
	cout << "Debut programme robotBassinTest avec vue \n";
	
	//! Instanciation (creation) d un objet RobotBassin
	cout << "Creation du robot bassin...\n";
	RobotBassin unRobotBassin;
	
	//! Init bassin : 
	//! 	position bassin : xOrigine 20  yOrigine 2 
	//!		dimensions : de 50 de longueur par 16 de largeur
	unRobotBassin.initBassin (20, 2, 50, 16);
	
	//! Placer robot en position depart
	unRobotBassin.placerDepart (20+10, 2+8);

	//! test placement 
	unRobotBassin.deplacer (20+12, 2+8, 0);

	  
  	//! Deplace le robot selon l'algorithme haut bas
	unRobotBassin.deplacerEnModeAuto();
  
	
		
	cout << "\nFin programme\n\n";
 
	return 0;
}

