-- phpMyAdmin SQL Dump
-- version 4.9.5deb2
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: Feb 23, 2021 at 02:18 PM
-- Server version: 8.0.22-0ubuntu0.20.04.3
-- PHP Version: 7.4.3

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `Fast-Food`
--

-- --------------------------------------------------------

--
-- Table structure for table `COMMANDE`
--

CREATE TABLE `COMMANDE` (
  `id` int NOT NULL,
  `prix` int NOT NULL,
  `validation` tinyint(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dumping data for table `COMMANDE`
--

INSERT INTO `COMMANDE` (`id`, `prix`, `validation`) VALUES
(1, 10, 0);

-- --------------------------------------------------------

--
-- Table structure for table `PRODUIT`
--

CREATE TABLE `PRODUIT` (
  `id` int NOT NULL,
  `nom` varchar(255) NOT NULL,
  `prix` int NOT NULL,
  `description` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dumping data for table `PRODUIT`
--

INSERT INTO `PRODUIT` (`id`, `nom`, `prix`, `description`) VALUES
(1, 'burger de folie', 10, 'C\'est un burger qui vous feras montez au 7 ème siècle'),
(2, 'boisson', 3, 'Coca cola'),
(14, 'potatos', 2, 'Description');

-- --------------------------------------------------------

--
-- Table structure for table `QUANTITE`
--

CREATE TABLE `QUANTITE` (
  `id` int NOT NULL,
  `idproduit` int NOT NULL,
  `idcommande` int NOT NULL,
  `nombre` int NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dumping data for table `QUANTITE`
--

INSERT INTO `QUANTITE` (`id`, `idproduit`, `idcommande`, `nombre`) VALUES
(1, 1, 1, 1);

-- --------------------------------------------------------

--
-- Table structure for table `REDUCTION`
--

CREATE TABLE `REDUCTION` (
  `id` int NOT NULL,
  `code` char(6) NOT NULL,
  `valeur` int NOT NULL,
  `debut` date NOT NULL,
  `fin` date NOT NULL,
  `iduser` int NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Table structure for table `TYPE`
--

CREATE TABLE `TYPE` (
  `Id` int NOT NULL,
  `fonction` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dumping data for table `TYPE`
--

INSERT INTO `TYPE` (`Id`, `fonction`) VALUES
(1, 'Administrateur'),
(2, 'Client');

-- --------------------------------------------------------

--
-- Table structure for table `USER`
--

CREATE TABLE `USER` (
  `id` int NOT NULL,
  `identifiant` varchar(255) NOT NULL,
  `nom` varchar(255) NOT NULL,
  `prenom` varchar(255) NOT NULL,
  `code` int NOT NULL,
  `type` int NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dumping data for table `USER`
--

INSERT INTO `USER` (`id`, `identifiant`, `nom`, `prenom`, `code`, `type`) VALUES
(1, 'aristide1', 'Fumo', 'Aristide', 518318, 2);

-- --------------------------------------------------------

--
-- Table structure for table `VALIDREDUCTION`
--

CREATE TABLE `VALIDREDUCTION` (
  `id` int NOT NULL,
  `idcommande` int NOT NULL,
  `iduser` int NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `COMMANDE`
--
ALTER TABLE `COMMANDE`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `PRODUIT`
--
ALTER TABLE `PRODUIT`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `QUANTITE`
--
ALTER TABLE `QUANTITE`
  ADD PRIMARY KEY (`id`),
  ADD KEY `idproduit` (`idproduit`),
  ADD KEY `idcommande` (`idcommande`);

--
-- Indexes for table `REDUCTION`
--
ALTER TABLE `REDUCTION`
  ADD PRIMARY KEY (`id`),
  ADD KEY `iduser` (`iduser`);

--
-- Indexes for table `TYPE`
--
ALTER TABLE `TYPE`
  ADD PRIMARY KEY (`Id`);

--
-- Indexes for table `USER`
--
ALTER TABLE `USER`
  ADD PRIMARY KEY (`id`),
  ADD KEY `type` (`type`);

--
-- Indexes for table `VALIDREDUCTION`
--
ALTER TABLE `VALIDREDUCTION`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `COMMANDE`
--
ALTER TABLE `COMMANDE`
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `PRODUIT`
--
ALTER TABLE `PRODUIT`
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=15;

--
-- AUTO_INCREMENT for table `REDUCTION`
--
ALTER TABLE `REDUCTION`
  MODIFY `id` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `TYPE`
--
ALTER TABLE `TYPE`
  MODIFY `Id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `USER`
--
ALTER TABLE `USER`
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `VALIDREDUCTION`
--
ALTER TABLE `VALIDREDUCTION`
  MODIFY `id` int NOT NULL AUTO_INCREMENT;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `QUANTITE`
--
ALTER TABLE `QUANTITE`
  ADD CONSTRAINT `QUANTITE_ibfk_1` FOREIGN KEY (`idproduit`) REFERENCES `PRODUIT` (`id`),
  ADD CONSTRAINT `QUANTITE_ibfk_2` FOREIGN KEY (`idcommande`) REFERENCES `COMMANDE` (`id`);

--
-- Constraints for table `REDUCTION`
--
ALTER TABLE `REDUCTION`
  ADD CONSTRAINT `REDUCTION_ibfk_1` FOREIGN KEY (`iduser`) REFERENCES `USER` (`id`);

--
-- Constraints for table `USER`
--
ALTER TABLE `USER`
  ADD CONSTRAINT `USER_ibfk_1` FOREIGN KEY (`type`) REFERENCES `TYPE` (`Id`) ON DELETE RESTRICT ON UPDATE RESTRICT;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
