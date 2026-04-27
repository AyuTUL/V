# /img — Required Game Assets

Place the following images in this folder:

| File               | Description                                      | Suggested Size |
|--------------------|--------------------------------------------------|----------------|
| `keeper.png`       | Goalkeeper standing (facing forward)             | 80×120px       |
| `keeper-left.png`  | Goalkeeper diving left                           | 80×120px       |
| `keeper-right.png` | Goalkeeper diving right                          | 80×120px       |
| `ball.png`         | Football (transparent background recommended)    | 60×60px        |
| `stadium.png`      | Stadium background (optional, used in old style) | 900×550px      |
| `goal.png`         | Goal net texture (optional)                      | 560×230px      |

## Free asset sources:
- https://opengameart.org (search "soccer goalkeeper")
- https://itch.io/game-assets (free tier)
- https://craftpix.net/freebies/ (sports assets)
- Or use simple CSS shapes — the game works without images.

## Using CSS fallbacks (no images needed):
The game CSS uses `background: url(...)` with `no-repeat` fallbacks, so 
if images are missing the game still runs — keeper and ball will just be invisible.
You can replace them with colored div boxes in game.css if needed.
