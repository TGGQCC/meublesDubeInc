/**
    Gestion d'un serveur WEB
    @file MyServer.cpp
    @author Alain Dubé
    @version 1.1 20/11/20 

    Modifications :
                    2021-11-01  Jérémie Cyr Ajout de routes
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

    this->on("/main", HTTP_GET, [](AsyncWebServerRequest *request) {
            request->send(SPIFFS, "/main.html", "text/html");
            });

    //Route de la page du four
    this->on("/login", HTTP_POST, [](AsyncWebServerRequest *request) {
            Serial.println("login... ");
            String response;
            HTTPClient http;
            String user;
            String password;

           if(request->hasParam("user", true) && request->hasParam("password", true))
            {
                String woodApiRestAddress = "http://172.16.200.254:3000/api/login";     //API
                http.begin(woodApiRestAddress);
                String response = http.getString();
                user = request->getParam("user", true)->value();
                password = request->getParam("password", true)->value();
                String json = "{\"user\":\""+ user + "\",\"password\":\""+ password +"\"}";                
                http.addHeader("Accept", "application/json");
                http.addHeader("Content-Type", "application/json");
                http.POST(json);
                response = http.getString();
                request->send(200, "text/plain", response);
            }else
            {
                 response = "Aucun bois sélectionné";
            }

            request->send(200, "text/plain");
        });

    //Route de l'image
    this->on("/sac.PNG", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/sac.PNG", "image/png");
        });

    //Route du script JavaScript
    this->on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/script.js", "text/javascript");
        });

    //Route du CSS
    this->on("/index.css", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/global.css", "text/css");
        });
    
    //Route de la page 404
    this->onNotFound([](AsyncWebServerRequest *request){
        request->send(404, "text/plain", "Page Not Found");
        });
    
    //Route pour obtenir tout les bois
    this->on("/getAllWoodOptions", HTTP_GET, [](AsyncWebServerRequest *request) {
            Serial.println("getAllWoodOptions... ");

            HTTPClient http;
            String woodApiRestAddress = "http://172.16.200.254:3000/api/getAllWoods";       //API
            http.begin(woodApiRestAddress);
            http.setAuthorization(request->getHeader("Authorization")->value().c_str());
            http.GET();
            String response = http.getString();
            Serial.println(response);
            request->send(200, "text/plain", response);
        });

        //Route pour obtenir les informations d'un bois
        this->on("/getCaracteristicsOf", HTTP_GET, [](AsyncWebServerRequest *request) {
            Serial.println("getCaracteristicsOf... ");
            String response;
            String id;
            HTTPClient http;
            if(request->hasParam("id"))
            {
                Serial.println(request->getParam("id")->value());
                String woodApiRestAddress = "http://172.16.200.254:3000/api/getCaracterisiticsOf/" + request->getParam("id")->value();      //API
                http.begin(woodApiRestAddress);
                http.setAuthorization(request->getHeader("Authorization")->value().c_str());
                http.GET();
                response = http.getString();
            }else
            {
                 response = "Aucun bois sélectionné";
            }

            request->send(200, "text/plain", response);
        });

        //Route pour démarrer le four
        this->on("/postDemarrerFour", HTTP_POST, [](AsyncWebServerRequest *request) {
            Serial.println("Démarrage du four... ");
            string tempsSechage;
            string temperatureSechage;

            if(request->hasParam("tempsSechage", true) && request->hasParam("temperatureSechage", true))
            {
                tempsSechage = request->getParam("tempsSechage", true)->value().c_str();
                temperatureSechage = request->getParam("temperatureSechage", true)->value().c_str();
                std::string repString = "";
                if (ptrToCallBackFunction) repString = (*ptrToCallBackFunction)("demarrerFour " + tempsSechage + " " + temperatureSechage);
            }
        });

        //Route pour arrêter le four
        this->on("/postStopFour", HTTP_POST, [](AsyncWebServerRequest *request) {
            Serial.println("Stopper le four... ");
            std::string repString = "";
            if (ptrToCallBackFunction) repString = (*ptrToCallBackFunction)("stopFour"); 
        });

        //Route pour obtenir la température actuelle du four
        this->on("/getTemperature", HTTP_GET, [](AsyncWebServerRequest *request) {
            Serial.println("getTemperature... ");
            std::string repString = "";
            if (ptrToCallBackFunction) repString = (*ptrToCallBackFunction)("askTemperature"); 
            String lireTemperature = String(repString.c_str());
            request->send(200, "text/plain", lireTemperature );
        });

    this->begin();
};
