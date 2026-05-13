<?php
require_once '../config.php';
requireAdmin();
$activePage = 'settings';
$diff = getSetting('goalie_difficulty', 'medium');
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Keeper Difficulty | Admin</title>
    <link rel="stylesheet" href="../css/admin.css">
</head>
<body>
<?php include 'sidebar.php'; ?>
<main class="main">
    <div class="page-hd">
        <h1>Keeper Difficulty</h1>
        <p>Choose how often the AI keeper guesses the right zone.</p>
    </div>

    <div class="card card--narrow">
        <div class="card-hd"><span class="card-hd-title">Difficulty</span></div>
        <div id="diff-alert" aria-live="polite"></div>
        <div class="diff-opts" role="radiogroup" aria-label="Keeper difficulty">
            <?php foreach ([
                'easy'   => ['30% correct dives, very beatable', 'diff-name-easy'],
                'medium' => ['50% correct dives, balanced default', 'diff-name-medium'],
                'hard'   => ['75% correct dives, tough to beat', 'diff-name-hard'],
            ] as $key => [$desc, $class]): ?>
            <div class="diff-opt">
                <div class="diff-opt-info">
                    <div class="name <?= $class ?>"><?= ucfirst($key) ?></div>
                    <div class="desc"><?= $desc ?></div>
                </div>
                <button type="button" class="diff-pill <?= $diff === $key ? 'active' : '' ?>" data-diff="<?= $key ?>" role="radio" aria-checked="<?= $diff === $key ? 'true' : 'false' ?>">
                    <?= $diff === $key ? 'Active' : 'Select' ?>
                </button>
            </div>
            <?php endforeach; ?>
        </div>
        <div class="card-note">
            Changes apply immediately to all new games.
        </div>
    </div>
</main>

<script>
document.querySelectorAll('.diff-pill').forEach(btn => btn.addEventListener('click', async () => {
    const body = new FormData();
    body.append('action', 'set_difficulty');
    body.append('difficulty', btn.dataset.diff);
    const d = await fetch('../api/admin.php', { method: 'POST', body }).then(r => r.json());
    const alertEl = document.getElementById('diff-alert');
    if (d.success) {
        document.querySelectorAll('.diff-pill').forEach(b => {
            b.classList.remove('active');
            b.textContent = 'Select';
            b.setAttribute('aria-checked', 'false');
        });
        btn.classList.add('active');
        btn.textContent = 'Active';
        btn.setAttribute('aria-checked', 'true');
        alertEl.innerHTML = `<div class="alert alert-ok alert-tight">${d.message}</div>`;
    } else {
        alertEl.innerHTML = `<div class="alert alert-err alert-tight">${d.error}</div>`;
    }
    setTimeout(() => alertEl.innerHTML = '', 3000);
}));
</script>
</body>
</html>
