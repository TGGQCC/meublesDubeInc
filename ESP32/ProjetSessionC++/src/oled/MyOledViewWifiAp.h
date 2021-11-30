/**
    Class MyOledView : Gestion d'une VUE pour le OLed
    @file MyOledViewWifiAp.h 
    @author Jérémie Cyr
    @version 1.1 21/11/08
    
    Historique des versions   
                            Versions  Date      Auteur          Description
                            1.0     21/11/08    Jérémie Cyr     Première version de la classe
                            
                            
    platform = espressif32
    board = esp32doit-devkit-v1
    framework = arduino
    lib_deps = 
        Aucune
    Autres librairies (à copier dans le répertoire lib)
        Aucune
    
    Exemple d'utilisation 
        //Définition 
         myOledViewWifiAp = new MyOledViewWifiAp;

        //Utilisation
         myOledViewWifiAp->setNomDuSysteme("SAC System");
         myOledViewWifiAp->setParams("IdSysteme", "SAC_911");
         myOledViewWifiAp->setSsIDDuSysteme(ssIDRandom.c_str());
         myOledViewWifiAp->setPassDuSysteme(PASSRandom.c_str());
         myOled->displayView(myOledViewWifiAp);
**/


#ifndef MYOLEDVIEWWIFIAP_H
#define MYOLEDVIEWWIFIAP_H
#include <Adafruit_SSD1306.h>
#include <string>
#include "MyOledView.h"

class MyOledViewWifiAp : public MyOledView {
    


    public:
        void setNomDuSysteme(std::string val);
        void setSsIDDuSysteme(std::string val);
        void setPassDuSysteme(std::string val);

    private:
        void display( Adafruit_SSD1306 *adafruit);
        void update(Adafruit_SSD1306 *adafruit);


        std::string nomDuSysteme;
        std::string ssIDDuSysteme;
        std::string passDuSysteme;


};
#endif