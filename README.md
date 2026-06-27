# 🚢 Battleship Simulator

A console-based two-player Battleship game built in C++ with color-coded board rendering, ship tracking, and score-based win detection.

---

## 🎮 Game Overview

Battleship is a classic strategy game where two players place their fleets on a 10x10 grid and take turns firing shots to sink each other's ships. Features both **Player vs Player** and **Player vs Computer** modes with a color-coded side-by-side board display.

---

## ✨ Features

- 🧭 Interactive main menu with game modes, instructions, and leaderboard
- 👥 Player vs Player and Player vs Computer modes
- 🗺️ Manual or random ship placement with horizontal/vertical orientation
- 🎨 Color-coded console board rendered side-by-side during gameplay
- 💥 Sunk ship detection — entire ship turns pink when fully destroyed
- ✅ Full input validation — boundaries, overlaps, and duplicate attacks
- 📊 Score tracking — hits reward, misses deduct

---

## 🛳️ Ships

| # | Ship | Size |
|---|------|------|
| 1 | Aircraft Carrier | 5 blocks |
| 2 | Battleship | 4 blocks |
| 3 | Destroyer | 3 blocks |
| 4 | Submarine | 3 blocks |
| 5 | Patrol Boat | 2 blocks |

---

## 🎯 Gameplay

- Each player places 5 ships on their own 10x10 grid
- Players alternate turns with **6 shots per turn**
- Enter row and column to attack the opponent's grid
- Cells already marked `X` or `O` cannot be re-attacked
- First player to destroy all enemy ships wins

---

## 🎨 Color Indicators

| Symbol | Color | Meaning |
|--------|-------|---------|
| `~` | Blue | Water / Empty |
| `X` | Red | Hit |
| `O` | Grey | Miss |
| `P` | Pink | Sunk Ship |

---

## 📊 Scoring

| Action | Points |
|--------|--------|
| Hit | +10 |
| Miss | -1 |

---

## 🛠️ Tech Stack

- **Language:** C++
- **Library:** Windows.h (console colors)
- **IDE:** Dev-C++

---

## 📁 Project Structure

```
Battleship/
├── battleship.cpp       # Full game source
└── README.md
```

---

## 🚀 How to Run

1. Clone the repository:
```bash
git clone https://github.com/mhussainusman/Battleship---console-game.git
```

2. Compile:
```bash
g++ battleship.cpp -o battleship
```

3. Run:
```bash
./battleship
```

> ⚠️ Windows only — uses `windows.h` for console color support

---

## ⚙️ Requirements

- Windows OS
- g++ compiler or any C++ IDE

---

## ⚠️ Known Limitations

- Player vs Computer mode not yet implemented
- Leaderboard is currently hardcoded (file I/O not integrated)

---

## 👤 Author

**Hussain Usman**
- GitHub: [@mhussainusman](https://github.com/mhussainusman)
- LinkedIn: [linkedin.com/in/hussain-usman-69b0a4286](https://linkedin.com/in/hussain-usman-69b0a4286)