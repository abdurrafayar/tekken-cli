<!-- Banner -->
<div align="center">

```
 ███████████ ██████████ █████   ████ █████   ████ ██████████ ██████   █████
░█░░░███░░░█░░███░░░░░█░░███   ███░ ░░███   ███░ ░░███░░░░░█░░██████ ░░███
░   ░███  ░  ░███  █ ░  ░███  ███    ░███  ███    ░███  █ ░  ░███░███ ░███
    ░███     ░██████    ░███████     ░███████     ░██████    ░███░░███░███
    ░███     ░███░░█    ░███░░███    ░███░░███    ░███░░█    ░███ ░░██████
    ░███     ░███ ░   █ ░███ ░░███   ░███ ░░███   ░███ ░   █ ░███  ░░█████
    █████    ██████████ █████ ░░████ █████ ░░████ ██████████ █████  ░░█████
   ░░░░░    ░░░░░░░░░░ ░░░░░   ░░░░ ░░░░░   ░░░░ ░░░░░░░░░░ ░░░░░    ░░░░░
```

<img src="https://img.shields.io/badge/language-C%2B%2B-blue?style=for-the-badge&logo=c%2B%2B" />
<img src="https://img.shields.io/badge/platform-Windows-lightblue?style=for-the-badge&logo=windows" />
<img src="https://img.shields.io/badge/players-2%20Local-green?style=for-the-badge" />
<img src="https://img.shields.io/badge/engine-None%20-red?style=for-the-badge" />

> A 2-player Tekken-inspired fighting game built entirely in a Windows terminal. No game engine. Just pure console magic. 🥊

</div>

---

## 🎮 What is this?

A semester project that turned into something way cooler than expected. **Tekken CLI** is a fully playable 2-player fighting game that runs inside a Windows command prompt — no Unity, no Unreal, no game engine at all. Just C++, `cout`, and a lot of creative thinking.

---

## 🥊 Key Features

- 🥊 3 fighters with unique moves and hand-crafted ASCII animations
- ⚔️ Real-time 2-player battles with simple, easy-to-learn controls
- 💥 Hit detection, damage effects & live health bars
- 🏆 Best-of-3 rounds with a 30-second timer each
- 💾 Save & load system to pick up where you left off
- 🔊 Sound effects to make it feel like an actual game
- 🖥️ Built entirely in a console window — no game engine, just C++

---

## 🕹️ Controls

| Action       | Player 1     | Player 2          |
| ------------ | ------------ | ----------------- |
| Move Left    | `A`          | `←` Left Arrow    |
| Move Right   | `D`          | `→` Right Arrow   |
| Punch 1      | `E`          | `Numpad 7`        |
| Punch 2      | `Q`          | `Numpad 8`        |
| Kick         | `Z`          | `Numpad 4`        |
| Pause        | `ESC`        | `ESC`             |

---

## 🧑‍💻 How to Run

### ⚡ Quick Start — No Compilation Needed

Just download the repo and double-click **`tekken.exe`** — that's it. You're in. 🎮

> Make sure the `sounds/` folder stays in the same folder as `tekken.exe`, otherwise the sound effects won't work.

---

### 🔧 Want to Compile It Yourself?

Sure! Here's how:

1. Clone the repo
```bash
git clone https://github.com/yourusername/tekken-cli.git
cd tekken-cli
```

2. Make sure the `sounds/` folder is in the same directory and contains:
```
sounds/
├── fight.wav
├── punch1.wav
├── punch2.wav
├── kick.wav
├── sword.wav
├── menu.wav
└── enter.wav
```

3. Compile
```bash
g++ -o tekken main.cpp -lwinmm
```

4. Run
```bash
./tekken.exe
```

> ⚠️ This game is Windows-only because it uses the Windows Console API and WinMM for sound.

---

## 🎨 The Characters

| Character    | Style            | Special Move Sound |
| ------------ | ---------------- | ------------------ |
| Jin          | Fast & Aggressive | Punch              |
| Yoshimitsu   | Skilled Swordsman | Sword Strike       |
| Paul         | Heavy Hitter     | Punch              |

Each character has 5 unique ASCII sprites: **idle, punch 1, punch 2, kick, and hurt** — all hand-drawn in code.

---

## ⚙️ Tech Stack

| What                | How                                      |
| ------------------- | ---------------------------------------- |
| Language            | C++                                      |
| Console Rendering   | Windows Console API (`gotoxy`, colors)   |
| Input Handling      | `GetAsyncKeyState` (real-time)           |
| Sound               | WinMM (`PlaySound`)                      |
| Save System         | File I/O with CSV parsing                |
| Sprite Mirroring    | Custom character-flip for Player 2       |

---

## 📂 Project Structure

```
tekken-cli/
├── main.cpp              # Everything lives here
├── sounds/               # .wav sound effects
│   ├── fight.wav
│   ├── punch1.wav
│   ├── punch2.wav
│   ├── kick.wav
│   ├── sword.wav
│   ├── menu.wav
│   └── enter.wav
├── tekken_saves.txt      # Auto-generated save file
└── README.md
```

---

## 💡 How It Works (The Fun Bits)

- **Sprites are just strings.** Each character is 17 lines of ASCII art stored in string arrays. Attacking? Swap the idle sprite for the attack sprite, print it, then swap back.
- **Player 2 is mirrored.** Every `/` becomes `\`, every `[` becomes `]` — flipped character by character so P2 faces the right direction.
- **Hit detection is distance-based.** If the gap between two players is smaller than the attack's reach, it lands. Simple but satisfying.
- **The timer is ASCII too.** Each digit (0–9) is a hand-drawn block font, rendered live on screen.

---

## 🙌 Credits

Built as a 1st semester project. Inspired by the legendary **Tekken** series by Bandai Namco.

---

<div align="center">

Made with 💛 and pure console magic.

</div>
