<?php
require_once '../config.php';
requireAdmin();
$activePage = 'scores';
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>All Scores — Admin</title>
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link href="https://fonts.googleapis.com/css2?family=Oswald:wght@400;600;700&family=Barlow:wght@300;400;500&display=swap" rel="stylesheet">
    <link rel="stylesheet" href="../css/admin.css">
</head>
<body>

<?php include 'sidebar.php'; ?>

<div class="main">
    <div class="page-header">
        <h1>🏆 ALL SCORES</h1>
        <p>Full game history across all players (last 100 games)</p>
    </div>

    <div class="card">
        <div class="card-header">
            <span class="card-title">GAME HISTORY</span>
            <div style="display:flex;gap:10px;align-items:center">
                <input type="text" id="search-input" placeholder="Search player..." 
                       style="background:rgba(255,255,255,0.05);border:1px solid var(--border);border-radius:6px;color:var(--text);padding:7px 12px;font-family:'Barlow',sans-serif;font-size:13px;outline:none">
                <button class="btn-primary" onclick="loadScores()" style="font-size:12px;padding:8px 16px">↺ REFRESH</button>
            </div>
        </div>
        <div style="overflow-x:auto">
            <table class="admin-table">
                <thead>
                    <tr>
                        <th>#</th>
                        <th>PLAYER</th>
                        <th>GOALS</th>
                        <th>SAVES</th>
                        <th>ROUNDS</th>
                        <th>LIFELINES</th>
                        <th>FINAL SCORE</th>
                        <th>DATE & TIME</th>
                    </tr>
                </thead>
                <tbody id="scores-tbody">
                    <tr><td colspan="8" style="text-align:center;color:var(--muted);padding:24px">Loading...</td></tr>
                </tbody>
            </table>
        </div>
    </div>

    <!-- Per-player leaderboard -->
    <div class="card">
        <div class="card-header"><span class="card-title">PLAYER STATS (BEST SCORES)</span></div>
        <div style="overflow-x:auto">
            <table class="admin-table">
                <thead>
                    <tr>
                        <th>RANK</th>
                        <th>PLAYER</th>
                        <th>BEST SCORE</th>
                        <th>GAMES</th>
                        <th>TOTAL GOALS</th>
                        <th>LAST PLAYED</th>
                    </tr>
                </thead>
                <tbody id="lb-tbody">
                    <tr><td colspan="6" style="text-align:center;color:var(--muted);padding:24px">Loading...</td></tr>
                </tbody>
            </table>
        </div>
    </div>
</div>

<script>
let allScores = [];

async function loadScores() {
    const res  = await fetch('../api/admin.php?action=get_scores');
    const data = await res.json();
    allScores  = data.scores || [];
    renderScores(allScores);
}

function renderScores(scores) {
    const tbody = document.getElementById('scores-tbody');
    if (!scores.length) {
        tbody.innerHTML = '<tr><td colspan="8" style="text-align:center;color:var(--muted);padding:24px">No games played yet.</td></tr>';
        return;
    }
    tbody.innerHTML = scores.map((row, i) => `
        <tr>
            <td style="color:var(--muted)">${i+1}</td>
            <td><strong>${esc(row.username)}</strong></td>
            <td>⚽ ${row.goals_scored}/5</td>
            <td>🧤 ${row.goals_saved}/5</td>
            <td>${row.rounds_played}</td>
            <td>${row.lifelines_used}</td>
            <td><strong style="color:var(--green);font-family:'Oswald',sans-serif;font-size:18px">${row.final_score}</strong></td>
            <td style="color:var(--muted);font-size:13px">${new Date(row.played_at).toLocaleString()}</td>
        </tr>`).join('');
}

async function loadLeaderboard() {
    const res  = await fetch('../api/game.php?action=get_leaderboard');
    const data = await res.json();
    const tbody = document.getElementById('lb-tbody');
    if (!data.success || !data.leaderboard.length) {
        tbody.innerHTML = '<tr><td colspan="6" style="text-align:center;color:var(--muted);padding:24px">No data.</td></tr>';
        return;
    }
    const medals = ['🥇','🥈','🥉'];
    tbody.innerHTML = data.leaderboard.map((row, i) => `
        <tr>
            <td>${medals[i] || (i+1)}</td>
            <td><strong>${esc(row.username)}</strong></td>
            <td><strong style="color:var(--green);font-family:'Oswald',sans-serif;font-size:18px">${row.best_score}</strong></td>
            <td>${row.games_played}</td>
            <td>⚽ ${row.total_goals}</td>
            <td style="color:var(--muted)">${new Date(row.last_played).toLocaleDateString()}</td>
        </tr>`).join('');
}

// Search filter
document.getElementById('search-input').addEventListener('input', (e) => {
    const q = e.target.value.toLowerCase();
    renderScores(allScores.filter(s => s.username.toLowerCase().includes(q)));
});

function esc(s) { return String(s).replace(/&/g,'&amp;').replace(/</g,'&lt;').replace(/>/g,'&gt;'); }

loadScores();
loadLeaderboard();
</script>
</body>
</html>
