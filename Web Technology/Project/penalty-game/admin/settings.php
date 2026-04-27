<?php
require_once '../config.php';
requireAdmin();
$activePage = 'settings';
$currentDiff = getSetting('goalie_difficulty', 'medium');
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Settings — Admin</title>
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link href="https://fonts.googleapis.com/css2?family=Oswald:wght@400;600;700&family=Barlow:wght@300;400;500&display=swap" rel="stylesheet">
    <link rel="stylesheet" href="../css/admin.css">
</head>
<body>

<?php include 'sidebar.php'; ?>

<div class="main">
    <div class="page-header">
        <h1>⚙️ GOALIE SETTINGS</h1>
        <p>Configure the AI goalkeeper difficulty for all players</p>
    </div>

    <div class="card" style="max-width:580px">
        <div class="card-header"><span class="card-title">GOALKEEPER DIFFICULTY</span></div>
        <div class="card-body">
            <p style="color:var(--muted);font-size:14px;margin-bottom:24px;line-height:1.6">
                This controls how accurately the AI goalkeeper predicts where the player will shoot.
                Higher difficulty means the keeper dives to the correct zone more often.
            </p>

            <div id="diff-alert"></div>

            <div style="display:flex;flex-direction:column;gap:16px;margin-bottom:28px">
                <div class="diff-card" data-diff="easy">
                    <div style="display:flex;align-items:center;justify-content:space-between">
                        <div>
                            <div style="font-family:'Oswald',sans-serif;font-size:16px;font-weight:600;color:var(--green)">🟢 EASY</div>
                            <div style="font-size:13px;color:var(--muted);margin-top:4px">30% chance keeper dives correctly — very beatable</div>
                        </div>
                        <button class="diff-pill <?= $currentDiff==='easy'?'active':'' ?>" data-diff="easy">
                            <?= $currentDiff==='easy'?'✓ ACTIVE':'SELECT' ?>
                        </button>
                    </div>
                </div>

                <div class="diff-card" data-diff="medium" style="padding:16px;background:rgba(255,255,255,0.02);border-radius:10px;border:1px solid var(--border)">
                    <div style="display:flex;align-items:center;justify-content:space-between">
                        <div>
                            <div style="font-family:'Oswald',sans-serif;font-size:16px;font-weight:600;color:var(--yellow)">🟡 MEDIUM</div>
                            <div style="font-size:13px;color:var(--muted);margin-top:4px">50% chance keeper dives correctly — fair challenge</div>
                        </div>
                        <button class="diff-pill <?= $currentDiff==='medium'?'active':'' ?>" data-diff="medium">
                            <?= $currentDiff==='medium'?'✓ ACTIVE':'SELECT' ?>
                        </button>
                    </div>
                </div>

                <div class="diff-card" data-diff="hard" style="padding:16px;background:rgba(255,255,255,0.02);border-radius:10px;border:1px solid var(--border)">
                    <div style="display:flex;align-items:center;justify-content:space-between">
                        <div>
                            <div style="font-family:'Oswald',sans-serif;font-size:16px;font-weight:600;color:var(--red)">🔴 HARD</div>
                            <div style="font-size:13px;color:var(--muted);margin-top:4px">75% chance keeper dives correctly — very difficult</div>
                        </div>
                        <button class="diff-pill <?= $currentDiff==='hard'?'active':'' ?>" data-diff="hard">
                            <?= $currentDiff==='hard'?'✓ ACTIVE':'SELECT' ?>
                        </button>
                    </div>
                </div>
            </div>

            <p style="font-size:12px;color:var(--muted)">
                ⚠️ Difficulty changes apply immediately to all new games. Currently active:
                <strong style="color:var(--text);text-transform:uppercase"><?= $currentDiff ?></strong>
            </p>
        </div>
    </div>
</div>

<style>
.diff-card { padding:16px;background:rgba(255,255,255,0.02);border-radius:10px;border:1px solid var(--border); }
</style>

<script>
document.querySelectorAll('.diff-pill').forEach(btn => {
    btn.addEventListener('click', async () => {
        const diff = btn.dataset.diff;
        const alertEl = document.getElementById('diff-alert');
        alertEl.innerHTML = '';

        const body = new FormData();
        body.append('action', 'set_difficulty');
        body.append('difficulty', diff);

        const res  = await fetch('../api/admin.php', { method:'POST', body });
        const data = await res.json();

        if (data.success) {
            // Update all buttons
            document.querySelectorAll('.diff-pill').forEach(b => {
                b.classList.remove('active');
                b.textContent = 'SELECT';
            });
            btn.classList.add('active');
            btn.textContent = '✓ ACTIVE';
            alertEl.innerHTML = `<div class="alert alert-success">✅ ${data.message}</div>`;
        } else {
            alertEl.innerHTML = `<div class="alert alert-error">❌ ${data.error}</div>`;
        }

        setTimeout(() => { alertEl.innerHTML = ''; }, 3000);
    });
});
</script>
</body>
</html>
