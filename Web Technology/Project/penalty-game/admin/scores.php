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
    <title>All Scores | Admin</title>
    <link rel="stylesheet" href="../css/admin.css">
</head>
<body>
<?php include 'sidebar.php'; ?>
<main class="main">
    <div class="page-hd">
        <h1>All Scores</h1>
        <p>View and delete session history, plus player totals.</p>
    </div>

    <section class="section-block" aria-labelledby="scores-total-title">
        <div class="section-head">
            <span class="section-title" id="scores-total-title">Totals</span>
        </div>
        <div class="table-wrap">
            <table class="tbl">
                <caption class="sr-only">Leaderboard summary of player totals</caption>
                <thead><tr>
                    <th>#</th><th>Player</th><th>Games</th>
                    <th>Goals</th><th>Saves</th><th>Conceded</th><th>Lifelines</th><th>Last Played</th>
                </tr></thead>
                <tbody id="lb-tbody">
                    <tr><td colspan="8" class="table-empty">Loading...</td></tr>
                </tbody>
            </table>
        </div>
    </section>

    <section class="section-block" aria-labelledby="scores-history-title">
        <div class="section-head">
            <span class="section-title" id="scores-history-title">Sessions</span>
            <div class="toolbar-group">
                <label class="sr-only" for="search">Filter by player</label>
                <input type="text" class="search-input" id="search" placeholder="Filter by player">
            </div>
        </div>
        <div class="table-wrap">
            <table class="tbl">
                <caption class="sr-only">Game history for all player sessions</caption>
                <thead><tr>
                    <th>ID</th><th>Player</th>
                    <th>Goals</th><th>Saves</th><th>Conceded</th><th>Lifelines</th>
                    <th>Date</th><th>Actions</th>
                </tr></thead>
                <tbody id="scores-tbody">
                    <tr><td colspan="8" class="table-empty">Loading...</td></tr>
                </tbody>
            </table>
        </div>
    </section>
</main>

<div class="modal" id="del-modal" role="dialog" aria-modal="true" aria-labelledby="delete-score-title" aria-describedby="delete-score-desc" aria-hidden="true">
    <div class="modal-box">
        <h3 id="delete-score-title">Delete this score?</h3>
        <p id="delete-score-desc">This cannot be undone.</p>
        <div class="modal-actions">
            <button type="button" class="btn btn-ghost" onclick="closeDeleteModal()">Cancel</button>
            <button type="button" class="btn btn-acc" id="confirm-del">Delete</button>
        </div>
    </div>
</div>

<script>
let allScores = [], deleteId = null, lastFocus = null;
const esc = s => String(s).replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');
const num = value => value ?? 0;

function showDel(id) {
    deleteId = id;
    lastFocus = document.activeElement;
    const modal = document.getElementById('del-modal');
    modal.classList.add('show');
    modal.setAttribute('aria-hidden', 'false');
    document.getElementById('confirm-del').focus();
}

function closeDeleteModal() {
    deleteId = null;
    const modal = document.getElementById('del-modal');
    modal.classList.remove('show');
    modal.setAttribute('aria-hidden', 'true');
    lastFocus?.focus?.();
}

document.addEventListener('keydown', e => {
    if (e.key === 'Escape' && document.getElementById('del-modal').classList.contains('show')) {
        closeDeleteModal();
    }
});

async function loadScores() {
    const d = await fetch('../api/admin.php?action=get_scores').then(r => r.json());
    allScores = d.scores || [];
    render(allScores);
}

function render(scores) {
    const tbody = document.getElementById('scores-tbody');
    if (!scores.length) {
        tbody.innerHTML = '<tr><td colspan="8" class="table-empty">No results.</td></tr>';
        return;
    }
    tbody.innerHTML = scores.map(r => `
        <tr id="row-${r.id}">
            <td><span class="table-id">${r.id}</span></td>
            <td><strong>${esc(r.username)}</strong></td>
            <td>${num(r.goals_scored)}</td>
            <td>${num(r.goals_saved)}</td>
            <td>${num(r.goals_conceded)}</td>
            <td>${num(r.lifelines_used)}</td>
            <td><span class="muted-date">${new Date(r.played_at).toLocaleDateString()}</span></td>
            <td>
                <button type="button" class="btn-del" onclick="showDel(${r.id})">Delete</button>
            </td>
        </tr>`).join('');
}

document.getElementById('confirm-del').addEventListener('click', async () => {
    if (!deleteId) return;
    const body = new FormData();
    body.append('action', 'delete_score');
    body.append('id', deleteId);
    await fetch('../api/admin.php', { method: 'POST', body });
    closeDeleteModal();
    loadScores();
});

document.getElementById('search').addEventListener('input', e => {
    const q = e.target.value.toLowerCase();
    render(allScores.filter(s => s.username.toLowerCase().includes(q)));
});

async function loadLeaderboard() {
    const d = await fetch('../api/game.php?action=get_leaderboard').then(r => r.json());
    const tbody = document.getElementById('lb-tbody');
    if (!d.success || !d.leaderboard.length) {
        tbody.innerHTML = '<tr><td colspan="8" class="table-empty">No data.</td></tr>';
        return;
    }
    tbody.innerHTML = d.leaderboard.map((r, i) => `
        <tr>
            <td><span class="table-id">${i + 1}</span></td>
            <td><strong>${esc(r.username)}</strong></td>
            <td>${num(r.games_played)}</td>
            <td><strong>${num(r.total_goals)}</strong></td>
            <td>${num(r.total_saves)}</td>
            <td>${num(r.total_conceded)}</td>
            <td>${num(r.total_lifelines)}</td>
            <td><span class="muted-date">${new Date(r.last_played).toLocaleDateString()}</span></td>
        </tr>`).join('');
}

loadScores();
loadLeaderboard();
</script>
</body>
</html>
