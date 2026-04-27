-- ============================================
-- PENALTY SHOOTOUT + QUIZ SYSTEM
-- Database Schema
-- ============================================

CREATE DATABASE IF NOT EXISTS penalty_game CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
USE penalty_game;

-- Users table
CREATE TABLE IF NOT EXISTS users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(50) UNIQUE NOT NULL,
    password_hash VARCHAR(255) NOT NULL,
    role ENUM('user','admin') DEFAULT 'user',
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Game sessions
CREATE TABLE IF NOT EXISTS game_sessions (
    id INT AUTO_INCREMENT PRIMARY KEY,
    user_id INT NOT NULL,
    goals_scored INT DEFAULT 0,
    goals_saved INT DEFAULT 0,
    rounds_played INT DEFAULT 0,
    lifelines_used INT DEFAULT 0,
    final_score INT DEFAULT 0,
    played_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE
);

-- Quiz questions
CREATE TABLE IF NOT EXISTS quiz_questions (
    id INT AUTO_INCREMENT PRIMARY KEY,
    question TEXT NOT NULL,
    option_a VARCHAR(255) NOT NULL,
    option_b VARCHAR(255) NOT NULL,
    option_c VARCHAR(255) NOT NULL,
    option_d VARCHAR(255) NOT NULL,
    correct_answer ENUM('a','b','c','d') NOT NULL,
    created_by INT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (created_by) REFERENCES users(id) ON DELETE SET NULL
);

-- Goalie difficulty settings
CREATE TABLE IF NOT EXISTS settings (
    id INT AUTO_INCREMENT PRIMARY KEY,
    setting_key VARCHAR(50) UNIQUE NOT NULL,
    setting_value VARCHAR(255) NOT NULL,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);

-- Seed default settings
INSERT INTO settings (setting_key, setting_value) VALUES
('goalie_difficulty', 'medium')
ON DUPLICATE KEY UPDATE setting_value = setting_value;

-- Seed admin account (password: admin123)
INSERT INTO users (username, password_hash, role) VALUES
('admin', '$2y$10$92IXUNpkjO0rOQ5byMi.Ye4oKoEa3Ro9llC/.og/at2.uheWG/igi', 'admin')
ON DUPLICATE KEY UPDATE username = username;

-- Seed sample quiz questions
INSERT INTO quiz_questions (question, option_a, option_b, option_c, option_d, correct_answer) VALUES
('How many players are on a football team on the field?', '9', '10', '11', '12', 'c'),
('Which country won the 2022 FIFA World Cup?', 'Brazil', 'France', 'Argentina', 'Germany', 'c'),
('How long is a standard football match?', '80 minutes', '90 minutes', '100 minutes', '120 minutes', 'b'),
('What is the diameter of a standard goal post?', '7.32 meters', '7.92 meters', '8.32 meters', '6.72 meters', 'a'),
('Who holds the record for most World Cup goals?', 'Pelé', 'Miroslav Klose', 'Ronaldo', 'Gerd Müller', 'b'),
('Which player is known as "El Pulgarcito del fútbol"?', 'Maradona', 'Messi', 'Ronaldo', 'Zidane', 'a'),
('What year was FIFA founded?', '1904', '1910', '1920', '1930', 'a'),
('How many minutes in each half of football?', '40', '45', '50', '35', 'b'),
('A penalty kick is taken from how many yards?', '10', '12', '15', '18', 'b'),
('Which trophy is awarded to the best player at the World Cup?', 'Golden Boot', 'Golden Ball', 'Golden Glove', 'Silver Ball', 'b');
