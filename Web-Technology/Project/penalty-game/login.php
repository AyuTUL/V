<?php
require_once 'config.php';
startSession();
if (!empty($_SESSION['user_id'])) {
    header('Location: ' . BASE_URL . ($_SESSION['role'] === 'admin' ? 'admin/index.php' : 'game.php'));
    exit;
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Penalty Shootout</title>
    <link rel="stylesheet" href="css/auth.css">
</head>
<body class="login-screen">
<main class="wrap" aria-labelledby="auth-title">
    <div class="wordmark">
        
        <div class="wordmark-title" id="auth-title">PENALTY<span>.</span>SHOOTOUT</div>
    </div>

    <div class="card">
        <div class="tabs" role="tablist" aria-label="Authentication views">
            <button type="button" class="tab active" id="tab-btn-login" data-tab="login" role="tab" aria-controls="tab-login" aria-selected="true">Login</button>
            <button type="button" class="tab" id="tab-btn-register" data-tab="register" role="tab" aria-controls="tab-register" aria-selected="false">Register</button>
        </div>
        <div class="tab-body">

            <section id="tab-login" class="tab-pane active" role="tabpanel" aria-labelledby="tab-btn-login">
                <fieldset class="role-row role-group">
                    <legend class="sr-only">Login role</legend>
                    <label class="role-opt active">
                        <input type="radio" name="role" value="user" checked>
                        <span class="role-dot"></span>
                        <span class="role-label">Player</span>
                    </label>
                    <label class="role-opt">
                        <input type="radio" name="role" value="admin">
                        <span class="role-dot"></span>
                        <span class="role-label">Admin</span>
                    </label>
                </fieldset>
                <form id="loginForm">
                    <div class="field">
                        <label for="l-user">Username</label>
                        <input type="text" id="l-user" autocomplete="username" required aria-describedby="l-err">
                    </div>
                    <div class="field">
                        <label for="l-pass">Password</label>
                        <input type="password" id="l-pass" autocomplete="current-password" required aria-describedby="l-err">
                    </div>
                    <div class="msg err" id="l-err" aria-live="polite"></div>
                    <button type="submit" class="btn">Enter</button>
                </form>
            </section>

            <section id="tab-register" class="tab-pane" role="tabpanel" aria-labelledby="tab-btn-register" hidden>
                <div class="note">Players can register here. Admin accounts are created separately.</div>
                <form id="regForm">
                    <div class="field">
                        <label for="r-user">Username</label>
                        <input type="text" id="r-user" autocomplete="username" required minlength="3" maxlength="50" aria-describedby="r-err r-ok">
                    </div>
                    <div class="field">
                        <label for="r-pass">Password</label>
                        <input type="password" id="r-pass" autocomplete="new-password" required minlength="6" aria-describedby="r-err r-ok">
                    </div>
                    <div class="msg err" id="r-err" aria-live="polite"></div>
                    <div class="msg ok" id="r-ok" aria-live="polite"></div>
                    <button type="submit" class="btn">Create Account</button>
                </form>
            </section>

        </div>
    </div>
</main>

<script>
document.querySelectorAll('.tab').forEach(t => t.addEventListener('click', () => {
    document.querySelectorAll('.tab').forEach(tab => {
        const active = tab === t;
        tab.classList.toggle('active', active);
        tab.setAttribute('aria-selected', String(active));
    });
    document.querySelectorAll('.tab-pane').forEach(pane => {
        const active = pane.id === 'tab-' + t.dataset.tab;
        pane.classList.toggle('active', active);
        pane.hidden = !active;
    });
}));

document.querySelectorAll('input[name="role"]').forEach(r => r.addEventListener('change', () => {
    document.querySelectorAll('.role-opt').forEach(l => l.classList.remove('active'));
    r.closest('.role-opt').classList.add('active');
}));

document.getElementById('loginForm').addEventListener('submit', async e => {
    e.preventDefault();
    const err = document.getElementById('l-err');
    const btn = e.target.querySelector('button');
    err.textContent = '';
    btn.disabled = true;
    btn.textContent = 'Loading...';
    const body = new FormData();
    body.append('action', 'login');
    body.append('username', document.getElementById('l-user').value.trim());
    body.append('password', document.getElementById('l-pass').value);
    body.append('expected_role', document.querySelector('input[name="role"]:checked').value);
    try {
        const d = await fetch('api/auth.php', { method: 'POST', body }).then(r => r.json());
        if (d.success) {
            window.location.href = d.redirect;
            return;
        }
        err.textContent = d.error;
    } catch {
        err.textContent = 'Connection error.';
    }
    btn.disabled = false;
    btn.textContent = 'Enter';
});

document.getElementById('regForm').addEventListener('submit', async e => {
    e.preventDefault();
    const err = document.getElementById('r-err');
    const ok = document.getElementById('r-ok');
    const btn = e.target.querySelector('button');
    err.textContent = '';
    ok.textContent = '';
    btn.disabled = true;
    btn.textContent = 'Creating...';
    const body = new FormData();
    body.append('action', 'register');
    body.append('username', document.getElementById('r-user').value.trim());
    body.append('password', document.getElementById('r-pass').value);
    try {
        const d = await fetch('api/auth.php', { method: 'POST', body }).then(r => r.json());
        if (d.success) {
            ok.textContent = d.message;
            e.target.reset();
        } else {
            err.textContent = d.error;
        }
    } catch {
        err.textContent = 'Connection error.';
    }
    btn.disabled = false;
    btn.textContent = 'Create Account';
});
</script>
</body>
</html>
