/**
    Class MyOledView : Gestion d'une VUE pour le OLed
    @file MyOledViewErrorWifiConnexion.h 
    @author Jérémie Cyr
    @version 1.0 21/11/01
    
    Historique des versions   
                            Versions  Date      Auteur          Description
                            1.0     21/11/01    Jérémie Cyr     Première version de la classe
                            
                            
    platform = espressif32
    board = esp32doit-devkit-v1
    framework = arduino
    lib_deps = 
        Aucune
    Autres librairies (à copier dans le répertoire lib)
        Aucune
    
    Exemple d'utilisation 
        //Définition 
            myOledViewErrorWifiConnexion = new MyOledViewErrorWifiConnexion;

        //Utilisation
            myOledViewErrorWifiConnexion->setNomDuSysteme("SAC System");
            myOled->displayView(myOledViewErrorWifiConnexion);
**/


#ifndef MYOLEDVIEWERRORWIFICONNEXION_H
#define MYOLEDVIEWERRORWIFICONNEXION_H

#include <Adafruit_SSD1306.h>
#include "MyOledView.h"
#include <string>

class MyOledViewErrorWifiConnexion : public MyOledView {

    public:

        void setNomDuSysteme(std::string val);

    private:
        void display(Adafruit_SSD1306 *adafruit);
        void update(Adafruit_SSD1306 *adafruit);


        std::string nomDuSysteme;
};
#endif