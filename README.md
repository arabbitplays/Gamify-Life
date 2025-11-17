# Gamify Life

A lightweight, Notcurses-based TUI application for tracking daily tasks, viewing statistics, and maintaining streaks.

- Supports custom tasks and streak definitions
- Optional syncing via PostgreSQL
- Simple, Vim-like keybindings

![img.png](screenshots/img.png)

## Requirements & Building

### Dependencies 
- `yaml-cpp`
- `libpqxx`
- `glm`
- `notcurses`

### Build Requirements
- Meson 
- Python3
- A recent C++ compiler
- (Optional) A Nix flake is provided for building inside a Nix shell

```bash
# Setup build directory
meson setup build

# Compile
meson compile -C build

# Run
./build/GamfiyLife
```

## Configuration

### Profile

- `profile_name`: The profile to use.
  - If it does not exist, it will be created automatically.

### Persistence Options

#### YAML File Storage
- `type`: `"yaml"`
- `dir`: Directory for storing YAML files

#### PostgreSQL Storage
- `type`: `"postgres"`
- `host`: Database host
- `user`: Database user
- `db_name`: Database name
- A SQL script for creating the necessary tables is included in the `scripts/` directory.
