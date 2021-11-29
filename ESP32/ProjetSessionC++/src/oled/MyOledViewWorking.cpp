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


        Fire24x24Pointers[0] = const_cast<unsigned char *>(&Fire24x24_1[0]);
        Fire24x24Pointers[1] = const_cast<unsigned char *>(&Fire24x24_2[0]);
        Fire24x24Pointers[2] = const_cast<unsigned char *>(&Fire24x24_3[0]);
        Fire24x24Pointers[3] = const_cast<unsigned char *>(&Fire24x24_4[0]);
        Fire24x24Pointers[4] = const_cast<unsigned char *>(&Fire24x24_5[0]);
        Fire24x24Pointers[5] = const_cast<unsigned char *>(&Fire24x24_6[0]);
    }


/**
 * displayGifFire affiche une image de feu statique
 *
 * Affiche une image de feu statique
 * 
 */
void MyOledViewWorking::displayGifFire(Adafruit_SSD1306 *adafruit, int positionX, int positionY) {
    adafruit->setTextSize(1);
    adafruit->drawBitmap(positionX, positionY, Fire24x24Pointers[0], 24, 24, WHITE);
    }


/**
 * displayGifFire affiche une image de feu animée
 *
 * Affiche une image de feu animée
 * 
 */
void MyOledViewWorking::displayGifFireAnimated(Adafruit_SSD1306 *adafruit, int positionX, int positionY) {
int secondes = atoi(getTag("secondes").c_str());
    adafruit->setTextSize(1);
    for (int index = 0; index <= secondes; index++) {
        adafruit->drawBitmap(positionX, positionY, Fire24x24Pointers[(++indexFire) % 6], 24, 24, WHITE);

        adafruit->display();
        delay(1000);
    }
    delay(indexFireDelay * 2);
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

    adafruit->setCursor(40, 56);
    adafruit->println(getTag("Ip").c_str());
}

void MyOledViewWorking::update(Adafruit_SSD1306 *adafruit){

}