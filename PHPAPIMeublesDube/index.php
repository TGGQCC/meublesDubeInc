<!DOCTYPE html>
    <html lang="en">
    <head>
        <title>Doc API</title>
        <!-- Required meta tags -->
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

        <!-- Bootstrap CSS -->
        <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
        <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js" integrity="sha384-MrcW6ZMFYlzcLA8Nl+NtUVF0sA7MsXsP1UyJoMp4YLEuNSfAP+JcXn/tWtIaxVXM" crossorigin="anonymous"></script>
    </head>
    <body>

      <!-- Tabs or Pills can be used in a card with the help of .nav-{tabs|pills} and .card-header-{tabs|pills} classes -->
      <div class="card">
        <div class="card-header">
          <ul class="nav nav-tabs card-header-tabs" id="myTab" role="tablist">
            <li class="nav-item" role="presentation">
              <a style="color:green" class="nav-link active" id="get-tab" data-bs-toggle="tab" href="#get" role="tab" aria-controls="get" aria-selected="true">Appels GET</a>
            </li>
            <li class="nav-item" role="presentation">
              <a style="color:purple" class="nav-link" id="post-tab" data-bs-toggle="tab" href="#post" role="tab" aria-controls="post" aria-selected="false">Appels POST</a>
            </li>
            <li class="nav-item" role="presentation">
              <a class="nav-link" id="apropos-tab" data-bs-toggle="tab" href="#apropos" role="tab" aria-controls="apropos" aria-selected="false">À propos</a>
            </li>
          </ul>
        </div>
        <div class="card-body">
          <div class="tab-content" id="myTabContent">
            <div class="tab-pane fade show active" id="get" role="tabpanel" aria-labelledby="get-tab">


            <p>
              <button style="background-color:green; border:green; width:200px" class="btn btn-primary" type="button" data-bs-toggle="collapse" data-bs-target="#collapseWidth1" aria-expanded="false" aria-controls="collapseWidthExample">
                getAllWood
              </button>
            </p>
            <div style="margin-bottom: 15px;" class="collapse collapse-horizontal" id="collapseWidth1">
              <div class="card card-body" style="width: 100%; color: green;">
                <ul>
                  <li><strong>Requête : </strong>
                  <span style="text-decoration:underline">http://10.172.80.27/php/meublesDubeInc/PHPAPIMeublesDube/api/getAllWoods</span>
                  <p style="margin-left:75px">Il faut préciser l'adresse IP qui est celle du serveur hébergeant l'API et ensuite, préciser le chemin vers l'API qui répond à l'appel GET. À la fin, ajouter un ? pour préciser une variable en GET (getToutEssenceBois dans ce cas) qui demandera à l'API d'exécuter une fonction (getToutEssenceBois() dans ce cas) et le résultat sera renvoyer en JSON</p>
                  </li><br>
                    <li><strong>Réponse : </strong>
                    <span style="text-decoration:underline">Format JSON</span>
                    <p style="margin-left:75px">Suite à l'appel Get, l'API renvoit la réponse en JSON contenant les id et les noms des bois. Voici à quoi la réponse ressemble pour cette requête :</p>
                      <div style="width:400px; margin-left:75px" class="card">
                        <img style="width:50%; height:50%" src="images/ReponseGetAllWood.PNG" class="card-img" alt="card-img-overlay">
                        <div class="card-img-overlay">
                        </div>
                      </div>
                    </li>
                </ul>
                <P></p>
              </div>
            </div>

            <p>
              <button style="background-color:green; border:green; width:200px" class="btn btn-primary" type="button" data-bs-toggle="collapse" data-bs-target="#collapseWidth2" aria-expanded="false" aria-controls="collapseWidthExample">
                getCaracteristicsOf
              </button>
            </p>
            <div style="margin-bottom: 15px;" class="collapse collapse-horizontal" id="collapseWidth2">
              <div class="card card-body" style="width: 100%; color: green;">
                <ul>
                    <li><strong>Requête : </strong>
                      <span style="text-decoration:underline">http://10.172.80.27/php/meublesDubeInc/PHPAPIMeublesDube/controleur.php?getCaracteristicsOf&id=1</span>
                      <p style="margin-left:75px">Il faut préciser l'adresse IP qui est celle du serveur hébergeant l'API et ensuite, préciser le chemin vers l'API qui répond à l'appel GET. À la fin, ajouter un ? pour préciser une variable en GET (getToutEssenceBois dans ce cas) qui demandera à l'API d'exécuter une fonction (getToutEssenceBois() dans ce cas) et ajouter une deuxième variable (id) qui spécifie le id du type de bois dont ont veux récupérer les informations et le résultat sera renvoyer en JSON</p>
                    </li><br>
                    <li><strong>Réponse : </strong>
                    <span style="text-decoration:underline">Format JSON</span>
                    <p style="margin-left:75px">Il faut préciser l'adresse IP qui est celle du serveur hébergeant l'API et ensuite, préciser le chemin vers l'API qui répond à l'appel GET. À la fin, ajouter un ? pour préciser une variable en GET (getToutEssenceBois dans ce cas) qui demandera à l'API d'exécuter une fonction (getToutEssenceBois() dans ce cas) et ajouter une deuxième variable (id) qui spécifie le id du type de bois dont ont veux récupérer les informations et le résultat sera renvoyer en JSON</p>

                    </li>
                  </ul>              
                </div>
            </div>


            </div>
            <div class="tab-pane fade" id="post" role="tabpanel" aria-labelledby="post-tab"><P style="color: purple">Il n'y a aucun appel POST disponible pour le moment</p></div>
            <div class="tab-pane fade" id="apropos" role="tabpanel" aria-labelledby="apropos-tab">Lorem ipsum dolor sit amet consectetur adipisicing elit. Iure, asperiores provident ea eaque quis omnis adipisci in exercitationem necessitatibus dolorem.</div>
          </div>
        </div>
      </div>

    </body>
    </html>