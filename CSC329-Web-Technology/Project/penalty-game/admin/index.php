<?php
require_once '../config.php';
requireAdmin();
$activePage = 'dashboard';
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Dashboard | Admin</title>
    <link rel="stylesheet" href="../css/admin.css">
</head>
<body>
<?php include 'sidebar.php'; ?>
<main class="main">
    <div class="page-hd">
        <h1>Dashboard</h1>
        <p>Players, sessions, and the current quiz setup.</p>
    </div>

    <section class="dash-summary" aria-label="System summary">
        <div class="dash-summary-main">
            <div class="dash-summary-label">Current totals</div>
            <div class="dash-summary-metrics">
                <div class="dash-metric">
                    <span class="dash-metric-value" id="s-users">-</span>
                    <span class="dash-metric-label">Players</span>
                </div>
                <div class="dash-metric">
                    <span class="dash-metric-value" id="s-games">-</span>
                    <span class="dash-metric-label">Sessions</span>
                </div>
            </div>
        </div>
        <dl class="dash-summary-meta">
            <div class="dash-meta-item">
                <dt>Quiz Questions</dt>
                <dd id="s-questions">-</dd>
            </div>
            <div class="dash-meta-item">
                <dt>Difficulty</dt>
                <dd id="s-diff">-</dd>
            </div>
        </dl>
    </section>

    <section class="dash-section" aria-labelledby="recent-games-title">
        <div class="dash-section-head">
            <div>
                <h2 id="recent-games-title">Recent Games</h2>
                <p>Most recent saved sessions.</p>
            </div>
        </div>
        <div class="table-wrap">
            <table class="tbl">
                <caption class="sr-only">Recent game sessions</caption>
                <thead><tr>
                    <th>Player</th><th>Goals</th><th>Saves</th><th>Conceded</th><th>Lifelines</th><th>Date</th>
                </tr></thead>
                <tbody id="recent-tbody">
                    <tr><td colspan="6" class="dash-empty">Loading...</td></tr>
                </tbody>
            </table>
        </div>
    </section>
</main>
<script>
const esc = s => String(s).replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');
const num = value => value ?? 0;

async function load() {
    const [sd, rd] = await Promise.all([
        fetch('../api/admin.php?action=get_stats').then(r => r.json()),
        fetch('../api/admin.php?action=get_scores').then(r => r.json())
    ]);

    if (sd.success) {
        const s = sd.stats;
        document.getElementById('s-users').textContent = s.total_users;
        document.getElementById('s-games').textContent = s.total_games;
        document.getElementById('s-questions').textContent = s.total_questions;
        const dEl = document.getElementById('s-diff');
        dEl.textContent = s.goalie_difficulty.charAt(0).toUpperCase() + s.goalie_difficulty.slice(1);
        dEl.className = s.goalie_difficulty === 'easy'
            ? 'dash-meta-value-easy'
            : s.goalie_difficulty === 'hard'
                ? 'dash-meta-value-hard'
                : 'dash-meta-value-medium';
    }

    const tbody = document.getElementById('recent-tbody');
    if (!rd.success || !rd.scores.length) {
        tbody.innerHTML = '<tr><td colspan="6" class="dash-empty">No games yet.</td></tr>';
        return;
    }

    tbody.innerHTML = rd.scores.slice(0, 8).map(r => `
        <tr>
            <td><strong>${esc(r.username)}</strong></td>
            <td>${num(r.goals_scored)}</td>
            <td>${num(r.goals_saved)}</td>
            <td>${num(r.goals_conceded)}</td>
            <td>${num(r.lifelines_used)}</td>
            <td><span class="muted-date">${new Date(r.played_at).toLocaleDateString()}</span></td>
        </tr>`).join('');
}

load();
</script>
</body>
</html>
