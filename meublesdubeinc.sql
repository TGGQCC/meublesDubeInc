-- phpMyAdmin SQL Dump
-- version 5.0.2
-- https://www.phpmyadmin.net/
--
-- Hôte : localhost:3306
-- Généré le : mar. 30 nov. 2021 à 22:37
-- Version du serveur :  8.0.20
-- Version de PHP : 7.4.14

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de données : `meublesdubeinc`
--
CREATE DATABASE IF NOT EXISTS `meublesdubeinc` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci;
USE `meublesdubeinc`;

-- --------------------------------------------------------

--
-- Structure de la table `bois`
--

CREATE TABLE `bois` (
  `id` int NOT NULL,
  `type` varchar(25) NOT NULL,
  `origine` varchar(50) NOT NULL,
  `sechage` int DEFAULT NULL,
  `temp_min` int DEFAULT NULL,
  `nom` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Déchargement des données de la table `bois`
--

INSERT INTO `bois` (`id`, `type`, `origine`, `sechage`, `temp_min`, `nom`) VALUES
(1, 'Dur', 'US', 20, 25, 'Érable'),
(2, 'Dur', 'Brazil', 45, 22, 'Acajou'),
(3, 'Mou', 'CAN', 15, 18, 'Épinette');

-- --------------------------------------------------------

--
-- Structure de la table `usager`
--

CREATE TABLE `usager` (
  `id` int NOT NULL,
  `usager` varchar(25) NOT NULL,
  `motDePasse` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Déchargement des données de la table `usager`
--

INSERT INTO `usager` (`id`, `usager`, `motDePasse`) VALUES
(1, 'Poney', '3d274b9f6e642eb73921f47df28991ff54987335a206da135349420701fb75a5c1ffb4ca9818048bb6e3b1f99e9d21d537505df7cd38f97cab306107ad052a6c');

--
-- Index pour les tables déchargées
--

--
-- Index pour la table `bois`
--
ALTER TABLE `bois`
  ADD PRIMARY KEY (`id`);

--
-- Index pour la table `usager`
--
ALTER TABLE `usager`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT pour les tables déchargées
--

--
-- AUTO_INCREMENT pour la table `bois`
--
ALTER TABLE `bois`
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT pour la table `usager`
--
ALTER TABLE `usager`
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
