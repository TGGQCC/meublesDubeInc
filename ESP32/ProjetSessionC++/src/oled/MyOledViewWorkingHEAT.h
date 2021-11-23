/**
    Class MyOledView : Gestion de la vue working heat
    @file MyOledViewWorkingHEAT.h 
    @author Jérémie Cyr
    @version 1.0 21/11/16
    
    Historique des versions   
                            Versions  Date      Auteur          Description
                            1.0     21/11/16    Jérémie Cyr     Première version de la classe
                            
                            
    platform = espressif32
    board = esp32doit-devkit-v1
    framework = arduino
    lib_deps = 
        Aucune
    Autres librairies (à copier dans le répertoire lib)
        Aucune
    
    Exemple d'utilisation 
        //Définition 

        //Utilisation

**/

#ifndef MYOLEDVIEWWORKINGHEAT_H
#define MYOLEDVIEWWORKINGHEAT_H

#include <Adafruit_SSD1306.h>
#include "MyOledViewWorking.h"
#include <string>

class MyOledViewWorkingHEAT : public MyOledViewWorking {
    
    public:

    private:
        void display(Adafruit_SSD1306 *adafruit);
        void update(Adafruit_SSD1306 *adafruit);

};
#endif