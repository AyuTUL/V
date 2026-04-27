<?php
// api/game.php — quiz lifeline + score saving + settings
require_once '../config.php';
startSession();

header('Content-Type: application/json');

if (empty($_SESSION['user_id'])) {
    jsonResponse(['error' => 'Not authenticated.'], 401);
}

$action = $_POST['action'] ?? $_GET['action'] ?? '';

switch ($action) {

    case 'get_quiz':
        // Return a random quiz question (excluding recently seen ones)
        $pdo = getDB();
        $exclude = $_POST['exclude'] ?? '';
        $excludeIds = array_filter(array_map('intval', explode(',', $exclude)));

        if (!empty($excludeIds)) {
            $placeholders = implode(',', array_fill(0, count($excludeIds), '?'));
            $stmt = $pdo->prepare("SELECT id, question, option_a, option_b, option_c, option_d 
                                   FROM quiz_questions 
                                   WHERE id NOT IN ($placeholders) 
                                   ORDER BY RAND() LIMIT 1");
            $stmt->execute($excludeIds);
        } else {
            $stmt = $pdo->prepare("SELECT id, question, option_a, option_b, option_c, option_d 
                                   FROM quiz_questions ORDER BY RAND() LIMIT 1");
            $stmt->execute();
        }

        $question = $stmt->fetch();
        if (!$question) {
            // Fallback: get any question if all excluded
            $stmt = $pdo->prepare("SELECT id, question, option_a, option_b, option_c, option_d 
                                   FROM quiz_questions ORDER BY RAND() LIMIT 1");
            $stmt->execute();
            $question = $stmt->fetch();
        }

        if (!$question) {
            jsonResponse(['error' => 'No quiz questions available. Ask admin to add some.'], 404);
        }

        jsonResponse(['success' => true, 'question' => $question]);
        break;

    case 'check_answer':
        $questionId = intval($_POST['question_id'] ?? 0);
        $answer     = strtolower(trim($_POST['answer'] ?? ''));

        if (!in_array($answer, ['a','b','c','d'])) {
            jsonResponse(['success' => false, 'error' => 'Invalid answer option.'], 400);
        }

        $pdo = getDB();
        $stmt = $pdo->prepare("SELECT correct_answer FROM quiz_questions WHERE id = ?");
        $stmt->execute([$questionId]);
        $row = $stmt->fetch();

        if (!$row) {
            jsonResponse(['success' => false, 'error' => 'Question not found.'], 404);
        }

        $correct = ($row['correct_answer'] === $answer);
        jsonResponse(['success' => true, 'correct' => $correct, 'correct_answer' => $row['correct_answer']]);
        break;

    case 'save_score':
        $goals_scored  = intval($_POST['goals_scored'] ?? 0);
        $goals_saved   = intval($_POST['goals_saved'] ?? 0);
        $rounds_played = intval($_POST['rounds_played'] ?? 0);
        $lifelines     = intval($_POST['lifelines_used'] ?? 0);

        // Final score formula: goals + saves + bonus for unused lifelines
        $final_score = ($goals_scored * 10) + ($goals_saved * 8) + ((5 - min($lifelines, 5)) * 2);

        $pdo = getDB();
        $stmt = $pdo->prepare("INSERT INTO game_sessions 
            (user_id, goals_scored, goals_saved, rounds_played, lifelines_used, final_score)
            VALUES (?, ?, ?, ?, ?, ?)");
        $stmt->execute([
            $_SESSION['user_id'],
            $goals_scored,
            $goals_saved,
            $rounds_played,
            $lifelines,
            $final_score
        ]);

        jsonResponse(['success' => true, 'final_score' => $final_score]);
        break;

    case 'get_settings':
        $difficulty = getSetting('goalie_difficulty', 'medium');
        jsonResponse(['success' => true, 'goalie_difficulty' => $difficulty]);
        break;

    case 'get_leaderboard':
        $pdo = getDB();
        $stmt = $pdo->prepare("
            SELECT u.username, MAX(gs.final_score) as best_score,
                   COUNT(gs.id) as games_played,
                   SUM(gs.goals_scored) as total_goals,
                   MAX(gs.played_at) as last_played
            FROM game_sessions gs
            JOIN users u ON u.id = gs.user_id
            GROUP BY gs.user_id, u.username
            ORDER BY best_score DESC
            LIMIT 20
        ");
        $stmt->execute();
        jsonResponse(['success' => true, 'leaderboard' => $stmt->fetchAll()]);
        break;

    default:
        jsonResponse(['error' => 'Unknown action.'], 400);
}
