# Pebble Shell 🐚

<div align="center">
  <pre>
<span style="color: #4FC3F7"> ____  _____ ____  ____  _      _      </span>
<span style="color: #81C784">|  _ \| ____| __ )| __ )| |    | |     </span>
<span style="color: #FFD54F">| |_) |  _| |  _ \|  _ \| |    | |     </span>
<span style="color: #E57373">|  __/| |___| |_) | |_) | |___ | |___  </span>
<span style="color: #CE93D8">|_|   |_____|____/|____/|_____|_____| </span>
  </pre>
  <p><em>By Riley Simmons</em></p>
</div>

---

Pebble is a lightweight, C-powered command-line shell with a splash of fun! Built-in `cd`, `exit`, background processes, piping, redirection, and a neat `delay` feature.

## 🚀 Features

- **Interactive Prompt** with command history and **arrow key navigation** (using GNU Readline)
- **Tab Completion** for filenames and commands
- **Environment Variable Expansion** like `$HOME`, `$PATH`, etc.
- **Syntax Highlighted Prompt** with current directory
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
Pebble ~/projects> cd ~/projects
Pebble ~/projects> delay 5 echo "Hello after 5 seconds"
Pebble ~/projects> echo $HOME
Pebble ~/projects> ls -l | grep ".c"
Pebble ~/projects> sleep 10 &
Pebble ~/projects> exit
```

## 📝 Code Structure

```
├── Makefile         # Build script
├── shell.h          # Public API
├── main.c           # Core loop & built-ins
├── input.c          # Readline input, tab-completion & history
├── exec.c           # Command execution, env var expansion, redirection
├── delay.c          # Delay queue & scheduler thread
└── visuals.c        # ASCII banner, colored prompt, clear-screen
```

## 🎨 Customize

- **Banner**: Edit `visuals.c` for your own ASCII art
- **Prompt Colors**: Modify ANSI codes in `visuals.c` prompt
- **Built-ins**: Extend `main.c` with new commands
- **Tab Completion**: Extend to search `$PATH` if desired

## 📜 License

This project is released under the MIT License. See [LICENSE](LICENSE) for details.

---

<sub>Made with ❤️ by Riley Simmons and powered by C & ☕</sub>
