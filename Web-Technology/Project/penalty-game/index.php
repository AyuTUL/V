<?php
require_once 'config.php';
startSession();

if (!empty($_SESSION['user_id'])) {
    $redirect = $_SESSION['role'] === 'admin' ? 'admin/index.php' : 'game.php';
    header('Location: ' . BASE_URL . $redirect);
} else {
    header('Location: ' . BASE_URL . 'login.php');
}
exit;
