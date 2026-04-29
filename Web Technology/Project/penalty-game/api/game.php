<?php
require_once '../config.php';
startSession();
header('Content-Type: application/json');

if (empty($_SESSION['user_id'])) jsonResponse(['error' => 'Not authenticated.'], 401);

$action = $_POST['action'] ?? $_GET['action'] ?? '';

switch ($action) {

    case 'get_quiz':
        $pdo     = getDB();
        $exclude = $_POST['exclude'] ?? '';
        $excludeIds = array_filter(array_map('intval', explode(',', $exclude)));

        if (!empty($excludeIds)) {
            $ph   = implode(',', array_fill(0, count($excludeIds), '?'));
            $stmt = $pdo->prepare("SELECT id, question, option_a, option_b, option_c, option_d
                                   FROM quiz_questions WHERE id NOT IN ($ph) ORDER BY RAND() LIMIT 1");
            $stmt->execute($excludeIds);
        } else {
            $stmt = $pdo->prepare("SELECT id, question, option_a, option_b, option_c, option_d
                                   FROM quiz_questions ORDER BY RAND() LIMIT 1");
            $stmt->execute();
        }

        $question = $stmt->fetch();
        if (!$question) {
            // fallback: pick any question if all seen
            $stmt = $pdo->prepare("SELECT id, question, option_a, option_b, option_c, option_d
                                   FROM quiz_questions ORDER BY RAND() LIMIT 1");
            $stmt->execute();
            $question = $stmt->fetch();
        }
        if (!$question) jsonResponse(['error' => 'No quiz questions available. Ask admin to add some.'], 404);
        jsonResponse(['success' => true, 'question' => $question]);
        break;

    case 'check_answer':
        $questionId = intval($_POST['question_id'] ?? 0);
        $answer     = strtolower(trim($_POST['answer'] ?? ''));
        if (!in_array($answer, ['a','b','c','d'])) jsonResponse(['success' => false, 'error' => 'Invalid answer.'], 400);
        $pdo  = getDB();
        $stmt = $pdo->prepare("SELECT correct_answer FROM quiz_questions WHERE id = ?");
        $stmt->execute([$questionId]);
        $row  = $stmt->fetch();
        if (!$row) jsonResponse(['success' => false, 'error' => 'Question not found.'], 404);
        jsonResponse(['success' => true, 'correct' => ($row['correct_answer'] === $answer), 'correct_answer' => $row['correct_answer']]);
        break;

    case 'save_score':
        $goals_scored   = intval($_POST['goals_scored']   ?? 0);
        $goals_saved    = intval($_POST['goals_saved']    ?? 0);
        $goals_conceded = intval($_POST['goals_conceded'] ?? 0);
        $lifelines      = intval($_POST['lifelines_used'] ?? 0);
        $pdo  = getDB();
        $stmt = $pdo->prepare("INSERT INTO game_sessions
            (user_id, goals_scored, goals_saved, goals_conceded, lifelines_used)
            VALUES (?, ?, ?, ?, ?)");
        $stmt->execute([
            $_SESSION['user_id'],
            $goals_scored,
            $goals_saved,
            $goals_conceded,
            $lifelines
        ]);
        jsonResponse(['success' => true]);
        break;

    case 'get_settings':
        jsonResponse(['success' => true, 'goalie_difficulty' => getSetting('goalie_difficulty', 'medium')]);
        break;

    case 'get_leaderboard':
        $pdo  = getDB();
        $stmt = $pdo->prepare("
            SELECT u.username,
                   COUNT(gs.id)              AS games_played,
                   SUM(gs.goals_scored)      AS total_goals,
                   SUM(gs.goals_saved)       AS total_saves,
                   SUM(gs.goals_conceded)    AS total_conceded,
                   SUM(gs.lifelines_used)    AS total_lifelines,
                   MAX(gs.played_at)         AS last_played
            FROM game_sessions gs
            JOIN users u ON u.id = gs.user_id
            GROUP BY gs.user_id, u.username
            ORDER BY total_goals DESC, total_saves DESC
            LIMIT 30
        ");
        $stmt->execute();
        jsonResponse(['success' => true, 'leaderboard' => $stmt->fetchAll()]);
        break;

    default:
        jsonResponse(['error' => 'Unknown action.'], 400);
}
