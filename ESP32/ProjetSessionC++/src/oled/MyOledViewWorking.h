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
    


**/


#ifndef MYOLEDVIEWWORKING_H
#define MYOLEDVIEWWORKING_H
#include <Adafruit_SSD1306.h>
#include <string>
#include "MyOledView.h"

//Feu animé
// (Horizontal) byte array of bitmap :
// NOTE: width NOT a multiple of 8 (required by some LCDs & printers)
//http : //en.radzio.dxp.pl/bitmap_converter/
const unsigned char Fire24x24_1[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x70, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x7f, 
	0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x80, 0x01, 0xff, 0xc0, 0x03, 0xff, 0xc0, 0x07, 0xff, 0xe0, 
	0x07, 0xff, 0xe0, 0x07, 0xff, 0xe0, 0x07, 0xff, 0xe0, 0x03, 0xff, 0xc0, 0x03, 0xff, 0xc0, 0x01, 
	0xff, 0x80, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00 };



const unsigned char Fire24x24_2[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x38, 0x00, 0x00, 0x3c, 
	0x00, 0x00, 0x7e, 0x00, 0x00, 0x7f, 0x00, 0x00, 0xff, 0x80, 0x01, 0xff, 0xc0, 0x01, 0xff, 0xc0, 
	0x03, 0xff, 0xc0, 0x03, 0xff, 0xc0, 0x03, 0xff, 0xc0, 0x01, 0xff, 0xc0, 0x01, 0xff, 0xc0, 0x00, 
	0xff, 0x80, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00
};


const unsigned char Fire24x24_3[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
	0x00, 0x00, 0x38, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x7e, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x80, 
	0x01, 0xff, 0xc0, 0x01, 0xff, 0xc0, 0x01, 0xff, 0xc0, 0x01, 0xff, 0x80, 0x00, 0xff, 0x80, 0x00, 
	0x7f, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00
};


const unsigned char Fire24x24_4[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x1f, 
	0x00, 0x00, 0x3f, 0x80, 0x00, 0x7f, 0x80, 0x00, 0x7f, 0xc0, 0x00, 0xff, 0xe0, 0x01, 0xff, 0xe0, 
	0x01, 0xff, 0xe0, 0x01, 0xff, 0xe0, 0x00, 0xff, 0xe0, 0x00, 0xff, 0xe0, 0x00, 0x7f, 0xc0, 0x00, 
	0x3f, 0x80, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00
};


const unsigned char Fire24x24_5[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x7e, 
	0x00, 0x00, 0xff, 0x00, 0x01, 0xff, 0x00, 0x01, 0xff, 0x80, 0x03, 0xff, 0xe0, 0x03, 0xff, 0xf0, 
	0x03, 0xff, 0xf0, 0x03, 0xff, 0xf0, 0x01, 0xff, 0xf0, 0x00, 0xff, 0xe0, 0x00, 0x7f, 0xc0, 0x00, 
	0x1f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


const unsigned char Fire24x24_6[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x30, 0x00, 0x00, 0x70, 0x00, 0x00, 0xf8, 0x00, 0x00, 0xfc, 
	0x00, 0x01, 0xfe, 0x00, 0x03, 0xff, 0x80, 0x03, 0xff, 0xe0, 0x03, 0xff, 0xe0, 0x03, 0xff, 0xf0, 
	0x03, 0xff, 0xe0, 0x03, 0xff, 0xe0, 0x03, 0xff, 0xc0, 0x01, 0xff, 0x80, 0x00, 0xff, 0x00, 0x00, 
	0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};



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