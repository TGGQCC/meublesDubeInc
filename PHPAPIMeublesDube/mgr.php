<?php
/*****************************************************************************/
//	Auteur:				Jérémie Cyr
//	Description:		Définition du manager et des méthodes
//                      d'accès à la BD
//	Date de creation:	Août 2021
/*****************************************************************************/

/**
 * classe qui gère les jeux vidéos
 */
class mgr      // Définition de la classe
{
    private $db;            // Instance de PDO

    /**
     * constructeur de la classe mgrJeuVideo
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
     * @param jeuVideo $jeuVideo
     * @return void
     */
    function getToutEssenceBois()
    {
        try
        {
            $requeteGetJeuVideo = $this->db->prepare('SELECT * FROM bois');
            $reponse = $requeteGetJeuVideo->execute();
            $tableauJeuVideo = $requeteGetJeuVideo->fetch(PDO::FETCH_ASSOC); //retourne un tableau indexé par le nom de la colonne
            var_dump($tableauJeuVideo);
            return $tableauJeuVideo;
        }
        catch (Exception $e)
        {
            echo('Erreur : ' . $e->getMessage().' code erreur: '.$e->getCode());
        }

    }

/**
     * Fonction qui va chercher les infos sur une essence de bois spécifiée
     *
     * @param jeuVideo $jeuVideo
     * @return void
     */
    function getEssenceBois()
    {
        try
        {
            $requeteGetToutEssenceBois = $this->db->prepare('SELECT * FROM bois');
            $tableToutEssenceBois = $requeteGetToutEssenceBois->execute();
            var_dump($tableToutEssenceBois);
            return $tableToutEssenceBois;
        }
        catch (Exception $e)
        {
            echo('Erreur : ' . $e->getMessage().' code erreur: '.$e->getCode());
        }

    }
}

?>