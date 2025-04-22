# Pebble Shell 🐚

<div align="center">
  <pre>
 ____  _____ ____  ____  _      _      
|  _ \| ____| __ )| __ )| |    | |     
| |_) |  _| |  _ \|  _ \| |    | |     
|  __/| |___| |_) | |_) | |___ | |___  
|_|   |_____|____/|____/|_____|_____|
  </pre>
  <p><em>By Riley Simmons</em></p>
</div>

---

Pebble is a lightweight, C-powered command-line shell with a splash of fun! Built-in `cd`, `exit`, background processes, piping, redirection, and a neat `delay` feature.

## 🚀 Features

- **Interactive Prompt** with command history (using GNU Readline)
- **Built-in Commands**: `cd`, `exit`, and `delay <sec> <cmd>`
- **Background Execution** via `&`
- **Pipelines & Redirection** (`|`, `<`, `>`, `>>`)
- **ASCII Art Banner** to welcome you each session
- **Full Source Separation** (`.c` and `.h` files)
- **Threaded Delay**: schedule commands for future execution

## 🛠️ Installation & Build

<details>
<summary>Prerequisites (click to expand)</summary>

- GCC (or any C compiler)
- GNU Make
- `pkg-config`
- GNU Readline headers
- POSIX Threads

</details>

```bash
# On Ubuntu/Debian
sudo apt update
sudo apt install build-essential pkg-config libreadline-dev

# Clone and build
git clone https://github.com/yourusername/pebble.git
cd pebble
make
```

## 💡 Usage

```bash
# Start the shell
./pebble

# Try built-in commands
Pebble> cd ~/projects
Pebble> delay 5 echo "Hello after 5 seconds"
Pebble> ls -l | grep ".c"
Pebble> sleep 10 &
Pebble> exit
```

## 📝 Code Structure

```
├── Makefile         # Build script
├── shell.h          # Public API
├── main.c           # Core loop & built-ins
├── input.c          # Readline-based input & history
├── exec.c           # Command execution, pipes, redirection
├── delay.c          # Delay queue & scheduler thread
└── visuals.c        # ASCII banner & clear-screen
```

## 🎨 Customize

- **Banner**: Edit `visuals.c` for your own ASCII art
- **Prompt**: Change the `readline("Pebble> ")` call in `input.c`
- **Built-ins**: Extend `main.c` with new commands

## 📜 License

This project is released under the MIT License. See [LICENSE](LICENSE) for details.

---

<sub>Made with ❤️ by Riley Simmons and powered by C & ☕</sub>

