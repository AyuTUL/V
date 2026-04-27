<?php
require_once '../config.php';
requireAdmin();
$username = $_SESSION['username'];
$activePage = 'dashboard';
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Admin Dashboard — Penalty Shootout</title>
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link href="https://fonts.googleapis.com/css2?family=Oswald:wght@400;600;700&family=Barlow:wght@300;400;500&display=swap" rel="stylesheet">
    <link rel="stylesheet" href="../css/admin.css">
</head>
<body>

<?php include 'sidebar.php'; ?>

<div class="main">
    <div class="page-header">
        <h1>DASHBOARD</h1>
        <p>Overview of the Penalty Shootout system</p>
    </div>

    <!-- Stats -->
    <div class="stats-grid" id="stats-grid">
        <div class="stat-card"><div class="label">TOTAL USERS</div><div class="value green" id="stat-users">—</div></div>
        <div class="stat-card"><div class="label">GAMES PLAYED</div><div class="value" id="stat-games">—</div></div>
        <div class="stat-card"><div class="label">QUIZ QUESTIONS</div><div class="value" id="stat-questions">—</div></div>
        <div class="stat-card"><div class="label">HIGHEST SCORE</div><div class="value green" id="stat-high">—</div></div>
        <div class="stat-card"><div class="label">GOALIE DIFFICULTY</div><div class="value" id="stat-diff" style="font-size:20px;text-transform:uppercase">—</div></div>
    </div>

    <!-- Recent scores preview -->
    <div class="card">
        <div class="card-header">
            <span class="card-title">📊 RECENT GAMES</span>
            <a href="scores.php" style="font-size:13px;color:var(--muted);text-decoration:none">View all →</a>
        </div>
        <div style="overflow-x:auto">
            <table class="admin-table">
                <thead>
                    <tr>
                        <th>PLAYER</th>
                        <th>GOALS</th>
                        <th>SAVES</th>
                        <th>LIFELINES</th>
                        <th>SCORE</th>
                        <th>DATE</th>
                    </tr>
                </thead>
                <tbody id="recent-scores">
                    <tr><td colspan="6" style="text-align:center;color:var(--muted);padding:24px">Loading...</td></tr>
                </tbody>
            </table>
        </div>
    </div>
</div>

<script>
async function loadStats() {
    const res = await fetch('../api/admin.php?action=get_stats');
    const data = await res.json();
    if (data.success) {
        const s = data.stats;
        document.getElementById('stat-users').textContent     = s.total_users;
        document.getElementById('stat-games').textContent     = s.total_games;
        document.getElementById('stat-questions').textContent = s.total_questions;
        document.getElementById('stat-high').textContent      = s.highest_score || 0;
        const diff = s.goalie_difficulty;
        const el   = document.getElementById('stat-diff');
        el.textContent = diff;
        el.style.color = diff === 'easy' ? 'var(--green)' : diff === 'hard' ? 'var(--red)' : 'var(--yellow)';
    }
}

async function loadRecentScores() {
    const res = await fetch('../api/admin.php?action=get_scores');
    const data = await res.json();
    const tbody = document.getElementById('recent-scores');
    if (!data.success || !data.scores.length) {
        tbody.innerHTML = '<tr><td colspan="6" style="text-align:center;color:var(--muted);padding:24px">No games yet.</td></tr>';
        return;
    }
    tbody.innerHTML = data.scores.slice(0, 8).map(row => `
        <tr>
            <td><strong>${esc(row.username)}</strong></td>
            <td>⚽ ${row.goals_scored}</td>
            <td>🧤 ${row.goals_saved}</td>
            <td>${row.lifelines_used}</td>
            <td><strong style="color:var(--green)">${row.final_score}</strong></td>
            <td style="color:var(--muted)">${new Date(row.played_at).toLocaleDateString()}</td>
        </tr>`).join('');
}

function esc(s) { return s.replace(/&/g,'&amp;').replace(/</g,'&lt;').replace(/>/g,'&gt;'); }

loadStats();
loadRecentScores();
</script>
</body>
</html>
