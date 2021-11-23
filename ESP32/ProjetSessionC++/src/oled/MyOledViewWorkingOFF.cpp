/**
    Vue du Oled quand le système travaille et le four est éteint
    @file MyOledViewWorkingOFF.cpp
    @author  Jérémie Cyr
    @version 1.0 21/11/16
*/
#include <Arduino.h>
#include "MyOledViewWorkingOFF.h"
using namespace std;

void MyOledViewWorkingOFF::display(Adafruit_SSD1306 *adafruit){
    MyOledViewWorking::display(adafruit);
    adafruit->setCursor(95, 24);
    adafruit->println("Ready");
    adafruit->setCursor(95, adafruit->getCursorY());
    adafruit->print(getTag("Temperature").c_str());

    adafruit->display();
}
