const express = require('express');
const bodyParser = require('body-parser');
const app = express();
const port = process.env.PORT || 3000;
const routes = require('./routes/routes');

app.use(bodyParser.json());
app.use(
  bodyParser.urlencoded({
    extended: true,
  })
);

app.use(function(req, res, next) {
  res.header("Access-Control-Allow-Origin", "*");
  res.header("Access-Control-Allow-Credentials", "true");
  res.header("Access-Control-Allow-Headers", "Origin,Content-Type, Authorization, x-id, Content-Length, X-Requested-With");
  res.header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
  next();
});

app.get('/', (req, res) => {
  res.send(html)
});


app.use('/api', routes);

/* Error handler middleware */
app.use((err, req, res, next) => {
  const statusCode = err.statusCode || 500;
  console.error(err.message, err.stack);
  res.status(statusCode).json({'message': err.message});

  return;
});

app.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`)
});

const html  = '<!DOCTYPE html>'+
                '<html lang="en">'+
                '<head>'+
                    '<title>Doc API</title>'+
                    '<meta charset="utf-8">'+
                    '<meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">'+
                    '<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">'+
                    '<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js" integrity="sha384-MrcW6ZMFYlzcLA8Nl+NtUVF0sA7MsXsP1UyJoMp4YLEuNSfAP+JcXn/tWtIaxVXM" crossorigin="anonymous"></script>'+
                '</head>'+
                '<body>'+
                  '<div class="card">'+
                    '<div class="card-header">'+
                      '<ul class="nav nav-tabs card-header-tabs" id="myTab" role="tablist">'+
                        '<li class="nav-item" role="presentation">'+
                          '<a style="color:green" class="nav-link active" id="get-tab" data-bs-toggle="tab" href="#get" role="tab" aria-controls="get" aria-selected="true">Appels GET</a>'+
                        '</li>'+
                        '<li class="nav-item" role="presentation">'+
                          '<a style="color:purple" class="nav-link" id="post-tab" data-bs-toggle="tab" href="#post" role="tab" aria-controls="post" aria-selected="false">Appels POST</a>'+
                        '</li>'+
                        '<li class="nav-item" role="presentation">'+
                          '<a class="nav-link" id="apropos-tab" data-bs-toggle="tab" href="#apropos" role="tab" aria-controls="apropos" aria-selected="false">À propos</a>'+
                        '</li>'+
                      '</ul>'+
                    '</div>'+
                    '<div class="card-body">'+
                      '<div class="tab-content" id="myTabContent">'+
                        '<div class="tab-pane fade show active" id="get" role="tabpanel" aria-labelledby="get-tab">'+
                        '<p>'+
                          '<button style="background-color:green; border:green; width:200px" class="btn btn-primary" type="button" data-bs-toggle="collapse" data-bs-target="#collapseWidth1" aria-expanded="false" aria-controls="collapseWidthExample">getAllWood</button>'+
                        '</p>'+
                        '<div style="margin-bottom: 15px;" class="collapse collapse-horizontal" id="collapseWidth1">'+
                          '<div class="card card-body" style="width: 100%; color: green;">'+
                            '<ul>'+
                              '<li><strong>Requête : </strong>'+
                              '<span style="text-decoration:underline">http://localhost:3000/api/getAllWoods</span>'+
                              '<p style="margin-left:75px">Il faut préciser l\'adresse IP qui est celle du serveur hébergeant l\'API, dans notre cas, localhost, et ensuite, préciser le chemin vers l\'API qui répond à l\'appel GET. À la fin, préciser le nom de la fonction et le résultat sera renvoyer en JSON</p>'+
                              '</li><br>'+
                                '<li><strong>Réponse : </strong>'+
                                '<span style="text-decoration:underline">Format JSON</span>'+
                                '<p style="margin-left:75px">Suite à l\'appel Get, l\'API renvoit la réponse en JSON contenant les id et les noms des bois. Voici à quoi la réponse ressemble pour cette requête :</p>'+
                                '<div>'+
                                  '{{"id":1,"nom":"Érable"},{"id":2,"nom":"Acajou"},{"id":3,"nom":"Épinette"}}'+
                                '</div>'+
                                '</li>'+
                            '</ul>'+
                          '</div>'+
                        '</div>'+
                        '<p>'+
                          '<button style="background-color:green; border:green; width:200px" class="btn btn-primary" type="button" data-bs-toggle="collapse" data-bs-target="#collapseWidth2" aria-expanded="false" aria-controls="collapseWidthExample">getCaracteristicsOf</button>'+
                        '</p>'+
                        '<div style="margin-bottom: 15px;" class="collapse collapse-horizontal" id="collapseWidth2">'+
                          '<div class="card card-body" style="width: 100%; color: green;">'+
                            '<ul>'+
                                '<li><strong>Requête : </strong>'+
                                  '<span style="text-decoration:underline">http://localhost:3000/api/getCaracterisiticsOf/1</span>'+
                                  '<p style="margin-left:75px">Il faut préciser l\'adresse IP qui est celle du serveur hébergeant l\'API, dans notre cas, localhost, et ensuite, préciser le chemin vers l\'API qui répond à l\'appel GET. À la fin, préciser le nom de la fonction ainsi que l\'id du bois dont vous voulez les caractéristiques et le résultat sera renvoyer en JSON</p>'+
                                '</li><br>'+
                                '<li><strong>Réponse : </strong>'+
                                '<span style="text-decoration:underline">Format JSON</span>'+
                                '<p style="margin-left:75px">Suite à l\'appel Get, l\'API renvoit la réponse en JSON contenant toutes les informations du bois. Voici à quoi la réponse ressemble pour cette requête :</p>'+
                                '<div>'+
                                    '{{"id": 1,"type": "Dur","origine": "US","sechage": 20,"temp_min": 25,"nom": "Érable"}}'+
                                '</div>'+
                                '</li>'+
                              '</ul>'+              
                            '</div>'+
                        '</div>'+
                        '<p>'+
                          '<button style="background-color:green; border:green; width:200px" class="btn btn-primary" type="button" data-bs-toggle="collapse" data-bs-target="#collapseWidth3" aria-expanded="false" aria-controls="collapseWidthExample">getCaracteristics</button>'+
                        '</p>'+
                        '<div style="margin-bottom: 15px;" class="collapse collapse-horizontal" id="collapseWidth3">'+
                          '<div class="card card-body" style="width: 100%; color: green;">'+
                            '<ul>'+
                                '<li><strong>Requête : </strong>'+
                                  '<span style="text-decoration:underline">http://localhost:3000/api/getCaracterisitics/Érable</span>'+
                                  '<p style="margin-left:75px">Il faut préciser l\'adresse IP qui est celle du serveur hébergeant l\'API, dans notre cas, localhost, et ensuite, préciser le chemin vers l\'API qui répond à l\'appel GET. À la fin, préciser le nom de la fonction ainsi que le nom du bois dont vous voulez les caractéristiques et le résultat sera renvoyer en JSON</p>'+
                                '</li><br>'+
                                '<li><strong>Réponse : </strong>'+
                                '<span style="text-decoration:underline">Format JSON</span>'+
                                '<p style="margin-left:75px">Suite à l\'appel Get, l\'API renvoit la réponse en JSON contenant toutes les informations du bois. Voici à quoi la réponse ressemble pour cette requête :</p>'+
                                '<div>'+
                                    '{{"id": 1,"type": "Dur","origine": "US","sechage": 20,"temp_min": 25,"nom": "Érable"}}'+
                                '</div>'+
                                '</li>'+
                              '</ul>'+              
                            '</div>'+
                        '</div>'+
                        '</div>'+
                        '<div class="tab-pane fade" id="post" role="tabpanel" aria-labelledby="post-tab">'+
                        '<p>'+
                          '<button style="background-color:purple; border:purple; width:200px" class="btn btn-primary" type="button" data-bs-toggle="collapse" data-bs-target="#collapseWidth4" aria-expanded="false" aria-controls="collapseWidthExample">login</button>'+
                        '</p>'+
                        '<div style="margin-bottom: 15px;" class="collapse collapse-horizontal" id="collapseWidth4">'+
                          '<div class="card card-body" style="width: 100%; color: purple;">'+
                            '<ul>'+
                                '<li><strong>Requête : </strong>'+
                                  '<span style="text-decoration:underline">http://localhost:3000/api/login</span>'+
                                  '<p style="margin-left:75px">Il faut préciser l\'adresse IP qui est celle du serveur hébergeant l\'API, dans notre cas, localhost, et ensuite, préciser le chemin vers l\'API qui répond à l\'appel POST. Dans le corps de la requête, le nom d\'usager et le mot de passe doivent être envoyés en JSON (EX: {"user":"patate","password":"123"}) et le token sera renvoyé en JSON.</p>'+
                                '</li><br>'+
                                '<li><strong>Réponse : </strong>'+
                                '<span style="text-decoration:underline">Format JSON</span>'+
                                '<p style="margin-left:75px">Suite à l\'appel POST, l\'API renvoit la réponse en JSON du token. Voici à quoi la réponse ressemble pour cette requête :</p>'+
                                '<div>'+
                                    '{"token": "eyJhbGciOiJIUzI1NiIsInR5sas6IkpXVCJ9.easpYXQiOjE2Mzc2MTE3MjR9.OiR1CNzLoXpToassdYGOKyGtveYDt5FGj6JfdssvJfc"}'+
                                '</div>'+
                                '</li>'+
                              '</ul>'+              
                            '</div>'+
                        '</div>'+
                        '</div>'+
                        '<div class="tab-pane fade" id="apropos" role="tabpanel" aria-labelledby="apropos-tab">Lorem ipsum dolor sit amet consectetur adipisicing elit. Iure, asperiores provident ea eaque quis omnis adipisci in exercitationem necessitatibus dolorem.</div>'+
                      '</div>'+
                    '</div>'+
                  '</div>'+
                '</body>'+
                '</html>';