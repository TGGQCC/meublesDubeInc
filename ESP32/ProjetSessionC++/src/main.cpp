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
 * */


#include <iostream>
#include <string>
#include <Arduino.h>
#include <ArduinoJson.h>

using namespace std;

#include "myFunctions.cpp" //fonctions utilitaires


//Pour avoir les données du senseur de température
#include "TemperatureStub.h"
#define DHTPIN  15   // Pin utilisée par le senseur DHT22
#define DHTTYPE DHT22  //Le type de senseur utilisé
TemperatureStub *temperatureStub = NULL;


//Pour la gestion du serveur WEB
#include <HTTPClient.h>
#include <WiFiManager.h>
WiFiManager wm;
#define WEBSERVER_H


//Pour la gestion du serveur ESP32
#include "MyServer.h"
MyServer *myServer = NULL;


//Variable pour la connection Wifi
const char *SSID = "JCESP";
const char *PASSWORD = "";
String ssIDRandom;


//Variable de température
int temperature = NULL; 


//fonction statique qui permet aux objets d'envoyer des messages (callBack) 
//  arg0 : Action 
// arg1 ... : Parametres
std::string CallBackMessageListener(string message) {
    while(replaceAll(message, std::string("  "), std::string(" ")));
    //Décortiquer le message
    string actionToDo = getValue(message, ' ', 0);
    string arg1 = getValue(message, ' ', 1);

    //Va chercher la valeur de température qui a été entrée par l'utilisateur sur action
    if (string(actionToDo.c_str()).compare(string("action")) == 0) {
        temperature = std::atoi(arg1.c_str());
        Serial.println(temperature);
        }
   
    std::string result = "";
    return result;
    }


//Définition de la led 
#define GPIO_PIN_LED_ROUGE         12 //GPIO12


void setup() { 
    //Active le serial monitor
    Serial.begin(9600);
    delay(100);

    //Initiation pour la lecture de la température
    temperatureStub = new TemperatureStub;
    temperatureStub->init(DHTPIN, DHTTYPE); //Pin 15 et Type DHT22

    //Initialisation de la led
    pinMode(GPIO_PIN_LED_ROUGE, OUTPUT);

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
            }

        // ----------- Routes du serveur ----------------
        myServer = new MyServer(80);
        myServer->initAllRoutes();
        myServer->initCallback(&CallBackMessageListener);


  } //setup


void loop() {

        float t = temperatureStub->getTemperature(); //Obtenir la température ambiante



    } //loop