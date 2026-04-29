<?php
require_once 'config.php';
requireLogin();
if ($_SESSION['role'] === 'admin') { header('Location: ' . BASE_URL . 'admin/index.php'); exit; }
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Penalty Shootout</title>
    <link rel="stylesheet" href="css/game.css">
</head>
<body>

<header class="hud">
    <div class="hud-brand">
        <div class="hud-kicker">PENALTY<span>.</span>SHOOTOUT</div>
        <div class="hud-meta">Arcade demo with quiz lifelines</div>
    </div>
    <div class="hud-score" aria-label="Match stats">
        <span class="hud-stat"><span class="hud-stat-label">Goals</span><b class="g" id="hud-goals">0</b></span>
        <span class="hud-stat"><span class="hud-stat-label">Saves</span><b class="g" id="hud-saves">0</b></span>
        <span class="hud-stat"><span class="hud-stat-label">Lifelines</span><b class="r" id="hud-quizzes">0</b></span>
    </div>
    <div class="hud-actions">
        <a href="leaderboard.php" class="hud-btn accent">Scores</a>
        <button type="button" class="hud-btn" onclick="logout()">Logout</button>
    </div>
</header>

<main id="game-area" aria-describedby="phase-label">
    <div id="phase-label" aria-live="polite">Kick: aim, lock, shoot.</div>

    <div id="result-flash" role="status" aria-live="polite" aria-atomic="true">
        <div id="result-word">GOAL!</div>
        <div id="result-sub"></div>
    </div>

    <div id="kick-panel">
        <div id="kick-goal-container">
            <div id="kick-goal-frame" tabindex="0" aria-label="Penalty goal area. Use arrow keys to aim, Enter to lock your shot, then hold Space to charge and release to shoot.">
                <div id="kick-aim"><div class="aim-ring"></div></div>
                <div id="kick-keeper"></div>
                <div id="kick-ball"></div>
            </div>
        </div>
        <div id="kick-aim-lock-msg" class="inst-msg">Locked. Hold <kbd>SPACE</kbd>, then release to shoot.</div>
        <div id="power-wrap">
            <div id="power-label">Power</div>
            <div id="power-track"><div id="power-fill"></div></div>
        </div>
    </div>

    <div id="goalie-panel">
        <div id="goalie-goal-container">
            <div id="goalie-goal-frame" tabindex="0" aria-label="Goalkeeper area. Click inside the goal or use arrow keys to choose a dive target, then press Enter to lock it before the shot.">
                <div id="goalie-keeper"></div>
                <div id="goalie-ai-ball"></div>
                <div id="goalie-cursor"></div>
            </div>
        </div>
        <div id="goalie-lock-msg" class="inst-msg">Dive locked. Shot in <span id="goalie-countdown">3</span>.</div>
    </div>
</main>

<div id="quiz-modal" role="dialog" aria-modal="true" aria-labelledby="quiz-title" aria-describedby="quiz-q" aria-hidden="true">
    <div class="quiz-card">
        <div class="quiz-top">
            <span class="quiz-tag" id="quiz-title">Quiz lifeline</span>
            <div class="quiz-hint">Answer correctly to keep the run alive.</div>
        </div>
        <div class="quiz-body">
            <div class="quiz-q" id="quiz-q"></div>
            <div class="quiz-opts" id="quiz-opts" role="group" aria-label="Quiz answers"></div>
            <div class="quiz-result" id="quiz-result" aria-live="polite"></div>
        </div>
        <button id="quiz-continue" type="button">Continue</button>
    </div>
</div>

<div id="gameover-modal" role="dialog" aria-modal="true" aria-labelledby="go-title" aria-describedby="go-summary" aria-hidden="true">
    <div class="go-card">
        <div class="go-top">
            <div class="go-label">Session complete</div>
            <div class="go-title" id="go-title">Game over</div>
        </div>
        <div class="go-body">
            <div class="go-stats" id="go-summary">
                <div class="go-stat"><div class="go-stat-n" id="go-goals">0</div><div class="go-stat-l">Goals</div></div>
                <div class="go-stat"><div class="go-stat-n" id="go-saves">0</div><div class="go-stat-l">Saves</div></div>
                <div class="go-stat"><div class="go-stat-n" id="go-conceded">0</div><div class="go-stat-l">Conceded</div></div>
                <div class="go-stat"><div class="go-stat-n" id="go-quizzes">0</div><div class="go-stat-l">Lifelines</div></div>
            </div>
            <div class="go-btns">
                <button class="go-btn-primary" id="btn-play-again" type="button">Play again</button>
                <a href="leaderboard.php" class="go-btn-secondary">Leaderboard</a>
            </div>
        </div>
    </div>
</div>

<script src="js/game.js"></script>
</body>
</html>
