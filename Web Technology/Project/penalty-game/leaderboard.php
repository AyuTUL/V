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
    <title>Leaderboard | Penalty Shootout</title>
    <link rel="stylesheet" href="css/auth.css">
</head>
<body class="leaderboard-screen">
<main class="lb-wrap">
    <div class="page-head">
        <div>
            <h1>Leaderboard</h1>
            <p>Totals across every saved session.</p>
        </div>
        <a class="page-link" href="<?= $role === 'admin' ? 'admin/index.php' : 'game.php' ?>">
            &larr; Back to <?= $role === 'admin' ? 'dashboard' : 'game' ?>
        </a>
    </div>
    <div class="table-wrap">
        <table class="lb-table">
            <caption class="sr-only">Leaderboard of players and their game totals</caption>
            <thead>
                <tr>
                    <th>#</th>
                    <th>Player</th>
                    <th class="center">Games</th>
                    <th class="center">Goals</th>
                    <th class="center">Saves</th>
                    <th class="center">Conceded</th>
                    <th class="center">Lifelines</th>
                    <th>Last played</th>
                </tr>
            </thead>
            <tbody id="lb-body">
                <tr class="empty-row"><td colspan="8">Loading...</td></tr>
            </tbody>
        </table>
    </div>
</main>
<script>
const ME  = <?= json_encode($username) ?>;
const esc = s => String(s).replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');
const num = value => value ?? 0;
const formatDate = value => new Date(value).toLocaleDateString();

fetch('api/game.php?action=get_leaderboard')
.then(r => r.json()).then(d => {
    const tbody = document.getElementById('lb-body');
    if (!d.success || !d.leaderboard.length) {
        tbody.innerHTML = '<tr class="empty-row"><td colspan="8">No games played yet.</td></tr>';
        return;
    }
    const rankClass = i => i === 0 ? 'rank-1' : i === 1 ? 'rank-2' : i === 2 ? 'rank-3' : 'rank-num';
    tbody.innerHTML = d.leaderboard.map((r, i) => `
        <tr class="${r.username === ME ? 'me' : ''}">
            <td><span class="${rankClass(i)}">${i + 1}</span></td>
            <td>
                ${esc(r.username)}
                ${r.username === ME ? '<span class="me-tag">YOU</span>' : ''}
            </td>
            <td class="center"><span class="stat-n">${num(r.games_played)}</span></td>
            <td class="center"><span class="stat-n">${num(r.total_goals)}</span></td>
            <td class="center"><span class="stat-n">${num(r.total_saves)}</span></td>
            <td class="center"><span class="stat-n">${num(r.total_conceded)}</span></td>
            <td class="center"><span class="stat-n">${num(r.total_lifelines)}</span></td>
            <td><span class="muted-date">${formatDate(r.last_played)}</span></td>
        </tr>`).join('');
}).catch(() => {
    document.getElementById('lb-body').innerHTML = '<tr class="empty-row"><td colspan="8">Failed to load.</td></tr>';
});
</script>
</body>
</html>
