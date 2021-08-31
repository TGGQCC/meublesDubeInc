<?php
/*****************************************************************************/
//	Auteur:				Jérémie Cyr et Joséanne Aubut
//	Description:		Définition du manager et des méthodes
//                      d'accès à la BD
//	Date de creation:	Août 2021
/*****************************************************************************/

/**
 * classe qui gère les essences de bois
 */
class mgr      // Définition de la classe
{
    private $db;            // Instance de PDO

    /**
     * constructeur de la classe mgr
     *
     * @param [PDO] $db
     */
    public function __construct($db)        // Permet de définir une instance PDO
    {
        $this->setdb($db);
    }

    /**
     * prend la variable privé et le met dans une variable publique
     *
     * @param PDO $db
     * @return void
     */
    public function setdb(PDO $db)
    {
        $this->db = $db;
    }

/**
     * Fonction qui va chercher toute la liste des essences de bois dans la BD
     *
     * @return void
     */
    function getToutEssenceBois()
    {
        try
        {
            $requeteGetToutEssenceBois = $this->db->prepare('SELECT id, nom FROM bois');
            $reponse = $requeteGetToutEssenceBois->execute();
            $tableauToutEssenceBois = $requeteGetToutEssenceBois->fetchAll(PDO::FETCH_ASSOC); //retourne un tableau indexé par le nom de la colonne
            return $tableauToutEssenceBois;
        }
        catch (Exception $e)
        {
            echo('Erreur : ' . $e->getMessage().' code erreur: '.$e->getCode());
        }

    }

/**
     * Fonction qui va chercher les infos sur une essence de bois spécifiée
     *
     * @return void
     */
    function getCaracteristicsBois($id)
    {
        try
        {
            $requeteGetEssenceBois = $this->db->prepare('SELECT * FROM bois WHERE id='.$id.'');
            $reponse = $requeteGetEssenceBois->execute();
            $tableauEssenceBois = $requeteGetEssenceBois->fetch(PDO::FETCH_ASSOC); //retourne un tableau indexé par le nom de la colonne
            return $tableauEssenceBois;
        }
        catch (Exception $e)
        {
            echo('Erreur : ' . $e->getMessage().' code erreur: '.$e->getCode());
        }

    }
}

?>