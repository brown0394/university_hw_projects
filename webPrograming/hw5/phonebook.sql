-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1:3306
-- 생성 시간: 22-11-26 06:32
-- 서버 버전: 10.4.25-MariaDB
-- PHP 버전: 8.1.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- 데이터베이스: `phonebook`
--
CREATE DATABASE IF NOT EXISTS `phonebook` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
USE `phonebook`;

-- --------------------------------------------------------

--
-- 테이블 구조 `contacts`
--

CREATE TABLE `contacts` (
  `name` varchar(20) COLLATE utf8mb4_unicode_ci NOT NULL,
  `phone` varchar(20) COLLATE utf8mb4_unicode_ci NOT NULL,
  `email` varchar(20) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `memo` varchar(30) COLLATE utf8mb4_unicode_ci DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- 테이블의 덤프 데이터 `contacts`
--

INSERT INTO `contacts` (`name`, `phone`, `email`, `memo`) VALUES
('a', '111-1111-1111', NULL, NULL),
('a1', '111-1111-1111', 'hello@ha.met', '11'),
('a2', '111-1111-1111', NULL, NULL),
('a3', '111-1111-1111', NULL, 'meomeomeomeo'),
('aa', '111-1111-1111', 'hello@ha.met', 'a'),
('aaa', '111-1111-1111', NULL, NULL),
('김철수', '010-1234-1234', 'email@mail.com', NULL),
('월드컵', '010-7777-7777', 'email@mail.net', '우승'),
('철출', '010-1234-1234', NULL, NULL),
('테스트', '010-0000-0000', NULL, NULL),
('홍철', '010-4321-4321', NULL, NULL),
('황희찬', '010-5555-5555', NULL, '부상회복');

--
-- 덤프된 테이블의 인덱스
--

--
-- 테이블의 인덱스 `contacts`
--
ALTER TABLE `contacts`
  ADD PRIMARY KEY (`name`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
