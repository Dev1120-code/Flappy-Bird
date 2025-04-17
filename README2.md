
# 🐦Flappy Bird - Console Game in C++

This is a **console-based Flappy Bird clone** written in C++ that runs on Windows. It uses basic ASCII characters for graphics and handles game logic like jumping, falling, pipe generation, scoring, and collision detection.

---


## 👨‍🎓 Student Submission

- This document is part of our submission for the Open Source Project Exploration assignment. We have selected the open-source Flappy-Bird Game as our project. The repository was explored, analyzed, and understood using modern tooling such as  LLMs (like ChatGPT).

---
## 📌 Project Overview


Original Creator: Angulars Coding
Technologies Used: C++
Repository Type: Open Source
This project provided a suitable balance between simplicity and complexity — ideal for individual analysis and understanding.


## 🧩Features


- Console rendering using ASCII art
- Jump mechanic with gravity
- Dynamic pipe generation with gaps
- Real-time score display
- Simple game menu and instruction screen
- Pipe and bird collision detection
- Game over screen

---

## 🎮Game Controls

- `Spacebar`: Make the bird jump
- `Esc`: Quit the game or return to the menu

---

## 🧠How It Works

The game draws a bird made of characters, which continuously falls due to gravity. Pressing the spacebar moves the bird up. Pipes move from right to left with randomly placed gaps. The player must navigate through these gaps. The game ends when the bird hits a pipe or the ground.

---

## 🧱Code Structure

### 🏠Main Menu

```cpp
int main() {
    // Shows menu and handles user choices
}

 1: Starts THE GAME
 2: Shows instruction
 3: Quits the program
```

---

### 🔁Game Loop (`play()`)

```cpp
void play() {
     
}
Initialize the game
     Runs an infinite loop for live gameplay
     Handles user input, physics, rendering, and collision
     Terminates on collision or exit
```
---
### 🎨Rendering Functions

```cpp
1.  void gotoxy(int x, int y) {
    
}
Moves the console cursor to the specified (x, y) position so that whatever you cout will appear exactly there.
    

2. void setcursor(bool visible, DWORD size){

}
Controls the visibility and size of the blinking console cursor
visible = false hides the cursor (used during gameplay)

🎨3. void drawBorder(){

}
This  function  draws the game boundary box using the ± character. 
It outlines the playable area of the screen.
```
---
### 🏗️Pipe Mechanics
```cpp
🛠️ 1. void genPipe(int ind){

}
Randomly generates the vertical position of the gap in a pipe, so the bird has to fly at different heights.


🎨 2. void drawPipe(int ind){

}
Draws a single pipe with a gap at the calculated position.


🧹 3. void erasePipe(int ind){

}
Clears a pipe from the screen (used before redrawing it in a new position).
This is neede because our console doesn't support "real animation," so the pipe must be erased before moving it left and redrawing.
```
---
### 🐤Bird
```cpp

🎨 1.  void drawBird(){

}
Draws the bird on screen using a 2D character array bird[2][6].
Heigth-2,Width-6

🧽 2.  void eraseBird(){

}
Erases the bird by overwriting its previous position with spaces (" ").
Same reason as erase pipe consol doesn't support "real animation".

```
---

### 💥Collision Detection

```cpp

 int collision(){

}
Checks if the bird has collided with the first pipe (pipe[0]) — either hitting the pipe wall or missing the gap.

```
---
## ⚙️Compilation and Running

- Open a terminal or command prompt.
- Compile the code:
```cpp
g++ -o flappybird flappybird.cpp
```
- Run the Game
```cpp
./flappybird
```

## 📦Dependencies

- A C++ compiler (e.g., g++)

- Windows console for proper character rendering
---
## 🚀Possible Improvements
-Add sound effects

-Implement difficulty scaling

-Add Fruit if bird eat the fruit score will increase by some more score (eg.Increase by 5)

-Improve visuals with Blocks instead of ASCII keys.

## 📸Screenshots

---

## 📄License

- This is open source project and free to use

---

