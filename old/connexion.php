<?php
/*****************************************************************************/
//	Auteur:			Jérémie Cyr et Joséanne Aubut
//	Description:		Connexion à la base de données 
//	Date de creation:	Août 2021
//	But:			Connecter l'application à la base de données
/*****************************************************************************/
try
{
        $db = new PDO(  'mysql:host=10.172.80.62;
                        dbname=meublesdubeinc;
                        charset=utf8', 
                        'meublesdubeinc', 
                        'Patate123.'
                        );
        $db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
}
catch (Exception $e)
{
        die('Erreur : ' . $e->getMessage().' code erreur: '.$e->getCode());
}
?>