/**
    Vue du Oled quand le système travaille
    @file MyOledViewWorking.cpp
    @author  Jérémie Cyr
    @version 1.0 21/11/16
*/
#include "MyOledViewWorking.h"
using namespace std;

void MyOledViewWorking::init(std::string _id) {

    Serial.println("Init dans MyOledViewWorking");
    setParams("id", _id);
    }


/**
 * displayGifFire affiche une image de feu statique
 *
 * Affiche une image de feu statique
 * 
 */
void MyOledViewWorking::displayGifFire(Adafruit_SSD1306 *adafruit, int positionX, int positionY) {
    adafruit->clearDisplay();
    adafruit->setTextSize(1);

    }


/**
 * displayGifFire affiche une image de feu animée
 *
 * Affiche une image de feu animée
 * 
 */
void MyOledViewWorking::displayGifFireAnimated(Adafruit_SSD1306 *adafruit, int positionX, int positionY) {
    adafruit->clearDisplay();
    adafruit->setTextSize(1);
    
    }


void MyOledViewWorking::display(Adafruit_SSD1306 *adafruit){
    adafruit->clearDisplay();
    adafruit->setTextSize(2);

    adafruit->setCursor(0, 0);
    adafruit->println(getTag("NomSysteme").c_str());
    adafruit->setTextSize(1);

    adafruit->println();
    adafruit->print("Id : ");
    adafruit->print(getTag("IdSysteme").c_str());

    adafruit->setCursor(40, 55);
    adafruit->println(getTag("Ip").c_str());
}

void MyOledViewWorking::update(Adafruit_SSD1306 *adafruit){

}