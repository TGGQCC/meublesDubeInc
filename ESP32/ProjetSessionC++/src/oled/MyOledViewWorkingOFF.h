/**
    Class MyOledView : Gestion de la vue working off
    @file MyOledViewWorkingOFF.h 
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
        myOledViewWorkingOFF = new MyOledViewWorkingOFF;

        //Utilisation
        myOledViewWorkingOFF->setParams("NomSysteme","SAC System");
        myOledViewWorkingOFF->setParams("IdSysteme", "SAC_911");
        myOledViewWorkingOFF->setParams("Temperature", temperatureString);
        myOledViewWorkingOFF->setParams("Ip", ip);
        myOled->displayView(myOledViewWorkingOFF);
**/


#ifndef MYOLEDVIEWWORKINGOFF_H
#define MYOLEDVIEWWORKINGOFF_H

#include <Adafruit_SSD1306.h>
#include "MyOledViewWorking.h"
#include <string>

class MyOledViewWorkingOFF : public MyOledViewWorking {
    
    public:

    private:
        void display(Adafruit_SSD1306 *adafruit);
};
#endif