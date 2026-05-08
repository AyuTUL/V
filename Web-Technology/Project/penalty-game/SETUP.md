# Penalty Shootout + Quiz System
## Setup Guide

---

## 1. FOLDER STRUCTURE

Copy the entire `penalty-game/` folder into your XAMPP `htdocs` directory:

```
C:/xampp/htdocs/penalty-game/
├── index.php           ← auto-redirects to login or game
├── login.php           ← user + admin login / register
├── game.php            ← main game (users only)
├── leaderboard.php     ← public leaderboard
├── logout.php
├── config.php          ← DB credentials (EDIT THIS)
├── api/
│   ├── auth.php
│   ├── game.php
│   └── admin.php
├── admin/
│   ├── index.php       ← admin dashboard
│   ├── questions.php   ← quiz CRUD
│   ├── settings.php    ← goalie difficulty
│   ├── scores.php      ← all scores view
│   └── sidebar.php
├── css/
│   ├── auth.css
│   ├── game.css
│   └── admin.css
├── js/
│   └── game.js
├── img/
│   ├── keeper.png       ← ADD YOUR IMAGES HERE
│   ├── ball.png
│   └── ...
└── db/
    └── schema.sql
```

---

## 2. DATABASE SETUP

1. Open phpMyAdmin: http://localhost/phpmyadmin
2. Click **Import** → select `db/schema.sql` → click **Go**
3. This creates the `penalty_game` database with:
   - `users` table (with seeded admin account)
   - `game_sessions` table
   - `quiz_questions` table (with 10 sample questions)
   - `settings` table (default: medium difficulty)

---

## 3. CONFIG EDIT

Open `config.php` and set your MySQL credentials:

```php
define('DB_HOST', 'localhost');
define('DB_USER', 'root');       // your MySQL username
define('DB_PASS', '');           // your MySQL password (blank for XAMPP default)
define('DB_NAME', 'penalty_game');
define('BASE_URL', 'http://localhost/penalty-game/');
```

---

## 4. DEFAULT ADMIN LOGIN

| Field    | Value      |
|----------|------------|
| Username | `admin`    |
| Password | `password` |

⚠️ **Change this immediately** via phpMyAdmin:
```sql
UPDATE users SET password_hash = '$2y$10$...' WHERE username = 'admin';
```
Or generate a new hash in PHP: `echo password_hash('your_new_password', PASSWORD_BCRYPT);`

---

## 5. IMAGE ASSETS

Place your game images in the `/img/` folder. See `img/readme.md` for details.

If you don't have images, the game still runs — keeper and ball areas will 
appear empty but all mechanics work. You can use emoji or colored boxes instead.

---

## 6. HOW TO PLAY

### As a Player:
1. Register an account on the login page
2. **Kick phase:** Move mouse inside the goal to aim, hold the shoot button to charge power, release to shoot
3. **Save phase:** Move mouse to position keeper, click to dive and save the AI's shot
4. **Lifeline:** If you miss, a football quiz appears. Answer correctly to keep the run alive.
5. Keep the run alive as long as you can, session stats are saved automatically when the run ends

### As Admin:
1. Login with admin credentials
2. **Dashboard:** See stats overview and recent games
3. **Quiz Questions:** Add/edit/delete football questions
4. **Settings:** Change AI goalkeeper difficulty (easy/medium/hard)
5. **All Scores:** See every game ever played, searchable by player

---

## 7. SAVED SESSION DATA

Each game session stores:
- Goals scored
- Saves made
- Goals conceded
- Lifelines used
- Played timestamp

Leaderboard totals are ranked by goals first, then saves.

---

## 8. TROUBLESHOOTING

| Issue | Fix |
|-------|-----|
| Blank page | Check PHP error logs, enable `display_errors` in php.ini |
| DB connection error | Verify config.php credentials match your MySQL setup |
| Quiz not loading | Make sure quiz_questions table has rows (schema.sql seeds 10) |
| Keeper/ball invisible | Add images to `/img/` folder (see img/readme.md) |
| Session issues | Make sure `session.save_path` is writable in php.ini |
