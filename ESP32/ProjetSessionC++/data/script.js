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

            //Refresh le contenu
            var siteHeader = document.getElementById('selectBois');
            siteHeader.style.display='none';
            siteHeader.offsetHeight; // no need to store this anywhere, the reference is enough
            siteHeader.style.display='block';

            }
    };
    xhttp.open("GET", "getAllWoodOptions", true);
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
                document.getElementById("sechage").innerText = ":" + listeBois[i]["sechage"] + " secondes";
                document.getElementById("temp_min").innerText = ":" + listeBois[i]["temp_min"] + " Celsius";
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
    xhttp.send();
}


    function postToESP_demarrerFour(){
        document.getElementById("btnDemarrerFour").style.display = "none";
        document.getElementById("btnStopFour").style.display = "block";

        var xhttp = new XMLHttpRequest();
        xhttp.open("POST", "postDemarrerFour", true);
        xhttp.send();
        }

    function postToESP_stopFour(){
        document.getElementById("btnDemarrerFour").style.display = "block";
        document.getElementById("btnStopFour").style.display = "none";

        var xhttp = new XMLHttpRequest();
        xhttp.open("POST", "postStopFour", true);
        xhttp.send();
        }


    
    (setInterval(function(){
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                console.log(this.responseText);
                document.getElementById("temperatureActuelle").innerText = this.responseText + " Celsius";
            }
        };
        xhttp.open("GET", "getTemperature", true);
        xhttp.send();
    },1000))();