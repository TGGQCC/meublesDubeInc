/**
    Gestion d'un serveur WEB
    @file MyServer.cpp
    @author Alain Dubé
    @version 1.1 20/11/20 

    Modifications : 
    Auteur : Jérémie Cyr    Date : 2021-10-26      Description : Ajout et modification de routes
*/
#include <Arduino.h>
#include "MyServer.h"
using namespace std;

typedef std::string (*CallbackType)(std::string);
CallbackType MyServer::ptrToCallBackFunction = NULL;

//Exemple pour appeler une fonction CallBack
//if (ptrToCallBackFunction) (*ptrToCallBackFunction)(stringToSend); 
void MyServer::initCallback(CallbackType callback) {
    ptrToCallBackFunction = callback;
    }

void MyServer::initAllRoutes() { 
    currentTemperature = 3.3f;

    //Initialisation du SPIFF.
    if (!SPIFFS.begin(true)) {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
        }

    //Route initiale (page html)
    this->on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/index.html", "text/html");
        });

    //Route du script JavaScript
    this->on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/script.js", "text/javascript");
        });

    //Route du fichier CSS
    this->on("/global.css", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/global.css", "text/css");
        });
   
    //Route 404
    this->onNotFound([](AsyncWebServerRequest *request){
        request->send(404, "text/plain", "Page Not Found");
        });
    
    //Route de l'image
    this->on("/leddartech.png", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/leddartech.png", "image/png");
        });

    //Route pour l'action getTemperature qui retourne la température saisie par l'utilisateur
    this->on("/getTemperature", HTTP_GET, [](AsyncWebServerRequest *request) {
        Serial.println("getTemperature... ");
        string temperature = "";
        if(request->hasParam("temperature"))
        {
            temperature = request->getParam("temperature")->value().c_str();
            if (ptrToCallBackFunction) (*ptrToCallBackFunction)("action " + temperature);
        }else
        {
            Serial.println("Erreur lors de l'obtention de la température... ");
        }
    });

    this->begin();
};
