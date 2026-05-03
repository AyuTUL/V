<!-- Lab 12: Write PHP code to create cookie and session. -->
<?php
session_start();

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $name = $_POST['name'] ?? '';
    if ($name !== '') {
        setcookie('user_name', $name, time() + 3600, '/');
        $_SESSION['user_name'] = $name;
    }
}

$cookieName = $_COOKIE['user_name'] ?? '';
$sessionName = $_SESSION['user_name'] ?? '';
?>
<html>

<head>
    <title>Cookie and Session</title>
</head>

<body>
    <h1>Cookie and Session Demo</h1>

    <form method="POST" action="">
        <label>Enter name:</label>
        <input type="text" name="name">
        <input type="submit" value="Set">
    </form>

    <p>Cookie value: <?php echo htmlspecialchars($cookieName); ?></p>
    <p>Session value: <?php echo htmlspecialchars($sessionName); ?></p>
</body>

</html>