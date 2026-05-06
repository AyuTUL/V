<?php
require_once '../config.php';
startSession();
header('Content-Type: application/json');
$action = $_POST['action'] ?? $_GET['action'] ?? '';

switch ($action) {

    case 'login':
        $username     = trim($_POST['username'] ?? '');
        $password     = $_POST['password'] ?? '';
        $expectedRole = $_POST['expected_role'] ?? 'user';

        if (!$username || !$password)
            jsonResponse(['success' => false, 'error' => 'Username and password required.'], 400);

        $pdo  = getDB();
        $stmt = $pdo->prepare("SELECT id, username, password_hash, role FROM users WHERE username = ?");
        $stmt->execute([$username]);
        $user = $stmt->fetch();

        if (!$user || !password_verify($password, $user['password_hash']))
            jsonResponse(['success' => false, 'error' => 'Invalid username or password.'], 401);

        // Role mismatch
        if ($user['role'] !== $expectedRole) {
            $msg = $expectedRole === 'admin'
                ? 'This account does not have admin privileges.'
                : 'Please select "Admin" to log in as admin.';
            jsonResponse(['success' => false, 'error' => $msg], 403);
        }

        $_SESSION['user_id']  = $user['id'];
        $_SESSION['username'] = $user['username'];
        $_SESSION['role']     = $user['role'];

        $redirect = $user['role'] === 'admin' ? 'admin/index.php' : 'game.php';
        jsonResponse(['success' => true, 'redirect' => BASE_URL . $redirect]);
        break;

    case 'register':
        $username = trim($_POST['username'] ?? '');
        $password = $_POST['password'] ?? '';

        if (strlen($username) < 3 || strlen($username) > 50)
            jsonResponse(['success' => false, 'error' => 'Username must be 3Ã¢â‚¬â€œ50 characters.'], 400);
        if (strlen($password) < 6)
            jsonResponse(['success' => false, 'error' => 'Password must be at least 6 characters.'], 400);

        $pdo  = getDB();
        $stmt = $pdo->prepare("SELECT id FROM users WHERE username = ?");
        $stmt->execute([$username]);
        if ($stmt->fetch())
            jsonResponse(['success' => false, 'error' => 'Username already taken.'], 409);

        $hash = password_hash($password, PASSWORD_BCRYPT);
        $stmt = $pdo->prepare("INSERT INTO users (username, password_hash, role) VALUES (?, ?, 'user')");
        $stmt->execute([$username, $hash]);
        jsonResponse(['success' => true, 'message' => 'Account created! You can now log in.']);
        break;

    case 'logout':
        session_destroy();
        jsonResponse(['success' => true, 'redirect' => BASE_URL . 'login.php']);
        break;

    case 'me':
        if (empty($_SESSION['user_id']))
            jsonResponse(['logged_in' => false]);
        jsonResponse([
            'logged_in' => true,
            'user_id'   => $_SESSION['user_id'],
            'username'  => $_SESSION['username'],
            'role'      => $_SESSION['role'],
        ]);
        break;

    default:
        jsonResponse(['error' => 'Unknown action.'], 400);
}
