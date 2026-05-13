// game.js - Penalty Shootout

let DIFFICULTY = 'medium';
const PREDICT = { easy: 0.30, medium: 0.50, hard: 0.75 };
const POST = 8;
const KEYBOARD_STEP = 18;
const BALL_TRAVEL_MS = 620;
const BALL_RESOLVE_MS = 700;
const GOAL_MOUTH_X_INSET = 0.085;
const GOAL_MOUTH_TOP_INSET = 0.12;
const GOAL_MOUTH_BOTTOM_INSET = 0.02;
const KEEPER_CORNER_BIAS = 0.04;
const KEEPER_SPRITES = {
    center: 'img/keeper.png',
    left: 'img/keeper-left.png',
    topLeft: 'img/keeper-top-left.png',
    topRight: 'img/keeper-top-right.png',
    right: 'img/keeper-right.png',
};
const KEEPER_POSES = ['left', 'topLeft', 'center', 'topRight', 'right'];
const KEEPER_POSE_TARGETS = {
    left: { x: 1 / 6, y: 0.58 },
    topLeft: { x: 1 / 6, y: 0.83 },
    center: { x: 1 / 2, y: 0.46 },
    topRight: { x: 5 / 6, y: 0.83 },
    right: { x: 5 / 6, y: 0.58 },
};

const S = {
    phase: 'kick',
    goalsScored: 0,
    shotsSaved: 0,
    goalsConceeded: 0,
    quizzesUsed: 0,
    seenQs: [],
    aimLocked: false,
    lockedX: 0,
    lockedY: 0,
    aimX: 0,
    aimY: 0,
    power: 0,
    powerDir: 1,
    charging: false,
    shotFired: false,
    keeperLocked: false,
    keeperX: 0,
    keeperPreviewX: 0,
    keeperPreviewY: 0,
    keeperPreviewPose: 'center',
    lockedKeeperDive: 'center',
    aiShotZone: 'left',
};

const $ = id => document.getElementById(id);

const kickPanel = $('kick-panel'), goaliePanel = $('goalie-panel');
const kickFrame = $('kick-goal-frame'), goalieFrame = $('goalie-goal-frame');
const kickAim = $('kick-aim'), kickAimMsg = $('kick-aim-lock-msg');
const kickBall = $('kick-ball'), kickKeeper = $('kick-keeper');
const powerWrap = $('power-wrap'), powerFill = $('power-fill');
const phaseLabel = $('phase-label'), resultFlash = $('result-flash');
const resultWord = $('result-word'), resultSub = $('result-sub');
const goalieKeeper = $('goalie-keeper'), goalieCursor = $('goalie-cursor');
const goalieAiBall = $('goalie-ai-ball'), goalieCountdown = $('goalie-countdown');
const goalieLockMsg = $('goalie-lock-msg');
const quizModal = $('quiz-modal'), quizQ = $('quiz-q');
const quizOpts = $('quiz-opts'), quizResult = $('quiz-result');
const quizContinue = $('quiz-continue'), gameoverModal = $('gameover-modal');
const hudGoals = $('hud-goals'), hudSaves = $('hud-saves');
const hudQuizzes = $('hud-quizzes');

let cdTimer = null, aiScheduled = false;
let curQuestion = null, quizCtx = '';
let activeDialog = null;
let lastFocus = null;

async function init() {
    preloadKeeperSprites();
    try {
        const d = await fetch('api/game.php?action=get_settings').then(r => r.json());
        if (d.success) DIFFICULTY = d.goalie_difficulty;
    } catch {}
    updateHUD();
    startKick();
}

function updateHUD() {
    hudGoals.textContent = S.goalsScored;
    hudSaves.textContent = S.shotsSaved;
    hudQuizzes.textContent = S.quizzesUsed;
}

function startKick() {
    S.phase = 'kick';
    S.aimLocked = false;
    S.shotFired = false;
    S.charging = false;
    S.power = 0;
    S.powerDir = 1;

    phaseLabel.textContent = 'Kick: aim, lock, shoot.';
    kickPanel.style.display = 'flex';
    goaliePanel.style.display = 'none';

    kickAim.style.display = 'block';
    kickAim.classList.remove('locked');
    kickAimMsg.style.display = 'none';
    powerWrap.style.display = 'none';
    setPower(5);

    resetKickBall();
    const metrics = frameMetrics(kickFrame);
    setKickAim(metrics.width / 2, Math.max(48, metrics.height * 0.35));
    setKeeperPose(kickKeeper, 'center');
    setKeeperPositionForPose(kickKeeper, metrics.width, 'center');
    kickFrame.style.cursor = 'crosshair';
    kickFrame.focus();

    kickFrame.addEventListener('pointermove', onKickMove);
    kickFrame.addEventListener('pointerdown', onKickClick);
}

function onKickMove(e) {
    if (S.aimLocked || S.shotFired) return;
    const r = kickFrame.getBoundingClientRect();
    setKickAim(e.clientX - r.left, r.height - (e.clientY - r.top));
}

function onKickClick(e) {
    if (S.aimLocked || S.shotFired) return;
    const r = kickFrame.getBoundingClientRect();
    setKickAim(e.clientX - r.left, r.height - (e.clientY - r.top));
    S.lockedX = S.aimX;
    S.lockedY = S.aimY;
    S.aimLocked = true;

    kickAim.classList.add('locked');
    kickFrame.removeEventListener('pointermove', onKickMove);
    kickFrame.removeEventListener('pointerdown', onKickClick);
    kickFrame.style.cursor = 'default';

    kickAimMsg.style.display = 'block';
    powerWrap.style.display = 'flex';

    (function tick() {
        if (!S.aimLocked || S.shotFired) return;
        if (S.charging) {
            S.power += S.powerDir * 1.2;
            if (S.power >= 100) { S.power = 100; S.powerDir = -1; }
            if (S.power <= 5) { S.power = 5; S.powerDir = 1; }
            setPower(S.power);
        }
        requestAnimationFrame(tick);
    })();
}

function executeKick() {
    const { width, height } = frameMetrics(kickFrame);
    const inPost = isKickInsideGoal(S.lockedX, S.lockedY, width, height);
    const shotPose = keeperPoseFromShot(S.lockedX, S.lockedY, width, height);
    const keeperPose = aiKeeperDecision(shotPose);

    setKeeperPose(kickKeeper, keeperPose);
    setKeeperPositionForPose(kickKeeper, width, keeperPose);
    animateBall(kickBall, kickFrame, S.lockedX, S.lockedY, -20, 0.6);

    setTimeout(() => {
        if (!inPost) {
            flash('MISS', 'var(--muted)', 'Off target. Quiz lifeline.', () => triggerQuiz('kick_miss'));
            return;
        }
        const isGoal = shotPose !== keeperPose;
        if (isGoal) {
            S.goalsScored++;
            updateHUD();
            flash('GOAL', 'var(--accent)', '+1 goal. You stay on attack.', () => startKick());
        } else {
            flash('SAVED', 'var(--danger)', 'Keeper got there. Quiz lifeline.', () => triggerQuiz('kick_miss'));
        }
    }, BALL_RESOLVE_MS);
}

function resetKickBall() {
    kickBall.style.cssText = 'display:none;transition:none;left:50%;bottom:-20px;transform:translateX(-50%) translate3d(0,0,0) scale(1) rotate(0deg)';
}

function startGoalie() {
    S.phase = 'goalie';
    S.keeperLocked = false;
    S.lockedKeeperDive = 'center';
    S.keeperPreviewPose = 'center';
    aiScheduled = false;

    phaseLabel.textContent = 'Save: choose a dive target, then lock it.';
    kickPanel.style.display = 'none';
    goaliePanel.style.display = 'flex';

    const metrics = frameMetrics(goalieFrame);
    goalieKeeper.style.left = '0';
    goalieKeeper.style.transition = 'transform .18s ease-out';
    setKeeperPose(goalieKeeper, 'center');
    setKeeperPositionForPose(goalieKeeper, metrics.width, 'center');
    goalieAiBall.style.display = 'none';
    goalieCountdown.textContent = '';
    goalieLockMsg.style.display = 'none';
    goalieFrame.style.cursor = 'crosshair';
    goalieFrame.focus();

    setGoaliePreviewFromPose('center', metrics.width, metrics.height);
    showGoalieCursor(true);
    goalieCursor.classList.remove('locked');

    goalieFrame.addEventListener('pointermove', onGoalieMove);
    goalieFrame.addEventListener('pointerdown', onGoalieClick);
    goalieFrame.addEventListener('pointerenter', onGoalieEnter);
    goalieFrame.addEventListener('pointerleave', onGoalieLeave);
}

function onGoalieEnter() {
    showGoalieCursor(true);
}

function onGoalieLeave() {
    if (!S.keeperLocked) showGoalieCursor(false);
}

function onGoalieMove(e) {
    if (S.keeperLocked) return;
    const r = goalieFrame.getBoundingClientRect();
    setGoalieCursorPosition(e.clientX - r.left, e.clientY - r.top);
}

function onGoalieClick(e) {
    if (S.keeperLocked) return;
    const r = goalieFrame.getBoundingClientRect();
    const clickX = e.clientX - r.left;
    const clickY = e.clientY - r.top;
    const pose = keeperPoseFromPoint(clickX, clickY, r.width, r.height);
    lockGoalieDive(pose, r.width, r.height, clickX, clickY);
}

function lockGoalieDive(pose, width, height, cursorX, cursorY) {
    S.lockedKeeperDive = pose;
    S.keeperPreviewPose = pose;
    S.keeperLocked = true;

    if (typeof cursorX === 'number' && typeof cursorY === 'number') {
        setGoalieCursorPosition(cursorX, cursorY);
    } else {
        setGoaliePreviewFromPose(pose, width, height);
    }
    showGoalieCursor(true);
    goalieCursor.classList.add('locked');
    goalieFrame.removeEventListener('pointermove', onGoalieMove);
    goalieFrame.removeEventListener('pointerdown', onGoalieClick);
    goalieFrame.style.cursor = 'default';
    goalieLockMsg.style.display = 'block';

    let n = 3;
    goalieCountdown.textContent = n;
    clearInterval(cdTimer);
    cdTimer = setInterval(() => {
        n--;
        if (n > 0) {
            goalieCountdown.textContent = n;
        } else {
            clearInterval(cdTimer);
            goalieCountdown.textContent = '!';
            fireAI();
        }
    }, 1000);
}

function fireAI() {
    if (aiScheduled) return;
    aiScheduled = true;
    if (!S.keeperLocked) {
        const { width, height } = frameMetrics(goalieFrame);
        lockGoalieDive(S.keeperPreviewPose || 'center', width, height);
    }
    const { width, height } = frameMetrics(goalieFrame);
    S.aiShotZone = KEEPER_POSES[Math.floor(Math.random() * KEEPER_POSES.length)];
    const isSave = S.lockedKeeperDive === S.aiShotZone;
    const target = targetPointForPose(S.aiShotZone, width, height);

    setKeeperPose(goalieKeeper, S.lockedKeeperDive);
    setKeeperPositionForPose(goalieKeeper, width, S.lockedKeeperDive);
    animateBall(goalieAiBall, goalieFrame, target.x, target.y, -30, 0.65);

    setTimeout(() => {
        showGoalieCursor(false);
        goalieCursor.classList.remove('locked');
        if (isSave) {
            S.shotsSaved++;
            updateHUD();
            flash('SAVE', 'var(--accent)', '+1 save. Your turn to shoot.', () => startKick());
        } else {
            S.goalsConceeded++;
            flash('GOAL', 'var(--danger)', 'They scored. Quiz lifeline.', () => triggerQuiz('goalie_miss'));
        }
    }, BALL_RESOLVE_MS);
}

function flash(word, color, sub, cb) {
    resultWord.textContent = word;
    resultWord.style.color = color;
    resultSub.textContent = sub;
    resultFlash.classList.add('show');
    setTimeout(() => {
        resultFlash.classList.remove('show');
        setTimeout(cb, 220);
    }, 1400);
}

async function triggerQuiz(ctx) {
    quizCtx = ctx;
    S.phase = 'quiz';
    S.quizzesUsed++;
    updateHUD();
    openDialog(quizModal);
    quizQ.textContent = 'Loading...';
    quizOpts.innerHTML = '';
    quizResult.style.display = 'none';
    quizContinue.style.display = 'none';
    try {
        const body = new FormData();
        body.append('action', 'get_quiz');
        body.append('exclude', S.seenQs.join(','));
        const d = await fetch('api/game.php', { method: 'POST', body }).then(r => r.json());
        if (!d.success) {
            quizQ.textContent = d.error || 'No questions available.';
            return;
        }
        curQuestion = d.question;
        S.seenQs.push(curQuestion.id);
        quizQ.textContent = curQuestion.question;
        quizOpts.innerHTML = '';
        ['a', 'b', 'c', 'd'].forEach(l => {
            const el = document.createElement('button');
            el.className = 'quiz-opt';
            el.dataset.answer = l;
            el.type = 'button';
            el.innerHTML = `<span class="opt-key">${l.toUpperCase()}</span>${curQuestion['option_' + l]}`;
            el.addEventListener('click', () => submitAnswer(l, el));
            quizOpts.appendChild(el);
        });
        quizOpts.querySelector('.quiz-opt')?.focus();
    } catch {
        quizQ.textContent = 'Failed to load question.';
    }
}

async function submitAnswer(ans, el) {
    document.querySelectorAll('.quiz-opt').forEach(o => o.disabled = true);
    const body = new FormData();
    body.append('action', 'check_answer');
    body.append('question_id', curQuestion.id);
    body.append('answer', ans);
    const d = await fetch('api/game.php', { method: 'POST', body }).then(r => r.json());
    el.classList.add(d.correct ? 'correct' : 'wrong');
    if (!d.correct) {
        document.querySelectorAll('.quiz-opt').forEach(o => {
            if (o.dataset.answer === d.correct_answer) o.classList.add('reveal');
        });
    }
    quizResult.style.display = 'block';
    if (d.correct) {
        quizResult.className = 'quiz-result win';
        quizResult.textContent = quizCtx === 'kick_miss' ? 'Correct. Shoot again.' : 'Correct. Stay in goal.';
        quizContinue.style.display = 'block';
        quizContinue.textContent = 'Continue';
        quizContinue.onclick = () => {
            closeDialog(quizModal);
            quizCtx === 'kick_miss' ? startKick() : startGoalie();
        };
    } else {
        quizResult.className = 'quiz-result lose';
        quizResult.textContent = quizCtx === 'kick_miss' ? 'Wrong. You switch to goal.' : 'Wrong. Run over.';
        quizContinue.style.display = 'block';
        quizContinue.textContent = quizCtx === 'kick_miss' ? 'Go to goal' : 'See score';
        quizContinue.onclick = () => {
            closeDialog(quizModal);
            quizCtx === 'kick_miss' ? startGoalie() : endGame();
        };
    }
    quizContinue.focus();
}

async function endGame() {
    S.phase = 'over';
    kickPanel.style.display = goaliePanel.style.display = 'none';
    try {
        const body = new FormData();
        body.append('action', 'save_score');
        body.append('goals_scored', S.goalsScored);
        body.append('goals_saved', S.shotsSaved);
        body.append('goals_conceded', S.goalsConceeded);
        body.append('lifelines_used', S.quizzesUsed);
        await fetch('api/game.php', { method: 'POST', body });
    } catch {}

    const total = S.goalsScored + S.shotsSaved;
    $('go-title').textContent = total >= 12 ? 'Outstanding' : total >= 6 ? 'Strong run' : 'Game over';
    $('go-goals').textContent = S.goalsScored;
    $('go-saves').textContent = S.shotsSaved;
    $('go-conceded').textContent = S.goalsConceeded;
    $('go-quizzes').textContent = S.quizzesUsed;
    openDialog(gameoverModal, $('btn-play-again'));
}

$('btn-play-again').addEventListener('click', () => {
    closeDialog(gameoverModal);
    Object.assign(S, {
        phase: 'kick',
        goalsScored: 0,
        shotsSaved: 0,
        goalsConceeded: 0,
        quizzesUsed: 0,
        seenQs: [],
        aimLocked: false,
        lockedX: 0,
        lockedY: 0,
        aimX: 0,
        aimY: 0,
        power: 0,
        powerDir: 1,
        charging: false,
        shotFired: false,
        keeperLocked: false,
        keeperX: 0,
        keeperPreviewX: 0,
        keeperPreviewY: 0,
        keeperPreviewPose: 'center',
        lockedKeeperDive: 'center',
        aiShotZone: 'left',
    });
    updateHUD();
    startKick();
});

document.addEventListener('keydown', e => {
    if (activeDialog && e.key === 'Escape' && activeDialog === gameoverModal) {
        closeDialog(gameoverModal);
        return;
    }
    if (S.phase === 'kick' && document.activeElement === kickFrame && !S.aimLocked && ['ArrowUp', 'ArrowDown', 'ArrowLeft', 'ArrowRight', 'Enter'].includes(e.key)) {
        e.preventDefault();
        if (e.key === 'Enter') {
            const r = kickFrame.getBoundingClientRect();
            onKickClick({ clientX: r.left + S.aimX, clientY: r.bottom - S.aimY });
            return;
        }
        nudgeKickAim(e.key);
        return;
    }
    if (S.phase === 'goalie' && document.activeElement === goalieFrame && !S.keeperLocked && ['ArrowUp', 'ArrowDown', 'ArrowLeft', 'ArrowRight', 'Enter'].includes(e.key)) {
        e.preventDefault();
        if (e.key === 'Enter') {
            const metrics = frameMetrics(goalieFrame);
            lockGoalieDive(S.keeperPreviewPose, metrics.width, metrics.height);
            return;
        }
        nudgeKeeperSelection(e.key);
        return;
    }
    if (e.code !== 'Space') return;
    e.preventDefault();
    if (S.phase === 'kick' && S.aimLocked && !S.shotFired) S.charging = true;
});

document.addEventListener('keyup', e => {
    if (e.code !== 'Space') return;
    if (S.phase !== 'kick' || !S.aimLocked || S.shotFired || !S.charging) return;
    S.charging = false;
    S.shotFired = true;
    executeKick();
});

function frameMetrics(frame) {
    const rect = frame.getBoundingClientRect();
    return { width: rect.width, height: rect.height };
}

function isKickInsideGoal(x, yFromBottom, width, height) {
    const xInset = Math.max(POST, width * GOAL_MOUTH_X_INSET);
    const topLimit = height * (1 - GOAL_MOUTH_TOP_INSET);
    const bottomLimit = Math.max(POST, height * GOAL_MOUTH_BOTTOM_INSET);
    return x > xInset && x < (width - xInset) &&
        yFromBottom > bottomLimit && yFromBottom < topLimit;
}

function clamp(n, min, max) {
    return Math.max(min, Math.min(n, max));
}

function zoneCenterX(zoneName, width) {
    const target = KEEPER_POSE_TARGETS[zoneName] || KEEPER_POSE_TARGETS.center;
    return width * target.x;
}

function targetPointForPose(pose, width, height) {
    const target = KEEPER_POSE_TARGETS[pose] || KEEPER_POSE_TARGETS.center;
    return { x: width * target.x, y: height * target.y };
}

function keeperWidth(el) {
    return el.getBoundingClientRect().width || 56;
}

function setPower(value) {
    powerFill.style.transform = `scaleX(${value / 100})`;
}

function setKickAim(x, y) {
    const { width, height } = frameMetrics(kickFrame);
    S.aimX = clamp(x, 10, width - 10);
    S.aimY = clamp(y, 10, height - 10);
    kickAim.style.left = `${S.aimX}px`;
    kickAim.style.bottom = `${S.aimY}px`;
}

function setKeeperHorizontalPosition(el, frameWidth, x) {
    const max = Math.max(0, frameWidth - keeperWidth(el));
    const clamped = clamp(x, 0, max);
    S.keeperX = clamped;
    el.style.transform = `translateX(${clamped}px)`;
}

function setKeeperPositionForPose(el, frameWidth, pose) {
    const x = zoneCenterX(pose, frameWidth) - keeperWidth(el) / 2;
    setKeeperHorizontalPosition(el, frameWidth, x);
}

function setKeeperPose(el, pose) {
    const nextPose = KEEPER_SPRITES[pose] ? pose : 'center';
    el.dataset.pose = nextPose;
    el.style.backgroundImage = `url('${KEEPER_SPRITES[nextPose]}')`;
}

function showGoalieCursor(visible) {
    goalieCursor.style.display = visible ? 'block' : 'none';
}

function setGoalieCursorPosition(x, y) {
    S.keeperPreviewX = x;
    S.keeperPreviewY = y;
    goalieCursor.style.left = `${x}px`;
    goalieCursor.style.top = `${y}px`;
}

function setGoaliePreviewFromPose(pose, width, height) {
    const target = targetPointForPose(pose, width, height);
    S.keeperPreviewPose = pose;
    setGoalieCursorPosition(target.x, height - target.y);
}

function preloadKeeperSprites() {
    Object.values(KEEPER_SPRITES).forEach(src => {
        const img = new Image();
        img.decoding = 'async';
        img.src = src;
    });
}

function keeperHorizontalZone(x, width) {
    const xInset = Math.max(POST, width * GOAL_MOUTH_X_INSET);
    const playableWidth = Math.max(1, width - (xInset * 2));
    const leftBoundary = xInset + playableWidth / 3;
    const rightBoundary = width - xInset - playableWidth / 3;

    if (x <= leftBoundary) return 'left';
    if (x >= rightBoundary) return 'right';
    return 'center';
}

function keeperPoseFromShot(x, yFromBottom, width, height) {
    const side = keeperHorizontalZone(x, width);
    if (side === 'center') return 'center';

    const sidePose = side;
    const topPose = side === 'left' ? 'topLeft' : 'topRight';
    const sideTarget = targetPointForPose(sidePose, width, height);
    const topTarget = targetPointForPose(topPose, width, height);
    const splitY = ((sideTarget.y + topTarget.y) / 2) - (height * KEEPER_CORNER_BIAS);

    return yFromBottom >= splitY ? topPose : sidePose;
}

function keeperPoseFromPoint(xFromLeft, yFromTop, width, height) {
    return keeperPoseFromShot(xFromLeft, height - yFromTop, width, height);
}

function ballRadius(el) {
    const rect = el.getBoundingClientRect();
    if (rect.height) return rect.height / 2;

    const computedHeight = parseFloat(getComputedStyle(el).height);
    return Number.isFinite(computedHeight) ? computedHeight / 2 : 12;
}

function animateBall(el, frame, targetX, targetY, startBottom, scale) {
    const { width } = frameMetrics(frame);
    const startX = width / 2;
    const dx = targetX - startX;
    el.style.cssText = `display:block;transition:none;left:50%;bottom:${startBottom}px;opacity:1;transform:translateX(-50%) translate3d(0,0,0) scale(1) rotate(0deg)`;
    const dy = (targetY - ballRadius(el)) - startBottom;
    requestAnimationFrame(() => {
        el.style.transition = `transform ${BALL_TRAVEL_MS}ms ease-out,opacity ${BALL_TRAVEL_MS}ms`;
        el.style.transform = `translateX(-50%) translate3d(${dx}px, ${-dy}px, 0) scale(${scale}) rotate(540deg)`;
    });
}

function nudgeKickAim(key) {
    const delta = {
        ArrowLeft: [-KEYBOARD_STEP, 0],
        ArrowRight: [KEYBOARD_STEP, 0],
        ArrowUp: [0, KEYBOARD_STEP],
        ArrowDown: [0, -KEYBOARD_STEP],
    }[key];
    if (!delta) return;
    setKickAim(S.aimX + delta[0], S.aimY + delta[1]);
}

function nudgeKeeperSelection(key) {
    const nextPose = {
        center: { ArrowLeft: 'left', ArrowRight: 'right' },
        left: { ArrowRight: 'center', ArrowUp: 'topLeft' },
        topLeft: { ArrowDown: 'left', ArrowRight: 'center' },
        right: { ArrowLeft: 'center', ArrowUp: 'topRight' },
        topRight: { ArrowDown: 'right', ArrowLeft: 'center' },
    }[S.keeperPreviewPose]?.[key];

    if (!nextPose) return;
    const { width, height } = frameMetrics(goalieFrame);
    setGoaliePreviewFromPose(nextPose, width, height);
    showGoalieCursor(true);
}

function aiKeeperDecision(shotPose) {
    if (Math.random() < (PREDICT[DIFFICULTY] ?? 0.5)) return shotPose;
    const fallback = KEEPER_POSES.filter(pose => pose !== shotPose);
    return fallback[Math.floor(Math.random() * fallback.length)];
}

function openDialog(dialog, focusEl) {
    lastFocus = document.activeElement;
    activeDialog = dialog;
    dialog.classList.add('show');
    dialog.setAttribute('aria-hidden', 'false');
    (focusEl || dialog.querySelector('button, a, input, select, textarea'))?.focus();
}

function closeDialog(dialog) {
    dialog.classList.remove('show');
    dialog.setAttribute('aria-hidden', 'true');
    activeDialog = null;
    lastFocus?.focus?.();
}

function logout() {
    fetch('api/auth.php', { method: 'POST', body: new URLSearchParams({ action: 'logout' }) })
    .then(r => r.json()).then(d => window.location.href = d.redirect);
}

init();
