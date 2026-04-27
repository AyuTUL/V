<?php
require_once 'config.php';
requireLogin();
$username = $_SESSION['username'];
$role     = $_SESSION['role'];
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Leaderboard — Penalty Shootout</title>
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link href="https://fonts.googleapis.com/css2?family=Oswald:wght@400;600;700&family=Barlow:wght@300;400;500&display=swap" rel="stylesheet">
    <link rel="stylesheet" href="css/auth.css">
    <style>
        body { overflow: auto; }
        .lb-container { max-width: 800px; margin: 0 auto; padding: 30px 20px; }
        .lb-header { display:flex; align-items:center; justify-content:space-between; margin-bottom:28px; }
        .lb-title { font-family:'Oswald',sans-serif; font-size:28px; font-weight:700; letter-spacing:4px; }
        .lb-back { color:var(--muted); text-decoration:none; font-size:13px; letter-spacing:1px; transition:color 0.2s; }
        .lb-back:hover { color:var(--text); }
        .lb-table { width:100%; border-collapse: collapse; }
        .lb-table th {
            font-family:'Oswald',sans-serif; font-size:11px; letter-spacing:2px;
            color:var(--muted); text-align:left; padding:10px 16px;
            border-bottom: 1px solid var(--border);
        }
        .lb-table td {
            padding: 14px 16px; font-size:15px;
            border-bottom: 1px solid rgba(255,255,255,0.04);
        }
        .lb-table tr:hover td { background: rgba(255,255,255,0.02); }
        .lb-table tr.me td { color: var(--green); }
        .rank { font-family:'Oswald',sans-serif; font-size:18px; font-weight:700; }
        .rank-1 { color: #ffd600; }
        .rank-2 { color: #bdbdbd; }
        .rank-3 { color: #bf8970; }
        .score-val { font-family:'Oswald',sans-serif; font-size:22px; font-weight:700; color:var(--green); }
        .empty { text-align:center; padding:40px; color:var(--muted); font-size:15px; }
    </style>
</head>
<body>
<div class="auth-bg">
    <div class="auth-noise"></div>
    <div class="lb-container">
        <div class="lb-header">
            <div class="lb-title">🏆 LEADERBOARD</div>
            <a href="<?= $role === 'admin' ? 'admin/index.php' : 'game.php' ?>" class="lb-back">← BACK TO <?= $role === 'admin' ? 'DASHBOARD' : 'GAME' ?></a>
        </div>

        <div id="lb-content">
            <div class="empty">Loading scores...</div>
        </div>
    </div>
</div>

<script>
const ME = <?= json_encode($username) ?>;

async function loadLeaderboard() {
    try {
        const res = await fetch('api/game.php?action=get_leaderboard');
        const data = await res.json();

        if (!data.success || !data.leaderboard.length) {
            document.getElementById('lb-content').innerHTML = '<div class="empty">No games played yet. Be the first!</div>';
            return;
        }

        const rows = data.leaderboard.map((row, i) => {
            const rank = i + 1;
            const rankClass = rank <= 3 ? `rank-${rank}` : '';
            const rankDisplay = rank <= 3 ? ['🥇','🥈','🥉'][rank-1] : rank;
            const isMe = row.username === ME;
            return `<tr class="${isMe ? 'me' : ''}">
                <td><span class="rank ${rankClass}">${rankDisplay}</span></td>
                <td>${isMe ? '★ ' : ''}${escHtml(row.username)}</td>
                <td><span class="score-val">${row.best_score}</span></td>
                <td>${row.games_played}</td>
                <td>${row.total_goals}</td>
                <td>${new Date(row.last_played).toLocaleDateString()}</td>
            </tr>`;
        }).join('');

        document.getElementById('lb-content').innerHTML = `
            <table class="lb-table">
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
                <tbody>${rows}</tbody>
            </table>`;
    } catch(e) {
        document.getElementById('lb-content').innerHTML = '<div class="empty">Failed to load scores.</div>';
    }
}

function escHtml(str) {
    return str.replace(/&/g,'&amp;').replace(/</g,'&lt;').replace(/>/g,'&gt;');
}

loadLeaderboard();
</script>
</body>
</html>
