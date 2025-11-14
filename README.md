# 🏓 Neon PingPong Game in C++

Welcome to the **Neon PingPong Game**, a visually striking and exhilarating classic Pong remake, crafted with love in C++! Featuring modern neon aesthetics, dynamic sound effects, and smooth controls, this game aims for an arcade-like experience right on your desktop.

![Neon PingPong Preview](preview.jpg)

---

## ✨ Features

- **Neon Theme:** Dazzling, animated neon visuals and glowing effects for a cyber arcade vibe.
- **Classic Gameplay:** Faithful to arcade pong, with paddles and a ball that speeds up over time.
- **Audio Integration:** Immersive background music and crisp sound effects for hits, scores, and game events.
- **Single & Multiplayer:** Play solo against the computer or challenge a friend locally (2-player mode).
- **Score Tracking:** Real-time score display—first to 10 wins!
- **Customizable Controls:** Responsive and intuitive key mapping for both paddles.
- **Pause & Restart:** Press P to pause the action, R to restart the match.
  
---

## 🎮 How to Play

- **Player 1 Controls:**  
  - Move Up: `W`  
  - Move Down: `S`
- **Player 2 Controls:**  
  - Move Up: `Up Arrow`  
  - Move Down: `Down Arrow`
- Press `P` to pause and `R` to restart the match.

Deflect the ball with your paddle and outmaneuver your opponent. The first player to reach 10 points wins!

---

## 🔊 Audio

- **Background Music:** Futuristic rhythm to match the neon theme.
- **Sound Effects:** Responsive sounds for paddle hits, wall bounces, and scoring.

> **Tip:** You can mute/unmute background music by pressing `M`.

---

## 🚀 Getting Started

### Prerequisites

- **C++17** or higher
- [Raylib](https://www.raylib.com/) graphics/audio library
- Visual Studio Code / Visual Studio / GCC g++

### Installation

1. **Clone the repository:**
    ```bash
    git clone https://github.com/Muhammadbilal206/PingPong-Game-in-Cpp.git
    cd PingPong-Game-in-Cpp
    ```
2. **Install Raylib:**
   - [Raylib Installation Instructions](https://github.com/raysan5/raylib#installation)

3. **Build and Run:**
    ```bash
    g++ -o pingpong main.cpp audio.cpp neon_theme.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
    ./pingpong
    ```

    *Or use the provided VSCode/Visual Studio project files for Windows.*

---

## 🗂️ Project Structure

```
PingPong-Game-in-Cpp/
├── main.cpp        # Game logic
├── audio.cpp/.h    # Audio and sound management
├── neon_theme.cpp  # Neon visual effects
├── assets/         # Audio/music files and neon textures
├── README.md
└── ...
```

---

## 📺 Demo

Check out a gameplay video here:  
[![Neon PingPong Gameplay](https://img.youtube.com/vi/PaAcVk5jUd8/0.jpg)](https://www.youtube.com/watch?v=PaAcVk5jUd8)

---

## 🙏 Credits

- Inspired by the original Pong (Atari 1972)
- Built with [C++](https://en.cppreference.com/w/) and [Raylib](https://www.raylib.com/)
- Neon SFX & Music: [FreeSound.org](https://freesound.org/) / [Mixkit](https://mixkit.co/)
- Neon art inspiration from [Behance Neon Game Art](https://www.behance.net/)

---

## 📃 License

MIT License.  
Feel free to fork, use, and modify!

---

Enjoy the game!  
💡 Suggestions and pull requests are welcome!
