# The Weight Of Love

**The Weight Of Love** is a narrative-driven C/C++ text adventure game that blends detective investigation, puzzles, and minigames. You play as a world-famous detective, driven to solve the murder of your beloved wife. The game tests your deduction, reasoning, and reflexes through a series of interactive rooms, each with unique challenges and story elements.

---

## Features

- **Investigation Phase:**  
  Collect clues, interrogate witnesses, and piece together the mystery in a branching investigation system.

- **Minigames:**  
  **Wordle:** Guess the correct five-letter word to progress.

  **Hangman:** Save your son by guessing the word before the hangman is complete.

  **Maze:** Navigate a randomly generated maze, avoid enemies, and survive.

  **Battle System:** Engage in turn-based combat with weapons and health bars.

  **Russian Roulette:** Make life-or-death choices in a tense minigame.

  **Typing Speed Game:** Test your typing speed and accuracy under time pressure.

- **Branching Narrative:**  
  Your choices and performance in minigames affect the story's outcome, leading to different epilogues.

---

## Folder Structure

```
final/
    b24cm1018_b24cm1002_b24cm1053_b24cs1056_main.c         # Main game logic and flow
    b24cm1018_b24cm1002_b24cm1053_b24cs1056_investigation.c # Investigation phase
    b24cm1018_b24cm1002_b24cm1053_b24cs1056_wordle.h       # Wordle minigame
    b24cm1018_b24cm1002_b24cm1053_b24cs1056_Hangmans.c     # Hangman minigame
    b24cm1018_b24cm1002_b24cm1053_b24cs1056_maze.c         # Maze minigame
    b24cm1018_b24cm1002_b24cm1053_b24cs1056_russianRoulette.c # Russian Roulette minigame
    b24cm1018_b24cm1002_b24cm1053_b24cs1056_character.h    # Character and battle system
    b24cm1018_b24cm1002_b24cm1053_b24cs1056_words.h/.txt   # Wordle word list and meanings
    b24cm1018_b24cm1002_b24cm1053_b24cs1056_clues.txt      # Investigation clues
    b24cm1018_b24cm1002_b24cm1053_b24cs1056_datastorage.txt # Game state tracking
    b24cm1018_b24cm1002_b24cm1053_b24cs1056_EpilogueWin.txt # Winning epilogue
    b24cm1018_b24cm1002_b24cm1053_b24cs1056_EpilogueLose.txt # Losing epilogue
    ...
```

---

## How to Build & Run

1. **Requirements:**
   - C compiler (e.g., GCC, MinGW, MSVC)
   - Windows OS (for some minigames using `<windows.h>` and `conio.h`)

2. **Build:**
   Compile each `.c` file as an executable. For example:
   ```sh
   gcc -o b24cm1018_b24cm1002_b24cm1053_b24cs1056_main.exe b24cm1018_b24cm1002_b24cm1053_b24cs1056_main.c
   ```
   Repeat for other minigames as needed.

3. **Run:**
   Start the main game:
   ```sh
   ./b24cm1018_b24cm1002_b24cm1053_b24cs1056_main.exe
   ```

   The main executable will call other minigame executables as you progress.

---

## Gameplay Overview

- **Start:**  
  Enter your character's name and begin the investigation.
- **Investigation:**  
  Collect all clues and testimonies to unlock the next phase.
- **Rooms:**  
  Solve puzzles and win minigames to advance through rooms.
- **Finale:**  
  Face the mastermind in a final battle. Your choices and victories determine the ending.

---

## Credits

Developed by NotEpicGames.
Scriptwriter - Abhinav Kumar
Programmer - Abhinav Kumar, Yug Dalwadi Bharat, Pranav Nair, Sadat Ul Rouf Wani.

## Notes

- Some minigames require a Windows terminal for full compatibility.
- All story, code, and assets are original and for educational/demo purposes.

## License

This project is for educational use only.


**Enjoy unraveling the mystery and testing your skills in _The Weight Of Love_!**