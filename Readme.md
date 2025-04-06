# Batputer

This project is a simple command-line tool that displays battery status information on Unix-like systems. The tool specifically shows battery status, charge level, health, and whether the battery is plugged in or unplugged.

## Features
- Display battery capacity and charge level
- Show battery status (plugged in or unplugged)
- Display battery type and health
- Show tool version
- Verbose mode to display detailed battery information

## Prerequisites
This tool is designed to run only on Unix-like systems (such as Linux and macOS). For proper functionality, the relevant battery information files must exist in the `/sys/class/power_supply/BAT0/` path on your system.

## Installation and Usage

### Steps to compile and run:

1. First, download or copy the code.
2. Ensure you have the `g++` compiler or any other C++ compiler installed on your system.

### Compile the project:

In the project directory, there is a `Makefile`. To compile the project, use the following command:

```bash
make
```

This will generate the executable `battery_monitor` in the current directory.

### Run the program:

To run the tool after compiling:

```bash
./batputer
```

## Options:

- `-h` or `--help`: Display help message.
- `-v` or `--version`: Show the tool version.
- `-vv` or `--verbose`: Show detailed battery information.

### Examples:

1. To display the battery status by default:

```bash
./batputer
```

2. To show the version of the program:

```bash
./batputer --version
```

3. To display more detailed battery information (verbose mode):

```bash
./batputer --verbose
```

4. To display the help message:

```bash
./batputer --help
```

## Project Structure

- `main.cpp`: The main program file containing the code that runs the tool.
- `tinyArgs/include/tinyArgs.hpp`: Header file for the `tinyArgs` library to handle command-line arguments.
- `Makefile`: Makefile that helps you compile the project using the `make` tool.

## Developers

- **Version**: 0.0.2
- **Developer**: mateo-rfz
