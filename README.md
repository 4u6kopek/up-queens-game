# Queens Game - FMI Edition

A strategy console game developed as a course project for the "Introduction to Programming" course at the Faculty of Mathematics and Informatics, Sofia University.

## 📝 Description
**Queens** is a tactical game played on a rectangular board of size **N x M** (max 15x15). Players must place queens on the board following strict chess-like rules until no valid moves remain.

## 📜 Game Rules
- Players take turns placing a single queen (**Q**) on an empty cell.
- A move is **valid** only if the new queen is not under attack by any previously placed queens (same row, column, or diagonal).
- The game **ends** when the current player has no valid moves left.
- The winner is the player who made the last valid move.

---

## ⌨️ Commands
The game is controlled via the following console commands:

| Command | Description |
| :--- | :--- |
| `new N M` | Starts a new PvP game with board dimensions N x M. |
| `new N M robot [diff]` | Starts a game against a robot (difficulties: `easy`, `medium`, `hard`). |
| `play x y` | Places a queen at the specified row **x** and column **y**. |
| `free` | Lists all valid cells where a queen can currently be placed. |
| `show` | Visualizes the current state of the board. |
| `turn` | Displays which player is currently on move. |
| `back` | Undoes the last made move. |
| `history` | Displays the full history of moves made during the game. |
| `save [filename]` | Saves the current game state to a plain text file. |
| `load [filename]` | Loads a saved game from a text file. |
| `help` | Shows a list of all available commands. |
| `exit` | Quits the program. |

---

## 🤖 Robot Intelligence
When playing against the computer, you can choose between three difficulty levels:
- **Easy**: The robot picks the first available valid move it finds.
- **Medium**: The robot prioritizes moves near the edges of the board.
- **Hard**: The robot calculates a move that minimizes the opponent's future valid moves.

---

## 👤 Author
- **Name**: Bogomil Dimitrov
- **Course**: Software Engineering
- **University**: Sofia University "St. Kliment Ohridski", FMI
