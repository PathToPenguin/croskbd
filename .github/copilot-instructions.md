# GitHub Copilot Instructions for croskbd

## Project Overview

croskbd is a keyboard remapping daemon for Chromebooks running non-ChromeOS operating systems (e.g., Linux). It remaps Chromebook-specific keys to work similarly to ChromeOS and handles tablet mode on 2-in-1 Chromebooks by disabling the keyboard and touchpad when appropriate.

**Current Status**: Alpha software - under active development.

## Technology Stack

- **Language**: C (C2x standard)
- **Build System**: Make
- **Dependencies**: Linux kernel headers (for input/uinput subsystems)
- **Target Platform**: Linux on Chromebook hardware

## Project Structure

```
.
├── src/                    # Source code
│   ├── include/           # Header files
│   ├── croskbd.c          # Main entry point
│   ├── config.c           # Configuration file parsing
│   ├── evdev.c            # Event device handling
│   ├── remap.c            # Key remapping logic
│   ├── uinput.c           # User input device creation
│   ├── vivaldi.c          # Vivaldi keyboard support
│   ├── cros_ec.c          # Chrome EC communication
│   └── utils.c            # Utility functions
├── data/                  # Init system service files
│   ├── croskbd.dinit.in   # Dinit service template
│   └── croskbd.systemd.in # Systemd service template
├── example.conf           # Example configuration file
├── Makefile               # Build configuration
└── README.md              # Project documentation
```

## Building the Project

### Build Commands

```bash
# Build the project
make

# Clean build artifacts
make clean

# Install the binary
make install

# Install with systemd service
make install install_systemd

# Install with dinit service
make install install_dinit
```

### Build Configuration

- Compiler: Uses `CC` environment variable (defaults to `cc`)
- Build flags:
  - `-std=c2x`: C2x standard
  - `-O2`: Optimization level 2
  - `-Wall -Werror`: All warnings as errors
  - `-pedantic`: Strict ISO C compliance
- Build artifacts are placed in `./build/` directory

## Coding Standards

### Code Style

- **Formatting**: Use clang-format with the provided `.clang-format` configuration
  - Tabs for indentation (width: 4)
  - Tab width: 4 spaces
- **Naming**: Follow existing patterns in the codebase
- **Headers**: Include guards in all header files
- **Comments**: Use C-style comments (`/* */`) for multi-line, C++ style (`//`) is acceptable for single-line

### Code Quality

- Code must compile without warnings (`-Wall -Werror`)
- Follow C2x standard strictly (`-std=c2x -pedantic`)
- Avoid platform-specific code where possible
- All changes should maintain compatibility with the existing codebase

## Configuration

The project uses a simple configuration file format (see `example.conf`):

```
debug=true
delete_key=true
override_key_codes=true
invert_top_row=false
handle_tablet_switch=false
```

Configuration is parsed by `src/config.c` and affects runtime behavior.

## Key Features

- **Event reading**: Reads events from keyboard via evdev
- **Event sending**: Sends remapped events via uinput
- **Key remapping**: Supports various remapping modes
- **Top row handling**: Chromebook top row (function keys) remapping
- **Inverted top row**: Alternate top row behavior
- **Vivaldi keyboards**: Support for newer Chromebook keyboards
- **Tablet mode**: Handles device state changes (in development)

## Development Guidelines

### Making Changes

1. **Understand the context**: This is a low-level system daemon that interacts with kernel input subsystems
2. **Test on hardware**: Ideally test on Chromebook hardware, but cross-compilation is supported
3. **Minimal changes**: This is a focused project - avoid feature creep
4. **Error handling**: Check all system calls and handle errors appropriately
5. **Memory safety**: Be careful with pointers and memory allocation
6. **Security**: This runs as a system daemon - security is important

### Common Tasks

- **Adding a new key remap**: Modify `src/remap.c` and `src/include/static_remaps.h`
- **Configuration options**: Update `src/config.c` and the `Settings` structure
- **Device support**: Add device-specific logic in appropriate modules (e.g., `vivaldi.c`, `cros_ec.c`)

### File-Specific Guidance

- `src/croskbd.c`: Main event loop and initialization
- `src/evdev.c`: Low-level event device handling - be careful with kernel APIs
- `src/uinput.c`: Virtual device creation - kernel API changes can break this
- `src/config.c`: Simple INI-style parsing - keep it simple
- `src/remap.c`: Core remapping logic - performance matters here
- `src/vivaldi.c`: Device-specific keyboard layouts
- `src/cros_ec.c`: Chrome embedded controller communication

## Testing

Currently, there is no automated test suite. Testing is done manually on Chromebook hardware.

When making changes:
1. Ensure the project builds without warnings
2. Test basic functionality on target hardware if available
3. Verify configuration file parsing works correctly
4. Check that key remapping behaves as expected

## Installation

The project provides installation targets for both systemd and dinit init systems:

- `make install`: Installs the binary to `$(PREFIX)/bin/` (default: `/usr/local/bin/`)
- `make install_systemd`: Installs systemd service file
- `make install_dinit`: Installs dinit service file

## Known Limitations

- No automated tests
- Limited to Linux on Chromebook hardware
- Some features are still in development (see README.md)
- Requires root/elevated privileges to access input devices

## Contributing

When contributing to this project:
1. Keep changes minimal and focused
2. Follow the existing code style (use clang-format)
3. Ensure code compiles without warnings
4. Update documentation if adding new features or changing behavior
5. Test on real hardware when possible
