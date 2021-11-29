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

using namespace std;

#include <iostream>
#include <sstream>    // header file for stringstream
#include <string>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <chrono>
#include "myFunctions.cpp" //fonctions utilitaires
#include <wire.h>
//Vues
#include "oled/MyOled.h"    
#include "oled/MyOledViewInitialisation.h"  
#include "oled/MyOledViewWifiAp.h"
#include "oled/MyOledViewWorking.h"
#include "oled/MyOledViewWorkingCOLD.h"
#include "oled/MyOledViewWorkingHEAT.h"
#include "oled/MyOledViewWorkingOFF.h"
#include "oled/MyOledViewErrorWifiConnexion.h"

#define SCREEN_WIDTH 128        // OLED display width, in pixels
#define SCREEN_HEIGHT 64        // OLED display height, in pixels
#define OLED_RESET 4            // Reset pin # (or -1 if sharing Arduino reset pin)
#define OLED_I2C_ADDRESS 0x3C   // Adresse I2C de l'écran Oled
//Définition des trois leds de statut
#define GPIO_PIN_LED_LOCK_ROUGE         12 //GPIO12
#define GPIO_PIN_LED_OK_GREEN             27 //GPIO27
#define GPIO_PIN_LED_HEAT_YELLOW        14 //GPIO14

//Vues
MyOled *myOled = new MyOled(&Wire, OLED_RESET, SCREEN_HEIGHT, SCREEN_WIDTH);
MyOledViewInitialisation *myOledViewInitialisation = NULL;
MyOledViewWifiAp *myOledViewWifiAp = NULL;
MyOledViewWorking *myOledViewWorking = NULL;
MyOledViewWorkingCOLD *myOledViewWorkingCOLD = NULL;
MyOledViewWorkingHEAT *myOledViewWorkingHEAT = NULL;
MyOledViewWorkingOFF *myOledViewWorkingOFF = NULL;
MyOledViewErrorWifiConnexion *myOledViewErrorWifiConnexion = NULL;


//Pour avoir les données du senseur de température
#include "temperature/TemperatureStub.h"
#define DHTPIN  15   // Pin utilisée par le senseur DHT22
#define DHTTYPE DHT22  //Le type de senseur utilisé
TemperatureStub *temperatureStub = NULL;


//Pour la gestion du serveur WEB
#include <HTTPClient.h>
#include <WiFiManager.h>
string ip;
WiFiManager wm;
#define WEBSERVER_H

//Pour la gestion du serveur ESP32
#include "server/MyServer.h"
MyServer *myServer = NULL;


//Variable pour la connection Wifi
const char *SSID = "JCESP";
const char *PASSWORD = "JCESP";
String ssIDRandom;

//Boutons
#include "buttons/MyButton.h"
MyButton *myButtonAction = NULL;
MyButton *myButtonReset = NULL;

//Variable de température
float temperature = NULL; 
bool sechage = false;
string temperatureSechage;
string tempsSechage;
int compteurSechage = 0;

//fonction statique qui permet aux objets d'envoyer des messages (callBack) 
//  arg0 : Action 
// arg1 ... : Parametres
std::string CallBackMessageListener(string message) {
    while(replaceAll(message, std::string("  "), std::string(" ")));
    //Décortiquer le message
    string actionToDo = getValue(message, ' ', 0);
    string arg1 = getValue(message, ' ', 1);
    string arg2 = getValue(message, ' ', 2);

    stringstream stream;
    stream << temperature;
    string strTemperature;
    stream >> strTemperature;

    if (string(actionToDo.c_str()).compare(string("askTemperature")) == 0) {  return(strTemperature.c_str()); }
    
    if (string(actionToDo.c_str()).compare(string("demarrerFour")) == 0) { 
        sechage = true;         
        tempsSechage = arg1;
        temperatureSechage = arg2;
        Serial.println(tempsSechage.c_str());
        Serial.println(temperatureSechage.c_str());
        }
        
    if (string(actionToDo.c_str()).compare(string("stopFour")) == 0) { sechage = false; compteurSechage = 0;}

    return "";
}








void setup() { 
    //Active le serial monitor
    Serial.begin(9600);
    delay(100);

    myOledViewInitialisation = new MyOledViewInitialisation;
    myOled->init(OLED_I2C_ADDRESS);
    myOled->veilleDelay(60); //En secondes
    myOledViewInitialisation->setNomDuSysteme("SAC System");
    myOledViewInitialisation->setIdDuSysteme("SAC_911");
    myOled->displayView(myOledViewInitialisation);

    //Gestion des boutons
    myButtonAction = new MyButton();        //Pour lire le bouton actions
    myButtonReset = new MyButton();        //Pour lire le bouton reset
    myButtonAction->init(T8);
    myButtonReset->init(T9);
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


         myOledViewWifiAp = new MyOledViewWifiAp;
         myOledViewWifiAp->setNomDuSysteme("SAC System");
         myOledViewWifiAp->setParams("IdSysteme", "SAC_911");
         myOledViewWifiAp->setSsIDDuSysteme(ssIDRandom.c_str());
         myOledViewWifiAp->setPassDuSysteme(PASSRandom.c_str());
         myOled->displayView(myOledViewWifiAp);


    if (!wm.autoConnect(ssIDRandom.c_str(), PASSRandom.c_str())){
            Serial.println("Erreur de connexion.");
            myOledViewErrorWifiConnexion = new MyOledViewErrorWifiConnexion;
            myOledViewErrorWifiConnexion->setNomDuSysteme("SAC System");
            myOled->displayView(myOledViewErrorWifiConnexion);

            }
        else {
                Serial.println("Connexion Établie.");      
                    digitalWrite(GPIO_PIN_LED_LOCK_ROUGE, HIGH);
                    digitalWrite(GPIO_PIN_LED_HEAT_YELLOW, HIGH);
                    digitalWrite(GPIO_PIN_LED_OK_GREEN, HIGH);
                    delay(500);
                    digitalWrite(GPIO_PIN_LED_LOCK_ROUGE, LOW);
                    digitalWrite(GPIO_PIN_LED_HEAT_YELLOW, LOW);
                    digitalWrite(GPIO_PIN_LED_OK_GREEN, LOW);
                    delay(500);
                    digitalWrite(GPIO_PIN_LED_LOCK_ROUGE, HIGH);
                    digitalWrite(GPIO_PIN_LED_HEAT_YELLOW, HIGH);
                    digitalWrite(GPIO_PIN_LED_OK_GREEN, HIGH);
                    delay(500);
                    digitalWrite(GPIO_PIN_LED_LOCK_ROUGE, LOW);
                    digitalWrite(GPIO_PIN_LED_HEAT_YELLOW, LOW);
                    digitalWrite(GPIO_PIN_LED_OK_GREEN, LOW);

            }

            ip = WiFi.localIP().toString().c_str();

        // ----------- Routes du serveur ----------------
        myServer = new MyServer(80);
        myServer->initAllRoutes();
        myServer->initCallback(&CallBackMessageListener);
        
        //Initialisation des vues COLD, HEAT et OFF
        myOledViewWorkingCOLD = new MyOledViewWorkingCOLD;
        myOledViewWorkingCOLD->init("SAC_911");
        myOledViewWorkingHEAT = new MyOledViewWorkingHEAT;
        myOledViewWorkingOFF = new MyOledViewWorkingOFF;


  } //setup


void loop() {
        myOled->veilleCheck(false); //Active la mise en veille
        
        int buttonAction = myButtonAction->checkMyButton(); //Bouton qui sors de la veille
        int buttonReset = myButtonReset->checkMyButton(); //Bouton qui redémarre l'ESP
        temperature = temperatureStub->getTemperature(); //Obtenir la température ambiante
        
        //Tradruit la temperature en string
        stringstream streamTemperature;
        streamTemperature << temperature;
        string temperatureString;
        streamTemperature >> temperatureString;

        //Calcul de +ou- 10% de la température minimale de séchage
        float temperatureSechageFloat = std::atof(temperatureSechage.c_str());
        float tempsSechageFloat = std::atof(tempsSechage.c_str());
        float temperatureSechageMin = temperatureSechageFloat - (0.10 * temperatureSechageFloat);
        float temperatureSechageMax = temperatureSechageFloat + (0.10 * temperatureSechageFloat);


        //Sortir de veille
        if(buttonAction > 2){
            Serial.println("Sortie de veille...");
            myOled->veilleExit();
        }

        //Redémarrer le système
        if(buttonReset > 2){
            Serial.println("Restarting...");
            ESP.restart();
        }

        //Logique du four et de l'affichage des vues et des leds
        if(sechage)
        {
            if(temperature < temperatureSechageMin){
                myOledViewWorkingCOLD->setParams("NomSysteme","SAC System");
                myOledViewWorkingCOLD->setParams("IdSysteme", "SAC_911");
                myOledViewWorkingCOLD->setParams("Temperature", temperatureString);
                myOledViewWorkingCOLD->setParams("Ip", ip);
                myOled->displayView(myOledViewWorkingCOLD);
                digitalWrite(GPIO_PIN_LED_LOCK_ROUGE, HIGH);
                digitalWrite(GPIO_PIN_LED_HEAT_YELLOW, LOW);
                digitalWrite(GPIO_PIN_LED_OK_GREEN, LOW);
            }
            while(temperature >= temperatureSechageMin && temperature <= temperatureSechageMax && compteurSechage <= tempsSechageFloat && sechage){
                    myOledViewWorkingHEAT->setParams("NomSysteme","SAC System");
                    myOledViewWorkingHEAT->setParams("IdSysteme", "SAC_911");
                    myOledViewWorkingHEAT->setParams("Temperature", temperatureString);
                    myOledViewWorkingHEAT->setParams("Ip", ip);
                    myOled->displayView(myOledViewWorkingHEAT);
                    digitalWrite(GPIO_PIN_LED_LOCK_ROUGE, LOW);
                    digitalWrite(GPIO_PIN_LED_HEAT_YELLOW, HIGH);
                    digitalWrite(GPIO_PIN_LED_OK_GREEN, LOW);
                    compteurSechage = compteurSechage + 1;
                    Serial.println(compteurSechage);
                    Serial.println(tempsSechageFloat);
                    delay(1000);
                    if(compteurSechage == tempsSechageFloat){
                        sechage = false;
                        compteurSechage = 0;
                        digitalWrite(GPIO_PIN_LED_LOCK_ROUGE, LOW);
                        digitalWrite(GPIO_PIN_LED_HEAT_YELLOW, LOW);
                        digitalWrite(GPIO_PIN_LED_OK_GREEN, LOW);
                    }
            }
            if(temperature > temperatureSechageMax){
                myOledViewWorkingCOLD->setParams("NomSysteme","SAC System");
                myOledViewWorkingCOLD->setParams("IdSysteme", "SAC_911");
                myOledViewWorkingCOLD->setParams("Temperature", temperatureString);
                myOledViewWorkingCOLD->setParams("Ip", ip);
                myOled->displayView(myOledViewWorkingCOLD);
                digitalWrite(GPIO_PIN_LED_LOCK_ROUGE, HIGH);
                digitalWrite(GPIO_PIN_LED_HEAT_YELLOW, LOW);
                digitalWrite(GPIO_PIN_LED_OK_GREEN, LOW);
            }
        }
        else{
            myOledViewWorkingOFF->setParams("NomSysteme","SAC System");
            myOledViewWorkingOFF->setParams("IdSysteme", "SAC_911");
            myOledViewWorkingOFF->setParams("Temperature", temperatureString);
            myOledViewWorkingOFF->setParams("Ip", ip);
            myOled->displayView(myOledViewWorkingOFF);
            digitalWrite(GPIO_PIN_LED_LOCK_ROUGE, LOW);
            digitalWrite(GPIO_PIN_LED_HEAT_YELLOW, LOW);
            digitalWrite(GPIO_PIN_LED_OK_GREEN, HIGH);
        }
    } //loop