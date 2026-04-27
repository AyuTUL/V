<?php
// api/admin.php — admin-only actions
require_once '../config.php';
requireAdmin();

header('Content-Type: application/json');
$action = $_POST['action'] ?? $_GET['action'] ?? '';

switch ($action) {

    case 'get_questions':
        $pdo = getDB();
        $stmt = $pdo->query("SELECT q.*, u.username as author FROM quiz_questions q 
                             LEFT JOIN users u ON u.id = q.created_by 
                             ORDER BY q.created_at DESC");
        jsonResponse(['success' => true, 'questions' => $stmt->fetchAll()]);
        break;

    case 'add_question':
        $q  = trim($_POST['question'] ?? '');
        $a  = trim($_POST['option_a'] ?? '');
        $b  = trim($_POST['option_b'] ?? '');
        $c  = trim($_POST['option_c'] ?? '');
        $d  = trim($_POST['option_d'] ?? '');
        $ans = strtolower(trim($_POST['correct_answer'] ?? ''));

        if (!$q || !$a || !$b || !$c || !$d || !in_array($ans, ['a','b','c','d'])) {
            jsonResponse(['success' => false, 'error' => 'All fields required and answer must be a/b/c/d.'], 400);
        }

        $pdo = getDB();
        $stmt = $pdo->prepare("INSERT INTO quiz_questions 
            (question, option_a, option_b, option_c, option_d, correct_answer, created_by)
            VALUES (?, ?, ?, ?, ?, ?, ?)");
        $stmt->execute([$q, $a, $b, $c, $d, $ans, $_SESSION['user_id']]);

        jsonResponse(['success' => true, 'id' => $pdo->lastInsertId(), 'message' => 'Question added.']);
        break;

    case 'delete_question':
        $id = intval($_POST['id'] ?? 0);
        if (!$id) jsonResponse(['success' => false, 'error' => 'Invalid ID.'], 400);

        $pdo = getDB();
        $stmt = $pdo->prepare("DELETE FROM quiz_questions WHERE id = ?");
        $stmt->execute([$id]);

        jsonResponse(['success' => true, 'message' => 'Question deleted.']);
        break;

    case 'update_question':
        $id  = intval($_POST['id'] ?? 0);
        $q   = trim($_POST['question'] ?? '');
        $a   = trim($_POST['option_a'] ?? '');
        $b   = trim($_POST['option_b'] ?? '');
        $c   = trim($_POST['option_c'] ?? '');
        $d   = trim($_POST['option_d'] ?? '');
        $ans = strtolower(trim($_POST['correct_answer'] ?? ''));

        if (!$id || !$q || !$a || !$b || !$c || !$d || !in_array($ans, ['a','b','c','d'])) {
            jsonResponse(['success' => false, 'error' => 'All fields required.'], 400);
        }

        $pdo = getDB();
        $stmt = $pdo->prepare("UPDATE quiz_questions SET 
            question=?, option_a=?, option_b=?, option_c=?, option_d=?, correct_answer=?
            WHERE id=?");
        $stmt->execute([$q, $a, $b, $c, $d, $ans, $id]);

        jsonResponse(['success' => true, 'message' => 'Question updated.']);
        break;

    case 'set_difficulty':
        $difficulty = $_POST['difficulty'] ?? '';
        if (!in_array($difficulty, ['easy', 'medium', 'hard'])) {
            jsonResponse(['success' => false, 'error' => 'Invalid difficulty.'], 400);
        }

        $pdo = getDB();
        $stmt = $pdo->prepare("INSERT INTO settings (setting_key, setting_value) VALUES ('goalie_difficulty', ?)
                               ON DUPLICATE KEY UPDATE setting_value = ?");
        $stmt->execute([$difficulty, $difficulty]);

        jsonResponse(['success' => true, 'message' => "Difficulty set to $difficulty."]);
        break;

    case 'get_scores':
        $pdo = getDB();
        $stmt = $pdo->query("
            SELECT gs.*, u.username 
            FROM game_sessions gs
            JOIN users u ON u.id = gs.user_id
            ORDER BY gs.played_at DESC
            LIMIT 100
        ");
        jsonResponse(['success' => true, 'scores' => $stmt->fetchAll()]);
        break;

    case 'get_stats':
        $pdo = getDB();
        $stats = [];

        $stmt = $pdo->query("SELECT COUNT(*) as c FROM users WHERE role='user'");
        $stats['total_users'] = $stmt->fetch()['c'];

        $stmt = $pdo->query("SELECT COUNT(*) as c FROM game_sessions");
        $stats['total_games'] = $stmt->fetch()['c'];

        $stmt = $pdo->query("SELECT COUNT(*) as c FROM quiz_questions");
        $stats['total_questions'] = $stmt->fetch()['c'];

        $stmt = $pdo->query("SELECT MAX(final_score) as c FROM game_sessions");
        $stats['highest_score'] = $stmt->fetch()['c'] ?? 0;

        $stats['goalie_difficulty'] = getSetting('goalie_difficulty', 'medium');

        jsonResponse(['success' => true, 'stats' => $stats]);
        break;

    default:
        jsonResponse(['error' => 'Unknown action.'], 400);
}
