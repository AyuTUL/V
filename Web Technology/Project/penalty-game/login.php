<?php
require_once 'config.php';
startSession();
if (!empty($_SESSION['user_id'])) {
    $redirect = $_SESSION['role'] === 'admin' ? 'admin/index.php' : 'game.php';
    header('Location: ' . BASE_URL . $redirect);
    exit;
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Penalty Shootout — Login</title>
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link href="https://fonts.googleapis.com/css2?family=Oswald:wght@400;600;700&family=Barlow:wght@300;400;500&display=swap" rel="stylesheet">
    <link rel="stylesheet" href="css/auth.css">
</head>
<body>
    <div class="auth-bg">
        <div class="auth-noise"></div>
        <div class="auth-container">
            <div class="auth-logo">
                <div class="logo-ball">⚽</div>
                <h1>PENALTY<br><span>SHOOTOUT</span></h1>
            </div>

            <div class="auth-card">
                <div class="tab-switcher">
                    <button class="tab-btn active" data-tab="login">LOGIN</button>
                    <button class="tab-btn" data-tab="register">REGISTER</button>
                </div>

                <div id="tab-login" class="tab-content active">
                    <form id="loginForm">
                        <div class="field-group">
                            <label>USERNAME</label>
                            <input type="text" name="username" id="login-username" autocomplete="username" required>
                        </div>
                        <div class="field-group">
                            <label>PASSWORD</label>
                            <input type="password" name="password" id="login-password" autocomplete="current-password" required>
                        </div>
                        <div class="error-msg" id="login-error"></div>
                        <button type="submit" class="btn-primary">KICK OFF →</button>
                    </form>
                    <p class="auth-hint">Admin? Use your admin credentials to access the dashboard.</p>
                </div>

                <div id="tab-register" class="tab-content">
                    <form id="registerForm">
                        <div class="field-group">
                            <label>USERNAME</label>
                            <input type="text" name="username" id="reg-username" autocomplete="username" required minlength="3" maxlength="50">
                        </div>
                        <div class="field-group">
                            <label>PASSWORD</label>
                            <input type="password" name="password" id="reg-password" autocomplete="new-password" required minlength="6">
                        </div>
                        <div class="error-msg" id="register-error"></div>
                        <div class="success-msg" id="register-success"></div>
                        <button type="submit" class="btn-primary">CREATE ACCOUNT</button>
                    </form>
                </div>
            </div>
        </div>
    </div>
    <script>
        // Tab switching
        document.querySelectorAll('.tab-btn').forEach(btn => {
            btn.addEventListener('click', () => {
                document.querySelectorAll('.tab-btn, .tab-content').forEach(el => el.classList.remove('active'));
                btn.classList.add('active');
                document.getElementById('tab-' + btn.dataset.tab).classList.add('active');
            });
        });

        // Login
        document.getElementById('loginForm').addEventListener('submit', async (e) => {
            e.preventDefault();
            const err = document.getElementById('login-error');
            err.textContent = '';
            const btn = e.target.querySelector('button');
            btn.disabled = true; btn.textContent = 'LOGGING IN...';

            const body = new FormData();
            body.append('action', 'login');
            body.append('username', document.getElementById('login-username').value);
            body.append('password', document.getElementById('login-password').value);

            try {
                const res = await fetch('api/auth.php', { method: 'POST', body });
                const data = await res.json();
                if (data.success) {
                    window.location.href = data.redirect;
                } else {
                    err.textContent = data.error;
                    btn.disabled = false; btn.textContent = 'KICK OFF →';
                }
            } catch { err.textContent = 'Connection error.'; btn.disabled = false; btn.textContent = 'KICK OFF →'; }
        });

        // Register
        document.getElementById('registerForm').addEventListener('submit', async (e) => {
            e.preventDefault();
            const err = document.getElementById('register-error');
            const succ = document.getElementById('register-success');
            err.textContent = ''; succ.textContent = '';
            const btn = e.target.querySelector('button');
            btn.disabled = true; btn.textContent = 'CREATING...';

            const body = new FormData();
            body.append('action', 'register');
            body.append('username', document.getElementById('reg-username').value);
            body.append('password', document.getElementById('reg-password').value);

            try {
                const res = await fetch('api/auth.php', { method: 'POST', body });
                const data = await res.json();
                if (data.success) {
                    succ.textContent = data.message;
                    e.target.reset();
                } else {
                    err.textContent = data.error;
                }
            } catch { err.textContent = 'Connection error.'; }
            btn.disabled = false; btn.textContent = 'CREATE ACCOUNT';
        });
    </script>
</body>
</html>
