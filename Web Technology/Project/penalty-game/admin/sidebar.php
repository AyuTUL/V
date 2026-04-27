<?php
// admin/sidebar.php — shared sidebar for all admin pages
$activePage = $activePage ?? '';
?>
<aside class="sidebar">
    <div class="sidebar-logo">
        <div class="logo-ball">⚽</div>
        <h2>PENALTY ADMIN</h2>
        <p>Control Panel</p>
    </div>

    <nav class="sidebar-nav">
        <div class="nav-section">OVERVIEW</div>
        <a href="index.php"    class="nav-link <?= $activePage === 'dashboard' ? 'active' : '' ?>"><span class="icon">📊</span> Dashboard</a>
        <a href="scores.php"   class="nav-link <?= $activePage === 'scores'    ? 'active' : '' ?>"><span class="icon">🏆</span> All Scores</a>

        <div class="nav-section">MANAGEMENT</div>
        <a href="questions.php" class="nav-link <?= $activePage === 'questions' ? 'active' : '' ?>"><span class="icon">🧠</span> Quiz Questions</a>
        <a href="settings.php"  class="nav-link <?= $activePage === 'settings'  ? 'active' : '' ?>"><span class="icon">⚙️</span> Goalie Settings</a>

        <div class="nav-section">GAME</div>
        <a href="../leaderboard.php" class="nav-link"><span class="icon">📋</span> Leaderboard</a>
    </nav>

    <div class="sidebar-footer">
        <div class="sidebar-user">
            Logged in as<strong><?= htmlspecialchars($_SESSION['username']) ?></strong>
        </div>
        <a href="#" class="btn-sm btn-outline-red" onclick="logout()">Logout</a>
    </div>
</aside>

<script>
function logout() {
    fetch('../api/auth.php', { method:'POST', body: new URLSearchParams({ action:'logout' }) })
    .then(r => r.json())
    .then(d => { window.location.href = d.redirect; });
}
</script>
