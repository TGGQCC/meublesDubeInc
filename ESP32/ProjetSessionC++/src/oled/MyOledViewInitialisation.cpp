/**
    Initialisation d'un écran Oled Utilisant un GPIO d'un contrôleur
    @file MyOledViewInitialisation.cpp
    @author  Jérémie Cyr
    @version 1.0 21/11/01
*/
#include "MyOledViewInitialisation.h"
using namespace std;


void MyOledViewInitialisation::setNomDuSysteme(string val){
        nomDuSysteme = val;
    }

void MyOledViewInitialisation::setIdDuSysteme(string val){
        idDuSysteme = val;
    }

void MyOledViewInitialisation::setSensibiliteBoutonAction(string val){
        sensibiliteBoutonAction = val;
    }

void MyOledViewInitialisation::setSensibiliteBoutonReset(string val){
        sensibiliteBoutonReset = val;
    }

void MyOledViewInitialisation::display(Adafruit_SSD1306 *adafruit){
    adafruit->clearDisplay();
    adafruit->setTextSize(2);
    adafruit->setCursor(0, 0);
    adafruit->setTextColor(SSD1306_WHITE);
    adafruit->println(nomDuSysteme.c_str());
    adafruit->setTextSize(1);
    adafruit->setTextColor(SSD1306_WHITE);
    adafruit->println();
    adafruit->print("Id : ");
    adafruit->println(idDuSysteme.c_str());
    adafruit->println("INITIALISATION");
    adafruit->println("Bouton ACTION: ????");
    adafruit->println("Bouton RESET: ????");
    adafruit->display();
    

}

void MyOledViewInitialisation::update(Adafruit_SSD1306 *adafruit){
    adafruit->clearDisplay();
    adafruit->setTextSize(2);
    adafruit->setCursor(0, 0);
    adafruit->setTextColor(SSD1306_WHITE);
    adafruit->println(nomDuSysteme.c_str());
    adafruit->setTextSize(1);
    adafruit->setTextColor(SSD1306_WHITE);
    adafruit->println();
    adafruit->print("Id : ");
    adafruit->println(idDuSysteme.c_str());
    adafruit->println("INITIALISATION");
    adafruit->print("Bouton ACTION: ");
    adafruit->println(sensibiliteBoutonAction.c_str());
    adafruit->print("Bouton RESET: ");
    adafruit->println(sensibiliteBoutonReset.c_str());
    adafruit->display();
}