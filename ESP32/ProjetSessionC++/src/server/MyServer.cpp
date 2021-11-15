/**
    Gestion d'un serveur WEB
    @file MyServer.cpp
    @author Alain Dubé
    @version 1.1 20/11/20 
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


    //Route de l'image
    this->on("/sac.PNG", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/sac.PNG", "image/png");
        });

    //Route du script JavaScript
    this->on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/script.js", "text/javascript");
        });

    this->on("/index.css", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/globaln.css", "text/css");
        });
   
    this->onNotFound([](AsyncWebServerRequest *request){
        request->send(404, "text/plain", "Page Not Found");
        });
    
    this->on("/getAllWoodOptions", HTTP_GET, [](AsyncWebServerRequest *request) {
            Serial.println("getAllWoodOptions... ");

            HTTPClient http;
            String woodApiRestAddress = "http://172.16.200.254:3000/api/getAllWoods";
            http.begin(woodApiRestAddress);
            http.GET();
            String response = http.getString();
            Serial.println(response);
            request->send(200, "text/plain", response);
        });

        this->on("/getCaracteristicsOf", HTTP_GET, [](AsyncWebServerRequest *request) {
            Serial.println("getCaracteristicsOf... ");
            String response;
            String id;
            HTTPClient http;
            if(request->hasParam("id"))
            {
                Serial.println(request->getParam("id")->value());
                String woodApiRestAddress = "http://172.16.200.254:3000/api/getCaracterisiticsOf/" + request->getParam("id")->value();
                http.begin(woodApiRestAddress);
                http.GET();
                response = http.getString();
            }else
            {
                 response = "Aucun bois sélectionné";
            }

            request->send(200, "text/plain", response);
        });

        this->on("/postDemarrerFour", HTTP_POST, [](AsyncWebServerRequest *request) {
            Serial.println("Démarrage du four... ");

        });


        this->on("/getTemperature", HTTP_GET, [](AsyncWebServerRequest *request) {
            Serial.println("getTemperature... ");
            std::string repString = "";
            if (ptrToCallBackFunction) repString = (*ptrToCallBackFunction)("askTemperature"); 
            String lireTemperature = String(repString.c_str());
            request->send(200, "text/plain", lireTemperature );
        });

    this->begin();
};
