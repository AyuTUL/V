<?php
require_once 'config.php';
requireLogin();
if ($_SESSION['role'] === 'admin') { header('Location: ' . BASE_URL . 'admin/index.php'); exit; }
$username = $_SESSION['username'];
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Penalty Shootout</title>
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link href="https://fonts.googleapis.com/css2?family=Oswald:wght@400;600;700&family=Barlow:wght@300;400;500&display=swap" rel="stylesheet">
    <link rel="stylesheet" href="css/game.css">
</head>
<body>

<!-- HUD -->
<div class="hud">
    <div class="hud-left">
        <div class="hud-stat">GOALS <span id="hud-kick" class="green">0</span></div>
        <div class="hud-stat">SAVES <span id="hud-save" class="green">0</span></div>
        <div class="hud-stat">LIFELINES <span id="hud-lifeline" class="red">0</span></div>
    </div>
    <div class="hud-title">⚽ PENALTY SHOOTOUT</div>
    <div class="hud-right">
        <div class="hud-stat">ROUND <span id="hud-round">1/5</span></div>
        <a href="leaderboard.php" class="btn-leaderboard">🏆 SCORES</a>
        <button class="btn-logout" onclick="logout()">LOGOUT</button>
    </div>
</div>

<!-- GAME AREA -->
<div id="game-area">

    <!-- Phase label -->
    <div id="phase-label">⚽ YOUR TURN — SHOOT</div>

    <!-- Round tracker (top-right dots) -->
    <div id="round-tracker"></div>

    <!-- ===== KICK PHASE ===== -->
    <div id="goal-container">
        <div id="goal-frame">
            <div class="goal-zone" id="zone-left"></div>
            <div class="goal-zone" id="zone-center"></div>
            <div class="goal-zone" id="zone-right"></div>
            <div id="keeper"></div>
            <div id="aim-indicator">
                <div class="aim-circle"></div>
            </div>
        </div>
    </div>

    <div id="ball"></div>

    <!-- Power bar -->
    <div id="power-wrap">
        <div id="power-label">POWER</div>
        <div id="power-track">
            <div id="power-fill"></div>
        </div>
    </div>

    <!-- Shoot button -->
    <button id="shoot-btn">HOLD TO CHARGE & RELEASE TO SHOOT</button>

    <!-- ===== SAVE PHASE ===== -->
    <div id="save-area">
        <div id="save-instruction">🧤 MOVE MOUSE TO POSITION KEEPER — CLICK TO DIVE!</div>
        <div id="save-goal-container">
            <div id="save-goal-frame">
                <div class="save-zone" id="szone-left"></div>
                <div class="save-zone" id="szone-center"></div>
                <div class="save-zone" id="szone-right"></div>
                <div id="save-keeper"></div>
                <div id="ai-ball"></div>
                <div id="save-cursor"></div>
            </div>
        </div>
    </div>

    <!-- Result flash -->
    <div id="result-flash">
        <div id="result-emoji">⚽</div>
        <div id="result-text">GOAL!</div>
        <div id="result-sub"></div>
    </div>

</div>

<!-- QUIZ MODAL -->
<div id="quiz-modal">
    <div class="quiz-card">
        <div class="quiz-header">
            <div class="quiz-icon">🧠</div>
            <div>
                <div class="quiz-title">FOOTBALL QUIZ LIFELINE</div>
                <div class="quiz-miss-text">Answer correctly to earn back your missed shot!</div>
            </div>
        </div>
        <div class="quiz-question" id="quiz-question"></div>
        <div class="quiz-options" id="quiz-options"></div>
        <div class="quiz-result" id="quiz-result"></div>
        <button id="quiz-continue">CONTINUE →</button>
    </div>
</div>

<!-- GAME OVER MODAL -->
<div id="gameover-modal">
    <div class="gameover-card">
        <div class="gameover-trophy" id="go-trophy">🏆</div>
        <div class="gameover-title">FULL TIME</div>
        <div style="font-family:'Oswald',sans-serif;font-size:13px;letter-spacing:2px;color:var(--muted);margin-top:4px">FINAL SCORE</div>
        <div class="gameover-score" id="final-score">0</div>

        <div class="gameover-breakdown">
            <div class="breakdown-stat">
                <span id="go-goals-scored">0</span>
                Goals Scored
            </div>
            <div class="breakdown-stat">
                <span id="go-goals-saved">0</span>
                Shots Saved
            </div>
            <div class="breakdown-stat">
                <span id="go-lifelines">0</span>
                Lifelines Used
            </div>
        </div>

        <div class="gameover-btns">
            <button class="btn-play-again" id="btn-play-again">▶ PLAY AGAIN</button>
            <a href="leaderboard.php" class="btn-see-scores">🏆 VIEW LEADERBOARD</a>
        </div>
    </div>
</div>

<script>
    function logout() {
        fetch('api/auth.php', { method:'POST', body: new URLSearchParams({ action:'logout' }) })
        .then(r => r.json())
        .then(d => { window.location.href = d.redirect; });
    }
</script>
<script src="js/game.js"></script>
</body>
</html>
