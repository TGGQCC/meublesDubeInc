/**
    Vue du Oled quand le système travaille et le four est froid
    @file MyOledViewWorkingCOLD.cpp
    @author  Jérémie Cyr
    @version 1.0 21/11/16
*/
#include <Arduino.h>
#include "MyOledViewWorkingCOLD.h"
using namespace std;

void MyOledViewWorkingCOLD::display(Adafruit_SSD1306 *adafruit){
    MyOledViewWorking::display(adafruit);
    adafruit->setCursor(85, 24);
    adafruit->println("Waiting");
    adafruit->setCursor(10, adafruit->getCursorY());
    adafruit->setTextSize(3);
    adafruit->print(getTag("Temperature").c_str());
    adafruit->display();

}

void MyOledViewWorkingCOLD::update(Adafruit_SSD1306 *adafruit){
    adafruit->clearDisplay();
    adafruit->setTextSize(2);


}