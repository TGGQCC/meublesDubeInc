/**
    Vue du Oled quand le système travaille et le four chauffe
    @file MyOledViewWorkingHEAT.cpp
    @author  Jérémie Cyr
    @version 1.0 21/11/16
*/
#include <Arduino.h>
#include "MyOledViewWorkingHEAT.h"
using namespace std;

void MyOledViewWorkingHEAT::display(Adafruit_SSD1306 *adafruit){
    MyOledViewWorking::display(adafruit);
    MyOledViewWorking::displayGifFire(adafruit, 80,31);
    adafruit->setCursor(85, 24);
    adafruit->println("Heating");
    adafruit->setCursor(10, adafruit->getCursorY() + 3);
    adafruit->setTextSize(2);
    adafruit->print(getTag("Temperature").c_str());
    adafruit->display();
}

void MyOledViewWorkingHEAT::update(Adafruit_SSD1306 *adafruit){
    adafruit->clearDisplay();
    adafruit->setTextSize(2);
}