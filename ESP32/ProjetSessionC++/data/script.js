/*
*   Auteur : Jérémie Cyr
*   Date : 2021-10-26
*   Description : Fonctions Javascript
*
*/
function sendToESP_getTemperature() {
    var temperature = document.getElementById("temperature").value;
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "getTemperature?temperature="+temperature, true);
    xhttp.send();
}