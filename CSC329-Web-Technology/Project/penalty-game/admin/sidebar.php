<?php $activePage = $activePage ?? ''; ?>
<aside class="sidebar">
    <div class="sidebar-brand">
        <div class="name">PENALTY<span>.</span>SHOOTOUT</div>
        <div class="sub">Admin</div>
    </div>
    <nav class="sidebar-nav" aria-label="Admin navigation">
        <div class="nav-group">Overview</div>
        <a href="index.php" class="nav-link <?= $activePage === 'dashboard' ? 'active' : '' ?>">Dashboard</a>
        <a href="scores.php" class="nav-link <?= $activePage === 'scores' ? 'active' : '' ?>">All Scores</a>
        <div class="nav-group">Manage</div>
        <a href="questions.php" class="nav-link <?= $activePage === 'questions' ? 'active' : '' ?>">Quiz Questions</a>
        <a href="settings.php" class="nav-link <?= $activePage === 'settings' ? 'active' : '' ?>">Keeper Difficulty</a>
        <div class="nav-group">Game</div>
        <a href="../leaderboard.php" class="nav-link">Leaderboard</a>
    </nav>
    <div class="sidebar-foot">
        <div class="foot-user">Signed in as<strong><?= htmlspecialchars($_SESSION['username']) ?></strong></div>
        <button type="button" class="btn-sm" onclick="logout()">Logout</button>
    </div>
</aside>
<script>
function logout() {
    fetch('../api/auth.php', { method: 'POST', body: new URLSearchParams({ action: 'logout' }) })
    .then(r => r.json()).then(d => window.location.href = d.redirect);
}
</script>
