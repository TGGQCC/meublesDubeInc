/**
    Class MyOledView : Gestion de la vue working
    @file MyOledViewWorking.h 
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


#ifndef MYOLEDVIEWWORKING_H
#define MYOLEDVIEWWORKING_H
#include <Adafruit_SSD1306.h>
#include <string>
#include "MyOledView.h"

class MyOledViewWorking : public MyOledView {
    public:                
        void init(std::string _id);

    private:


    protected:
        int indexFire;
        int indexFireDelay;
        unsigned char *Fire24x24Pointers[6];

        void displayGifFire(Adafruit_SSD1306 *adafruit, int positionX, int positionY);
        void displayGifFireAnimated(Adafruit_SSD1306 *adafruit, int positionX, int positionY);
        void display(Adafruit_SSD1306 *adafruit);
        void update(Adafruit_SSD1306 *adafruit);
};

#endif