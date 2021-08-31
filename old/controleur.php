<?php
/*****************************************************************************/
//	Auteur:			Jérémie Cyr et Joséanne Aubut
//	Description:		API
//	Date de creation:	Août 2021
//	But:			Exécuter des requêtes à la BD
/*****************************************************************************/
include('connexion.php');
include('mgr.php');
header("Access-Control-Allow-Origin: *");

    //Déclaration du manager
    $mgr = new mgr($db);


    //Appelle une fonction si elle est appelée dans l'url
    if(isset($_GET['getAllWood'])) {
        $mgr->getToutEssenceBois();
        }

    if(isset($_GET['getCaracteristicsOf'])) {
        $boisId = $_GET['id'];
        $mgr->getCaracteristicsBois($boisId);
        }

?>