# Super Uno

## Introduction

Welcome to the **SUNO** project, a **terminal-based** implementation of the **UNO** card game, written in **C** and following the **C99 standard**.

This project was developed as a way to study and practice the C language, focusing on **modularization, coding best practices, code structure, and game logic**. The goal was to create a **challenging, fun, and faithful** experience based on the official UNO rules.

The game is fully functional and can be downloaded from the **RELEASES** section.  
Check it out at the link below:

- <https://github.com/Starciad/SUno/releases>

---

## About the Project

**SUNO** is a **fully terminal-based** UNO game, providing a **smooth and immersive** gameplay experience with support for **solo mode against AI opponents**.

### **Main Features**

- Intuitive text-based game interface.
- Full implementation of the official UNO rules.
- **AI system for bots**, each with slightly different strategies.
- Detailed messages to track moves and actions.
- Support for **multiple players** against AI opponents.
- Well-structured and modular code following best practices.
- Uses only **C standard libraries**.

The code structure has been carefully designed to be **easy to understand, modify, and expand**, allowing for future feature additions.

## About the UNO Game

**UNO** is an American card game created by **Merle Robbins and family** in **1971**. Over the years, it has become one of the **most popular card games worldwide**, with various themed editions and rule variations.

### **Quick Facts**

- **Number of players**: 2 – 10  
- **Number of cards**: 108  
- **Average playtime**: 15 – 30 minutes  

### **Official Rules**

The objective of the game is to be the first player to get rid of all their cards.

Each player starts with **7 cards**, and a card from the top of the deck is flipped to start the **discard pile**. During the game, players must **play a card that matches the top card** of the discard pile by **number, color, or type**. If they cannot play, they must **draw a card**.

The deck includes **number cards (0–9)** and **special action cards**, as shown in the table below:

| Card            | Effect |
|----------------|--------|
| **Skip**       | The next player **loses their turn**. |
| **Reverse**    | **Reverses** the turn order. |
| **Draw Two (+2)** | The next player **draws 2 cards** and loses their turn. |
| **Wild**       | Allows the player to **choose a new color**. |
| **Wild Draw Four (+4)** | Allows the player to **choose a new color**, forces the next player to **draw 4 cards**, and lose their turn. |

If a player has only **one card left**, they must declare "**UNO!**". If caught not saying it, they must **draw 2 penalty cards**. The game continues until one player has no cards left.

## Screenshots

📸 *Add images or GIFs showcasing the game running in the terminal here.*

## Contributions

Contributions are welcome! If you want to **fix bugs, optimize the code, or add new features**, follow these steps:

1. **Fork** the repository.
2. Create a **new branch** for your changes:

```sh
git checkout -b my-modification
```

3. Make your changes and **commit with a descriptive message**:

```sh
git commit -m "feat: improved AI logic."
```

4. Push your changes to your repository:

```sh
git push origin my-modification
```

5. Open a **Pull Request (PR)** so your changes can be reviewed.

If you find a bug or have a suggestion, feel free to **open an issue**! 🚀

## Compiling the Project

To compile **SUNO**, you need a **C compiler** that supports **C99**. The code can be easily compiled using **GCC**.

### **1. Clone the repository**

```sh
git clone https://github.com/Starciad/SUno.git
cd SUno
```

### **2. Compile the code**

Make sure you have **GCC** and **make** installed in your environment. Then, navigate to the `project/` directory and run `make`. The game will compile and generate an executable.

### **3. Run the game**

```sh
./suno
```

If you prefer to compile manually, ensure that all `*.c` files are being compiled correctly and that the headers in `include/` are included.

## License

This project is licensed under the **MIT License**.  
This means you are free to **use, modify, and distribute** the code, as long as proper credit is given to the original author.

For more details, check the [`LICENSE`](LICENSE) file.

## Acknowledgments

🎴 - Thank you for checking out this project. Have fun playing UNO in the terminal! 😃
