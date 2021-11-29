let compteurSechage = 0;
let sechage = false;

function getFromESP_getAllWoodOptions() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            var listeBois = JSON.parse(this.responseText);
            for (i = 0; i < listeBois.length; i++) {
                var x = document.getElementById("selectBois");
                var option = document.createElement("option");
                option.value = listeBois[i]["id"];
                option.text = listeBois[i]["nom"];
                x.add(option);
                } 
                getFromESP_getCaracterisiticsOf(1);

            //Refresh le contenu
            var siteHeader = document.getElementById('selectBois');
            siteHeader.style.display='none';
            siteHeader.offsetHeight; // no need to store this anywhere, the reference is enough
            siteHeader.style.display='block';

            }
    };
    xhttp.open("GET", "getAllWoodOptions", true);
    xhttp.setRequestHeader('Authorization', window.localStorage.getItem("token")); 

    xhttp.send();
}

function getFromESP_getCaracterisiticsOf(id) {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            var listeBois = JSON.parse(this.responseText);
            for (i = 0; i < listeBois.length; i=i+2) {
                document.getElementById("nom").innerText = ":" + listeBois[i]["nom"];
                document.getElementById("type").innerText = ":" + listeBois[i]["type"];
                document.getElementById("origine").innerText = ":" + listeBois[i]["origine"];
                document.getElementById("sechage").innerText = listeBois[i]["sechage"];
                document.getElementById("temp_min").innerText = listeBois[i]["temp_min"];
                document.getElementById("boisFour").innerText = listeBois[i]["nom"];
                document.getElementById("temp_minFour").innerText = "(min:" + listeBois[i]["temp_min"] + " Celsius)";
                document.getElementById("sechageFour").innerText = "/" + listeBois[i]["sechage"] + "s";
                } 

            //Refresh le contenu
            var siteHeader = document.getElementById('selectBois');
            siteHeader.style.display='none';
            siteHeader.offsetHeight; // no need to store this anywhere, the reference is enough
            siteHeader.style.display='block';

            }
    };

    xhttp.open("GET", "getCaracteristicsOf?id="+id, true);
    xhttp.setRequestHeader('Authorization', window.localStorage.getItem("token"));
    xhttp.send();
}


    function postToESP_demarrerFour(){
        document.getElementById("btnDemarrerFour").style.display = "none";
        document.getElementById("btnStopFour").style.display = "block";
        let tempsSechage = document.getElementById("sechage").innerText;
        let temperatureSechage = document.getElementById("temp_min").innerText;
        console.log(temperatureSechage);
        console.log(tempsSechage);
        var xhttp = new XMLHttpRequest();
        xhttp.open("POST", "postDemarrerFour", true);
        xhttp.send("tempsSechage="+tempsSechage+"&temperatureSechage="+temperatureSechage);
        sechage = true;
        }

    function postToESP_stopFour(){
            document.getElementById("btnDemarrerFour").style.display = "block";
            document.getElementById("btnStopFour").style.display = "none";

            var xhttp = new XMLHttpRequest();
            xhttp.open("POST", "postStopFour", true);
            xhttp.send();
            sechage = false;
            compteurSechage = 0;
            document.getElementById("compteurSechage").innerText = compteurSechage;
            document.getElementById("ledRouge").style.background = "white";
            document.getElementById("ledJaune").style.background = "white";
            document.getElementById("ledVerte").style.background = "green";
        }


    
    (setInterval(function(){
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById("temperatureActuelle").innerText = this.responseText + " Celsius";
                let temperature = parseFloat(this.responseText);
                let tempsSechage = document.getElementById("sechage").innerText;
                let temperatureSechage = document.getElementById("temp_min").innerText;
                let temperatureSechageMin = parseFloat(temperatureSechage) - (0.10 * parseFloat(temperatureSechage));
                let temperatureSechageMax = parseFloat(temperatureSechage) + (0.10 * parseFloat(temperatureSechage));
                console.log(temperatureSechageMin);
                console.log(temperatureSechageMax);
                if(sechage == true)
                {
                    if(temperature < temperatureSechageMin){
                        document.getElementById("ledRouge").style.background = "red";
                        document.getElementById("ledJaune").style.background = "white";
                        document.getElementById("ledVerte").style.background = "white";

                    }
                    if(temperature >= temperatureSechageMin && temperature <= temperatureSechageMax && compteurSechage <= parseFloat(tempsSechage) && sechage){
                        document.getElementById("ledJaune").style.background = "yellow";
                        document.getElementById("ledRouge").style.background = "white";
                        document.getElementById("ledVerte").style.background = "white";
                        compteurSechage = compteurSechage + 1;
                        console.log(compteurSechage);
                        document.getElementById("compteurSechage").innerText = compteurSechage;
                    }
                    if(temperature > temperatureSechageMax){
                        document.getElementById("ledRouge").style.background = "red";
                        document.getElementById("ledJaune").style.background = "white";
                        document.getElementById("ledVerte").style.background = "white";

                    }
                    if(compteurSechage == parseFloat(tempsSechage)){
                        sechage = false;
                        compteurSechage = 0;
                        document.getElementById("compteurSechage").innerText = compteurSechage;
                        document.getElementById("btnDemarrerFour").style.display = "block";
                        document.getElementById("btnStopFour").style.display = "none";
                        document.getElementById("ledRouge").style.background = "white";
                        document.getElementById("ledJaune").style.background = "white";
                        document.getElementById("ledVerte").style.background = "green";
                    }
                }
                else{
                    document.getElementById("ledRouge").style.background = "white";
                    document.getElementById("ledJaune").style.background = "white";
                    document.getElementById("ledVerte").style.background = "green";
                }
            }
        };
        xhttp.open("GET", "getTemperature", true);
        xhttp.send();
    },1000))();