<?php
// ============================================
// config.php Ã¢â‚¬â€ DB connection + session setup
// ============================================

define('DB_HOST', 'localhost');
define('DB_USER', 'root');       // change to your MySQL user
define('DB_PASS', '');           // change to your MySQL password
define('DB_NAME', 'penalty_game');

define('BASE_URL', 'http://localhost/penalty-game/'); // adjust if needed

function getDB(): PDO {
    static $pdo = null;
    if ($pdo === null) {
        try {
            $pdo = new PDO(
                "mysql:host=" . DB_HOST . ";dbname=" . DB_NAME . ";charset=utf8mb4",
                DB_USER,
                DB_PASS,
                [
                    PDO::ATTR_ERRMODE            => PDO::ERRMODE_EXCEPTION,
                    PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
                    PDO::ATTR_EMULATE_PREPARES   => false,
                ]
            );
            ensureDatabaseSchema($pdo);
        } catch (PDOException $e) {
            http_response_code(500);
            die(json_encode(['error' => 'Database connection failed: ' . $e->getMessage()]));
        }
    }
    return $pdo;
}

function ensureDatabaseSchema(PDO $pdo): void {
    static $checked = false;
    if ($checked) {
        return;
    }

    $stmt = $pdo->query("SHOW COLUMNS FROM game_sessions LIKE 'goals_conceded'");
    if (!$stmt->fetch()) {
        $pdo->exec("ALTER TABLE game_sessions ADD COLUMN goals_conceded INT DEFAULT 0 AFTER goals_saved");
    }

    $stmt = $pdo->query("SHOW COLUMNS FROM game_sessions LIKE 'rounds_played'");
    if ($stmt->fetch()) {
        $pdo->exec("ALTER TABLE game_sessions DROP COLUMN rounds_played");
    }

    $stmt = $pdo->query("SHOW COLUMNS FROM game_sessions LIKE 'final_score'");
    if ($stmt->fetch()) {
        $pdo->exec("ALTER TABLE game_sessions DROP COLUMN final_score");
    }

    $checked = true;
}

function startSession(): void {
    if (session_status() === PHP_SESSION_NONE) {
        session_start();
    }
}

function requireLogin(): void {
    startSession();
    if (empty($_SESSION['user_id'])) {
        header('Location: ' . BASE_URL . 'login.php');
        exit;
    }
}

function requireAdmin(): void {
    requireLogin();
    if ($_SESSION['role'] !== 'admin') {
        header('Location: ' . BASE_URL . 'game.php');
        exit;
    }
}

function jsonResponse(array $data, int $code = 200): void {
    http_response_code($code);
    header('Content-Type: application/json');
    echo json_encode($data);
    exit;
}

function getSetting(string $key, string $default = ''): string {
    $pdo = getDB();
    $stmt = $pdo->prepare("SELECT setting_value FROM settings WHERE setting_key = ?");
    $stmt->execute([$key]);
    $row = $stmt->fetch();
    return $row ? $row['setting_value'] : $default;
}
