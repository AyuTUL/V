const ball = document.getElementById("ball");
const keeper = document.getElementById("keeper");
const aim = document.getElementById("aim");
const powerBar = document.getElementById("powerBar");

const scoreText = document.getElementById("score");
const roundText = document.getElementById("round");
const message = document.getElementById("message");

let score = 0;
let round = 1;
const maxRounds = 5;

let aimX = 265; // starting X of target inside goal
let aimY = 20;  // vertical position relative to bottom of goal
let power = 0;
let charging = false;
let powerDir = 1;

// Keyboard aiming
document.addEventListener("keydown", (e) => {
    if (e.code === "ArrowLeft") aimX -= 5;
    if (e.code === "ArrowRight") aimX += 5;
    if (e.code === "ArrowUp") aimY += 2;    // move up inside goal
    if (e.code === "ArrowDown") aimY -= 2;  // move down inside goal
    aimX = Math.max(0, Math.min(aimX, 530));
    aimY = Math.max(0, Math.min(aimY, 180));
    aim.style.left = aimX + "px";
    aim.style.bottom = aimY + "px";
});

// Power bar loop
setInterval(() => {
    if (charging) {
        power += powerDir * 2;
        if (power >= 100) powerDir = -1;
        if (power <= 10) powerDir = 1;
        powerBar.style.width = power + "%";
    }
}, 30);

// Shoot on SPACE release
document.addEventListener("keydown", (e) => {
    if (e.code === "Space") charging = true;
});

document.addEventListener("keyup", (e) => {
    if (e.code === "Space" && charging) {
        charging = false;
        shoot();
    }
});

function shoot() {
    if (round > maxRounds) return;

    // Random goalkeeper dive
    const zones = ["left", "center", "right"];
    const dive = zones[Math.floor(Math.random() * 3)];
    if (dive === "left") { keeper.src = "img/keeper-left.png"; keeper.style.left = "80px"; }
    if (dive === "center") { keeper.src = "img/keeper.png"; keeper.style.left = "235px"; }
    if (dive === "right") { keeper.src = "img/keeper-right.png"; keeper.style.left = "390px"; }

    // Animate ball toward aim
    ball.style.left = (aimX + 175) + "px"; // offset to align in goal
    ball.style.bottom = (aimY + power / 3 + 60) + "px";

    setTimeout(() => {
        // Determine save or goal (simple zones)
        let shotZone;
        if (aimX < 180) shotZone = "left";
        else if (aimX < 360) shotZone = "center";
        else shotZone = "right";

        if (shotZone === dive) {
            message.innerText = "🧤 SAVED!";
        } else {
            score++;
            scoreText.innerText = score;
            message.innerText = "⚽ GOAL!";
        }

        // Reset ball and keeper
        ball.style.left = "430px";
        ball.style.bottom = "60px";
        keeper.src = "img/keeper.png";
        keeper.style.left = "235px";

        // Next round
        round++;
        roundText.innerText = round > maxRounds ? maxRounds : round;

        if (round > maxRounds) {
            message.innerText = "Game Over! Final Score: " + score;
        } else {
            message.innerText = "Use arrow keys to move aim. Hold SPACE to shoot!";
        }

    }, 500);
}