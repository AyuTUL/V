# Design

## Overview
Penalty Shootout uses a dark, restrained visual system with one energetic accent color. The player-facing game surface leans arcade and atmospheric, while the auth and admin surfaces stay compact and literal. The design goal is not premium branding. It is clarity during demos, readable game feedback, and a coherent relationship between gameplay and management screens.

## Color

### Strategy
Restrained dark UI with a single acid-lime accent for primary actions, selected states, and positive outcomes. Red is reserved for destructive or failed states. Yellow and blue appear only in admin-specific secondary roles.

### Tokens
- `--bg`: `#0a0a0a` or `#0e0e0e` depending on surface
- `--surface`: `#1a1a1a`
- `--line`: `#2a2a2a`
- `--text`: `#e0e0e0`
- `--dim`: `#949494` or `#9a9a9a` for supporting text
- `--accent`: `#b0f000`
- `--red`: `#ff4444`
- `--yellow`: `#f0c000` (admin difficulty state)
- `--blue`: `#5090ff` (admin edit affordance)

### Usage rules
- Use `--accent` for primary actions, active selections, key totals, and successful outcomes.
- Use `--red` for errors, wrong answers, destructive actions, and negative outcomes.
- Keep `--dim` for supporting text only, not core labels that need high contrast at small sizes.
- Avoid adding new decorative colors without a task-specific reason.

## Typography

### Families
- Heading/display: `Russo One`
- Body/UI: `Helvetica, Arial, sans-serif`

### Role guidance
- `Russo One` is appropriate for brand marks, screen titles with game energy, and a small number of result callouts.
- Body and form UI stay on the sans-serif stack for readability.
- Small uppercase metadata is part of the current style, but it should stay legible and not be pushed below accessible contrast or size.

## Layout

### Auth
- Narrow centered form shell
- Single card with tabs
- Dense but readable spacing

### Game
- Full-viewport stadium scene
- Top HUD with score and navigation
- One active interaction panel at a time
- Modals for quiz recovery and end-of-game summary

### Admin
- Sidebar navigation on desktop
- Stacked top-first navigation on smaller screens
- Data-heavy card and table layouts
- Compact controls with consistent button vocabulary

## Components

### Buttons
- Primary: acid-lime fill, dark text
- Secondary/ghost: outline on dark surface
- Destructive: ghost button that turns red on hover

### Status patterns
- Success: lime tint plus border
- Error: red tint plus border
- Do not use side-stripe accents as the only state signal

### Tables
- Real table structure for leaderboard and admin data
- Horizontal overflow allowed when necessary
- Use concise headers and readable row spacing

### Modals
- Dark overlay
- Surface card
- Explicit title, explanatory copy, and focused primary action

## Motion
- Short transitions around `150ms` to `450ms`
- Motion supports state change and game feedback only
- Prefer transform and opacity animation over layout-driven animation
- Respect `prefers-reduced-motion`

## Responsive behavior
- Controls should meet a 44px minimum target where practical
- Admin shell collapses away from fixed sidebar behavior on smaller screens
- Game sizing should be based on the rendered goal frame, not fixed desktop dimensions
- HUD and card headers are allowed to wrap

## Accessibility notes
- Target WCAG AA contrast for controls, labels, and helper text
- Keyboard completion matters for both gameplay and admin flows
- Dialogs need focus management and announced status text
