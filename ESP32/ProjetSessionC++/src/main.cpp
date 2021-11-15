/* Copyright (C) 2021 Jérémie Cyr
 * All rights reserved.
 *
 * Projet de session
 * Description: 
 * 
 * Ecole du Web
 * Cours Objets connectés (c)2021
 *  
    @file     main.cpp
    @author   Jérémie Cyr
    @version  1.1 2021-11-01

    Historique des versions
           Version    Date        Auteur         Description
           1.0        2021-11-01  Jérémie Cyr    Première version fonctionnelle

    platform = espressif32
    board = esp32doit-devkit-v1
    framework = arduino
    lib_deps =      
             ArduinoJson                (Pour accéder au fonctionnalités Json)
             AsyncTCP-esphome           (Pour utiliser les focntionnalités TCP)
             ESPAsyncWebServer-esphome  (Pour accéder au serveur Web)

   Autres librairies (à copier dans le répertoire lib)
        DHT  //(Pour accéder au senseur de température, Adafruit)
        WiFiManager-master //Contrôle du sans fil

   Stubs : 
   TemperatureStub //Crédits : Alain Dubé

   Fonctions utiles (utilitaires) Crédits : Alain Dubé
        /lib/MYLIB/myFunctions.cpp
            

Classes du système
    MyServer                            V1.0    Gestion des routes de l'interface WEB
            /data                               Répertoire qui contient les fichiers du site WEB 
                index.html              V1.0    Page index de l'interface
                global.css              V1.0    CSS
                script.js               V1.0    JS 
                sac.PNG                         Image fournie par le client
              


     Senseur de température AM2302 / DHT22
            GPIO 15 
      Leds
            GPIO12 : pin 12   Rouge
            GPIO14 : pin 14   Jaune
            GPIO27 : pin 27   Vert       
            
      Boutons
            GPIO32 : T8  
            GPIO33 : T9                   
 * */


#include <iostream>
#include <sstream>    // header file for stringstream
#include <string>
#include <Arduino.h>
#include <ArduinoJson.h>

using namespace std;

#include "myFunctions.cpp" //fonctions utilitaires

#include <wire.h>
#define SCREEN_WIDTH 128        // OLED display width, in pixels
#define SCREEN_HEIGHT 64        // OLED display height, in pixels
#define OLED_RESET 4            // Reset pin # (or -1 if sharing Arduino reset pin)
#define OLED_I2C_ADDRESS 0x3C   // Adresse I2C de l'écran Oled

#include "oled/MyOled.h"
#include "oled/MyOledViewInitialisation.h"
#include "oled/MyOledViewWifiAp.h"
MyOled *myOled = new MyOled(&Wire, OLED_RESET, SCREEN_HEIGHT, SCREEN_WIDTH);
MyOledViewInitialisation *myOledViewInitialisation = NULL;
MyOledViewWifiAp *myOledViewWifiAp = NULL;

//Pour avoir les données du senseur de température
#include "temperature/TemperatureStub.h"
#define DHTPIN  15   // Pin utilisée par le senseur DHT22
#define DHTTYPE DHT22  //Le type de senseur utilisé
TemperatureStub *temperatureStub = NULL;


//Pour la gestion du serveur WEB
#include <HTTPClient.h>
#include <WiFiManager.h>
WiFiManager wm;
#define WEBSERVER_H


//Pour la gestion du serveur ESP32
#include "server/MyServer.h"
MyServer *myServer = NULL;


//Variable pour la connection Wifi
const char *SSID = "JCESP";
const char *PASSWORD = "";
String ssIDRandom;

//Boutons
#include "buttons/MyButton.h"
MyButton *myButtonAction = NULL;
MyButton *myButtonReset = NULL;

//Variable de température
float temperature = NULL; 


//fonction statique qui permet aux objets d'envoyer des messages (callBack) 
//  arg0 : Action 
// arg1 ... : Parametres
std::string CallBackMessageListener(string message) {
    while(replaceAll(message, std::string("  "), std::string(" ")));
    //Décortiquer le message
    string actionToDo = getValue(message, ' ', 0);
    string arg1 = getValue(message, ' ', 1);

    stringstream stream;
    stream << temperature;
    string strTemperature;
    stream >> strTemperature;

    if (string(actionToDo.c_str()).compare(string("askTemperature")) == 0) {  return(strTemperature.c_str()); }

        
        return "";
    }


//Définition des trois leds de statut
#define GPIO_PIN_LED_LOCK_ROUGE         12 //GPIO12
#define GPIO_PIN_LED_OK_GREEN             27 //GPIO27
#define GPIO_PIN_LED_HEAT_YELLOW        14 //GPIO14


void setup() { 
    //Active le serial monitor
    Serial.begin(9600);
    delay(100);

    myOledViewInitialisation = new MyOledViewInitialisation;

    myOled->init(OLED_I2C_ADDRESS);
    myOled->veilleDelay(30); //En secondes
    myOledViewInitialisation->setNomDuSysteme("SAC System");
    myOledViewInitialisation->setIdDuSysteme("SAC_911");
    myOled->displayView(myOledViewInitialisation);

    //Gestion des boutons
    myButtonAction = new MyButton();        //Pour lire le bouton actions
    myButtonReset = new MyButton();        //Pour lire le bouton reset
    myButtonAction->init(T8);
    myButtonAction->init(T9);
    int sensibilisationButtonAction = myButtonAction->autoSensibilisation();
    int sensibilisationButtonReset = myButtonReset->autoSensibilisation();
    Serial.print("sensibilisationButtonAction : "); Serial.println(sensibilisationButtonAction);
    Serial.print("sensibilisationButtonReset : "); Serial.println(sensibilisationButtonReset);
    
    stringstream streamSensibilite;
    streamSensibilite << sensibilisationButtonAction;
    string sensibilite;
    streamSensibilite >> sensibilite;

    myOledViewInitialisation->setSensibiliteBoutonAction(sensibilite);
    
    streamSensibilite << sensibilisationButtonReset;
    streamSensibilite >> sensibilite;
    myOledViewInitialisation->setSensibiliteBoutonReset(sensibilite);

    myOled->updateCurrentView(myOledViewInitialisation);




    

    //Initiation pour la lecture de la température
    temperatureStub = new TemperatureStub;
    temperatureStub->init(DHTPIN, DHTTYPE); //Pin 15 et Type DHT22

    //Initialisation de la led
    pinMode(GPIO_PIN_LED_LOCK_ROUGE, OUTPUT);
    pinMode(GPIO_PIN_LED_HEAT_YELLOW, OUTPUT);
    pinMode(GPIO_PIN_LED_OK_GREEN, OUTPUT);

    

    //Connection au WifiManager
        String ssIDRandom, PASSRandom;
        String stringRandom;
        stringRandom = get_random_string(4).c_str();
        ssIDRandom = SSID;
        ssIDRandom = ssIDRandom + stringRandom;
        stringRandom = get_random_string(4).c_str();
        PASSRandom = PASSWORD;
        PASSRandom = PASSRandom + stringRandom;
        
    //Print les identifiants
    char strToPrint[128];
        sprintf(strToPrint, "Identification : %s   MotDePasse: %s", ssIDRandom, PASSRandom);
        Serial.println(strToPrint);


    if (!wm.autoConnect(ssIDRandom.c_str(), PASSRandom.c_str())){
            Serial.println("Erreur de connexion.");
        
            }
        else {
            Serial.println("Connexion Établie.");
                //Démarrage de la vue de WifiAp
                myOledViewWifiAp = new MyOledViewWifiAp;
                myOledViewWifiAp->setNomDuSysteme("SAC System");
                myOledViewWifiAp->setParams("IdSysteme", "SAC_911");
                myOledViewWifiAp->setSsIDDuSysteme(ssIDRandom.c_str());
                myOledViewWifiAp->setPassDuSysteme(PASSRandom.c_str());
                myOled->displayView(myOledViewWifiAp);
            }

        // ----------- Routes du serveur ----------------
        myServer = new MyServer(80);
        myServer->initAllRoutes();
        myServer->initCallback(&CallBackMessageListener);


  } //setup


void loop() {

        int buttonAction = myButtonAction->checkMyButton();
        temperature = temperatureStub->getTemperature(); //Obtenir la température ambiante



    } //loop