/**
    Gestion de la vue des erreurs de connexion au wifi de l'OLED 
    @file MyOledViewErrorWifiConnexion.cpp
    @author Jérémie Cyr
    @version 1.0 2021/11/01
*/
#include <Arduino.h>
#include "MyOledViewErrorWifiConnexion.h"
using namespace std;

void MyOledViewErrorWifiConnexion::setNomDuSysteme(string val){
        nomDuSysteme = val;
    }

void MyOledViewErrorWifiConnexion::display(Adafruit_SSD1306 *adafruit){
    adafruit->clearDisplay();
    adafruit->setTextSize(2);
    adafruit->setCursor(0, 0);
    adafruit->println(nomDuSysteme.c_str());
    adafruit->setTextSize(1);
    adafruit->println("Erreur de connexion au Wifi");
    adafruit->display();
}

void MyOledViewErrorWifiConnexion::update(Adafruit_SSD1306 *adafruit){
    adafruit->clearDisplay();
    adafruit->setTextSize(2);
    adafruit->setCursor(0, 0);
    adafruit->println(nomDuSysteme.c_str());
    adafruit->setTextSize(1);
    adafruit->println("Erreur de connexion au Wifi");
    adafruit->display();
}