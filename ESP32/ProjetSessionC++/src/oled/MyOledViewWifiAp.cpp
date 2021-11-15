/**
    Initialisation d'un écran Oled Utilisant un GPIO d'un contrôleur
    @file MyOledViewInitialisation.cpp
    @author  Jérémie Cyr
    @version 1.0 21/11/01
*/
#include "MyOledViewWifiAp.h"
using namespace std;


void MyOledViewWifiAp::setNomDuSysteme(string val){
        nomDuSysteme = val;
    }

void MyOledViewWifiAp::setSsIDDuSysteme(string val){
        ssIDDuSysteme = val;
    }

void MyOledViewWifiAp::setPassDuSysteme(string val){
        passDuSysteme = val;
    }


void MyOledViewWifiAp::display(Adafruit_SSD1306 *adafruit){
    adafruit->clearDisplay();
    adafruit->setTextSize(2);
    adafruit->setCursor(0, 0);
    adafruit->setTextColor(SSD1306_WHITE);
    adafruit->println(nomDuSysteme.c_str());
    adafruit->setTextSize(1);
    adafruit->setTextColor(SSD1306_WHITE);
    adafruit->println();
    adafruit->print("Id : ");
    adafruit->println(getTag("IdSysteme").c_str());
    adafruit->println("AP configuration");
    adafruit->setCursor(22, adafruit->getCursorY());
    adafruit->print("SSID : ");
    adafruit->println(ssIDDuSysteme.c_str());
    adafruit->setCursor(22, adafruit->getCursorY());
    adafruit->print("PASS : ");
    adafruit->println(passDuSysteme.c_str());
    adafruit->display();
    

}

void MyOledViewWifiAp::update(Adafruit_SSD1306 *adafruit){

}