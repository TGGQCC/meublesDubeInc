/**
    Class MyOledView : Gestion d'une VUE pour le OLed
    @file MyOledViewInitialisation.h 
    @author Jérémie Cyr
    @version 1.1 21/11/01
    
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
        myOledViewInitialisation = new MyOledViewInitialisation;

        //Utilisation
        myOledViewInitialisation->setNomDuSysteme("SAC System");
        myOledViewInitialisation->setIdDuSysteme("SAC_911");
        myOled->displayView(myOledViewInitialisation);
**/


#ifndef MYOLEDVIEWINITIALISATION_H
#define MYOLEDVIEWINITIALISATION_H
#include <Adafruit_SSD1306.h>
#include <string>
#include "MyOledView.h"

class MyOledViewInitialisation : public MyOledView {
    


    public:
        void setNomDuSysteme(std::string val);
        void setIdDuSysteme(std::string val);
        void setSensibiliteBoutonAction(std::string val);
        void setSensibiliteBoutonReset(std::string val);

    private:
        void display( Adafruit_SSD1306 *adafruit);
        void update(Adafruit_SSD1306 *adafruit);


        std::string nomDuSysteme;
        std::string idDuSysteme;
        std::string sensibiliteBoutonAction;
        std::string sensibiliteBoutonReset;


};
#endif