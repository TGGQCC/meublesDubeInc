<?php
/*****************************************************************************/
//	Auteur:			Jérémie Cyr
//	Description:		API
//	Date de creation:	Avril 2020
//	But:			Exécuter des requêtes à la BD
/*****************************************************************************/
include('connexion.php');
include('test.php');

 
    $mgr = new mgr($db);


    if(isset($_GET['getToutEssenceBois'])) {
        $mgr->getToutEssenceBois();
        }

        
?>