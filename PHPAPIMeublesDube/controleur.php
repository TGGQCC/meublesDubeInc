<?php
/*****************************************************************************/
//	Auteur:			Jérémie Cyr
//	Description:		API
//	Date de creation:	Avril 2020
//	But:			Exécuter des requêtes à la BD
/*****************************************************************************/
include('connexion.php');
include('mgr.php');

 
    $mgr = new mgr($db);


    if(isset($_GET['getToutEssenceBois'])) {
        $mgr->getToutEssenceBois();
        }

    if(isset($_GET['getEssenceBois'])) {
        $boisId = $_GET['id'];
        $mgr->getEssenceBois($boisId);
        }
        
?>