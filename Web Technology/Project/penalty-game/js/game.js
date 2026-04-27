// ============================================
// game.js — Full penalty shootout engine
// ============================================

const TOTAL_ROUNDS = 5;

// Difficulty settings from server
let GOALIE_DIFFICULTY = 'medium'; // easy|medium|hard → reaction time of AI keeper

// Difficulty → AI keeper reaction speed (px per frame)
const DIFFICULTY_SPEED = { easy: 1.5, medium: 3.5, hard: 7 };
// Difficulty → probability AI keeper correctly predicts zone
const DIFFICULTY_PREDICT = { easy: 0.3, medium: 0.5, hard: 0.75 };

// ===== STATE =====
let state = {
    round:         1,
    phase:         'kick',   // 'kick' | 'save' | 'done'
    kickScore:     0,        // player goals scored
    saveScore:     0,        // player saves made
    lifelinesUsed: 0,
    roundDots:     [],       // 'pending'|'goal'|'miss' per round
    power:         0,
    powerDir:      1,
    powerRunning:  false,
    shotFired:     false,
    saveDone:      false,
    aimX:          280,      // inside goal (0–560)
    aimY:          60,       // from bottom (0–230)
    seenQuestions: [],
    animFrame:     null,
};

// ===== DOM REFS =====
const $ = id => document.getElementById(id);

const phaseLabel      = $('phase-label');
const aimIndicator    = $('aim-indicator');
const powerFill       = $('power-fill');
const shootBtn        = $('shoot-btn');
const ball            = $('ball');
const keeper          = $('keeper');
const resultFlash     = $('result-flash');
const resultEmoji     = $('result-emoji');
const resultText      = $('result-text');
const resultSub       = $('result-sub');
const quizModal       = $('quiz-modal');
const quizQuestion    = $('quiz-question');
const quizOptions     = $('quiz-options');
const quizResult      = $('quiz-result');
const quizContinue    = $('quiz-continue');
const gameoverModal   = $('gameover-modal');
const saveArea        = $('save-area');
const saveGoalFrame   = $('save-goal-frame');
const saveKeeper      = $('save-keeper');
const aiBall          = $('ai-ball');
const saveCursor      = $('save-cursor');

// HUD
const hudKick    = $('hud-kick');
const hudSave    = $('hud-save');
const hudRound   = $('hud-round');
const hudLifeline= $('hud-lifeline');

// ===== INIT =====
async function init() {
    try {
        const res = await fetch('../api/game.php?action=get_settings');
        const data = await res.json();
        if (data.success) GOALIE_DIFFICULTY = data.goalie_difficulty;
    } catch (e) { /* use default */ }

    buildRoundDots();
    updateHUD();
    startKickPhase();
}

// ===== ROUND DOTS =====
function buildRoundDots() {
    const tracker = $('round-tracker');
    tracker.innerHTML = '';
    for (let i = 0; i < TOTAL_ROUNDS; i++) {
        const dot = document.createElement('div');
        dot.className = 'round-dot' + (i === 0 ? ' active' : '');
        dot.id = `dot-${i}`;
        tracker.appendChild(dot);
    }
}

function setDot(round, status) {
    const dot = $(`dot-${round - 1}`);
    if (!dot) return;
    dot.className = 'round-dot';
    if (status === 'goal') dot.classList.add('kick-scored');
    if (status === 'miss') dot.classList.add('kick-missed');
    if (status === 'active') dot.classList.add('active');
}

// ===== HUD =====
function updateHUD() {
    hudKick.textContent     = state.kickScore;
    hudSave.textContent     = state.saveScore;
    hudRound.textContent    = `${Math.min(state.round, TOTAL_ROUNDS)}/${TOTAL_ROUNDS}`;
    hudLifeline.textContent = state.lifelinesUsed;
}

// ============================================================
// =====================  KICK PHASE  ========================
// ============================================================
function startKickPhase() {
    state.phase      = 'kick';
    state.shotFired  = false;
    state.power      = 0;
    state.powerDir   = 1;

    phaseLabel.textContent = '⚽ YOUR TURN — SHOOT';

    // Show goal + ball, hide save area
    $('goal-container').style.display = 'block';
    saveArea.style.display = 'none';
    shootBtn.style.display = 'block';
    $('power-wrap').style.display = 'flex';

    // Reset keeper position
    keeper.style.left = '240px';
    keeper.style.transform = 'translateX(0) scaleX(1)';

    // Reset ball
    resetBall();

    // Reset aim
    state.aimX = 280; state.aimY = 60;
    updateAim();

    // Set active dot
    if (state.round <= TOTAL_ROUNDS) setDot(state.round, 'active');

    // Start power oscillation
    state.powerRunning = true;
    runPower();

    // Bind shoot button
    shootBtn.onclick = null;
    shootBtn.onmousedown = startCharge;
    shootBtn.onmouseup   = releaseShoot;
    shootBtn.ontouchstart = (e) => { e.preventDefault(); startCharge(); };
    shootBtn.ontouchend   = (e) => { e.preventDefault(); releaseShoot(); };
    shootBtn.textContent  = 'HOLD TO CHARGE & RELEASE TO SHOOT';
}

function startCharge() {
    if (state.shotFired) return;
    state.powerRunning = true;
}

function releaseShoot() {
    if (state.shotFired) return;
    state.shotFired    = true;
    state.powerRunning = false;
    shootBtn.style.display = 'none';
    $('power-wrap').style.display = 'none';
    executeShot();
}

function runPower() {
    if (!state.powerRunning || state.shotFired) return;
    state.power += state.powerDir * 3;
    if (state.power >= 100) { state.power = 100; state.powerDir = -1; }
    if (state.power <= 5)   { state.power = 5;   state.powerDir = 1;  }
    powerFill.style.width = state.power + '%';
    requestAnimationFrame(runPower);
}

// ===== GOAL MOUSE AIMING =====
$('goal-frame').addEventListener('mousemove', (e) => {
    if (state.phase !== 'kick' || state.shotFired) return;
    const rect = $('goal-frame').getBoundingClientRect();
    state.aimX = e.clientX - rect.left;
    state.aimY = rect.height - (e.clientY - rect.top);
    state.aimX = Math.max(10, Math.min(state.aimX, 550));
    state.aimY = Math.max(5,  Math.min(state.aimY, 220));
    updateAim();
});

function updateAim() {
    aimIndicator.style.left   = state.aimX + 'px';
    aimIndicator.style.bottom = state.aimY + 'px';
}

// ===== EXECUTE SHOT =====
function executeShot() {
    // Determine shot zone
    const shotZone = getZone(state.aimX, 560);
    const keeperZone = aiKeeperDecision(shotZone);

    // Move keeper
    animateKeeperDive(keeperZone);

    // Animate ball flying into goal
    ball.style.transition = 'left 0.5s ease-out, bottom 0.5s ease-out, transform 0.5s, width 0.5s';
    ball.style.left   = (state.aimX - 175) + 'px';  // relative to goal-container offset
    ball.style.bottom = (state.aimY + 80) + 'px';
    ball.style.width  = '28px';
    ball.style.transform = 'rotate(360deg)';

    setTimeout(() => {
        const isGoal = shotZone !== keeperZone;
        showRoundResult('kick', isGoal);
    }, 550);
}

function getZone(x, width) {
    if (x < width / 3)       return 'left';
    if (x < (width * 2 / 3)) return 'center';
    return 'right';
}

function aiKeeperDecision(shotZone) {
    const prob = DIFFICULTY_PREDICT[GOALIE_DIFFICULTY] || 0.5;
    if (Math.random() < prob) return shotZone; // AI correctly guesses
    // Random wrong zone
    const zones = ['left', 'center', 'right'].filter(z => z !== shotZone);
    return zones[Math.floor(Math.random() * zones.length)];
}

function animateKeeperDive(zone) {
    const positions = { left: '60px', center: '240px', right: '420px' };
    keeper.style.left = positions[zone];
    if (zone === 'left')   keeper.style.transform = 'scaleX(-1)';
    if (zone === 'right')  keeper.style.transform = 'scaleX(1)';
    if (zone === 'center') keeper.style.transform = 'scaleX(1)';
}

function resetBall() {
    ball.style.transition = 'none';
    ball.style.left   = '50%';
    ball.style.transform = 'translateX(-50%)';
    ball.style.bottom = '30px';
    ball.style.width  = '44px';
}

// ============================================================
// =====================  SAVE PHASE  ========================
// ============================================================
function startSavePhase() {
    state.phase    = 'save';
    state.saveDone = false;

    phaseLabel.textContent = '🧤 SAVE THE SHOT — CLICK TO DIVE';

    $('goal-container').style.display = 'none';
    saveArea.style.display = 'flex';
    $('power-wrap').style.display = 'none';
    shootBtn.style.display = 'none';

    // Reset save keeper
    saveKeeper.style.left   = '50%';
    saveKeeper.style.transform = 'translateX(-50%)';
    aiBall.style.display = 'none';

    // Keeper follows mouse inside save-goal-frame
    saveGoalFrame.addEventListener('mousemove', onSaveMouseMove);
    saveGoalFrame.addEventListener('click', onSaveDive);

    // Cursor
    saveGoalFrame.addEventListener('mouseenter', () => { saveCursor.style.display = 'block'; });
    saveGoalFrame.addEventListener('mouseleave', () => { saveCursor.style.display = 'none'; });

    // AI shot fires after 1.5s
    setTimeout(fireAIShot, 1500);
}

let saveKeeperX = 280; // current pixel position of save keeper center

function onSaveMouseMove(e) {
    if (state.saveDone) return;
    const rect = saveGoalFrame.getBoundingClientRect();
    const x = e.clientX - rect.left;
    const y = e.clientY - rect.top;

    // Keeper follows mouse (center on mouse)
    saveKeeperX = Math.max(0, Math.min(x - 40, 480));
    saveKeeper.style.left      = saveKeeperX + 'px';
    saveKeeper.style.transform = 'none';

    saveCursor.style.left = x + 'px';
    saveCursor.style.top  = y + 'px';
}

function onSaveDive(e) {
    if (state.saveDone) return;
    state.saveDone = true;

    saveGoalFrame.removeEventListener('mousemove', onSaveMouseMove);
    saveGoalFrame.removeEventListener('click', onSaveDive);
    saveCursor.style.display = 'none';

    // Record where keeper is when clicked → zone
    const keeperCenter = saveKeeperX + 40;
    state.savedZone = getZone(keeperCenter, 560);
}

let aiShotZone = 'left';

function fireAIShot() {
    // AI picks a zone
    const zones = ['left', 'center', 'right'];
    aiShotZone = zones[Math.floor(Math.random() * zones.length)];

    const targetX = { left: 80, center: 280, right: 440 };
    const targetY = { left: 120, center: 80, right: 120 };

    // Show ball and animate
    aiBall.style.display = 'block';
    aiBall.style.transition = 'none';
    aiBall.style.left   = '50%';
    aiBall.style.bottom = '-30px';
    aiBall.style.transform = 'translateX(-50%)';

    requestAnimationFrame(() => {
        aiBall.style.transition = 'all 0.5s ease-out';
        aiBall.style.left   = targetX[aiShotZone] + 'px';
        aiBall.style.bottom = targetY[aiShotZone] + 'px';
        aiBall.style.transform = 'none';
    });

    setTimeout(() => {
        // If player hasn't clicked yet → auto-check based on keeper position
        const saveZone = state.savedZone || getZone(saveKeeperX + 40, 560);
        const isSave   = (saveZone === aiShotZone);
        showRoundResult('save', isSave);
    }, 600);
}

// ============================================================
// ===================  ROUND RESULTS  =======================
// ============================================================
function showRoundResult(type, success) {
    let emoji, text, color, sub;

    if (type === 'kick') {
        if (success) {
            emoji = '⚽'; text = 'GOAL!'; color = '#00c853';
            sub   = '+10 points';
            state.kickScore++;
            setDot(state.round, 'goal');
        } else {
            emoji = '🧤'; text = 'SAVED!'; color = '#ff3d3d';
            sub   = 'Quiz lifeline available!';
            setDot(state.round, 'miss');
        }
    } else {
        if (success) {
            emoji = '🧤'; text = 'GREAT SAVE!'; color = '#1de9b6';
            sub   = '+8 points';
            state.saveScore++;
        } else {
            emoji = '😬'; text = 'GOAL CONCEDED'; color = '#ff3d3d';
            sub   = '';
        }
    }

    resultEmoji.textContent = emoji;
    resultText.textContent  = text;
    resultText.style.color  = color;
    resultSub.textContent   = sub;
    resultFlash.classList.add('show');

    updateHUD();

    if (type === 'kick' && !success) {
        // Offer quiz lifeline
        setTimeout(() => {
            resultFlash.classList.remove('show');
            showQuiz();
        }, 1200);
    } else {
        setTimeout(() => {
            resultFlash.classList.remove('show');
            advanceRound(type);
        }, 1600);
    }
}

function advanceRound(completedPhase) {
    if (completedPhase === 'kick') {
        startSavePhase();
    } else {
        // Both kick and save done → next round
        state.round++;
        if (state.round > TOTAL_ROUNDS) {
            endGame();
        } else {
            updateHUD();
            startKickPhase();
        }
    }
}

// ============================================================
// ====================  QUIZ LIFELINE  ======================
// ============================================================
let currentQuestion = null;

async function showQuiz() {
    quizModal.classList.add('show');
    quizOptions.innerHTML = '<div style="color:var(--muted);text-align:center;padding:20px">Loading question...</div>';
    quizResult.style.display = 'none';
    quizContinue.style.display = 'none';

    try {
        const body = new FormData();
        body.append('action', 'get_quiz');
        body.append('exclude', state.seenQuestions.join(','));

        const res  = await fetch('../api/game.php', { method: 'POST', body });
        const data = await res.json();

        if (!data.success) {
            quizOptions.innerHTML = `<div style="color:var(--red)">${data.error}</div>`;
            return;
        }

        currentQuestion = data.question;
        state.seenQuestions.push(currentQuestion.id);

        quizQuestion.textContent = currentQuestion.question;
        quizOptions.innerHTML = '';

        ['a','b','c','d'].forEach(letter => {
            const opt = document.createElement('div');
            opt.className = 'quiz-opt';
            opt.dataset.answer = letter;
            opt.innerHTML = `<span class="opt-letter">${letter.toUpperCase()}</span> ${currentQuestion['option_' + letter]}`;
            opt.addEventListener('click', () => submitAnswer(letter, opt));
            quizOptions.appendChild(opt);
        });
    } catch (e) {
        quizOptions.innerHTML = `<div style="color:var(--red)">Failed to load question.</div>`;
    }
}

async function submitAnswer(answer, clickedEl) {
    // Disable all options
    document.querySelectorAll('.quiz-opt').forEach(o => {
        o.style.pointerEvents = 'none';
    });

    state.lifelinesUsed++;
    updateHUD();

    const body = new FormData();
    body.append('action', 'check_answer');
    body.append('question_id', currentQuestion.id);
    body.append('answer', answer);

    const res  = await fetch('../api/game.php', { method: 'POST', body });
    const data = await res.json();

    clickedEl.classList.add(data.correct ? 'correct' : 'wrong');

    if (!data.correct) {
        // Reveal correct answer
        document.querySelectorAll('.quiz-opt').forEach(o => {
            if (o.dataset.answer === data.correct_answer) o.classList.add('reveal');
        });
    }

    quizResult.style.display = 'block';
    quizResult.className = 'quiz-result ' + (data.correct ? 'win' : 'lose');
    quizResult.textContent = data.correct
        ? '✅ CORRECT! You earned a lifeline — shot counts as saved!'
        : '❌ WRONG! The miss stands. Better luck next time.';

    quizContinue.style.display = 'block';
    quizContinue.textContent   = 'CONTINUE →';
    quizContinue.onclick = () => {
        quizModal.classList.remove('show');
        // If correct → treat as goal (grant the point)
        if (data.correct) {
            state.kickScore++;
            setDot(state.round, 'goal');
            updateHUD();
        }
        advanceRound('kick');
    };
}

// ============================================================
// ======================  GAME OVER  ========================
// ============================================================
async function endGame() {
    state.phase = 'done';

    // Save score to DB
    try {
        const body = new FormData();
        body.append('action',       'save_score');
        body.append('goals_scored', state.kickScore);
        body.append('goals_saved',  state.saveScore);
        body.append('rounds_played', TOTAL_ROUNDS);
        body.append('lifelines_used', state.lifelinesUsed);

        const res  = await fetch('../api/game.php', { method: 'POST', body });
        const data = await res.json();

        if (data.success) {
            $('final-score').textContent = data.final_score;
        }
    } catch (e) {
        $('final-score').textContent = (state.kickScore * 10) + (state.saveScore * 8);
    }

    $('go-goals-scored').textContent  = state.kickScore;
    $('go-goals-saved').textContent   = state.saveScore;
    $('go-lifelines').textContent     = state.lifelinesUsed;

    // Trophy
    const total = state.kickScore + state.saveScore;
    const trophy = total >= 8 ? '🏆' : total >= 5 ? '🥈' : '🥉';
    $('go-trophy').textContent = trophy;

    gameoverModal.classList.add('show');
}

// ===== PLAY AGAIN =====
$('btn-play-again').addEventListener('click', () => {
    gameoverModal.classList.remove('show');
    state = {
        round: 1, phase: 'kick',
        kickScore: 0, saveScore: 0, lifelinesUsed: 0,
        roundDots: [], power: 0, powerDir: 1,
        powerRunning: false, shotFired: false, saveDone: false,
        aimX: 280, aimY: 60,
        seenQuestions: [], animFrame: null,
    };
    buildRoundDots();
    updateHUD();
    startKickPhase();
});

// ===== START =====
init();
