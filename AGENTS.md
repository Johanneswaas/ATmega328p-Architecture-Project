# AGENTS.md

## Project overview

This repository is a small AVR C project for the ATmega328P microcontroller.

- Application code lives under `Application/`.
- Peripheral drivers live under `driver/`.
- Application-specific configuration objects live under `Application/Config/`.
- The current project structure is organized by peripheral, e.g. `driver/DIO/` and `driver/USART/`.

## Coding conventions

- Keep code in C11 and prefer explicit integer types from `stdint.h`.
- Maintain the existing driver pattern: public API in the module header, implementation in the matching `.c` file, and application configuration separated from the driver layer.
- Preserve the Doxygen-style header comments already used in the project.
- Prefer MCU-safe code using AVR register access and the existing types/enums instead of introducing host-only abstractions.
- Treat `Application/Config/` as the application-level wiring layer; do not move configuration concerns into the driver implementation unless the architecture genuinely requires it.

## Important project-specific patterns

- `driver/DIO/Dio.h` defines the shared DIO port/pin enums and configuration structure used by the app.
- `Application/Config/DIO/Dio_cfg.h` and `Dio_cfg.c` declare the actual pin mapping used by the firmware.
- `Application/main.c` is the entry point and wires the app to the driver layer.
- `driver/USART/Usart.c` implements the ISR-based RX buffer pattern and should be handled with care when touching interrupt logic or ring-buffer behavior.

## Build and validation guidance

- There is no repository Makefile or README in the current workspace, so the project appears to rely on direct AVR tooling and editor configuration instead of a generated build script.
- The VS Code configuration in `.vscode/c_cpp_properties.json` targets `avr-gcc` with `-mmcu=atmega328p` and includes the AVR headers from the Homebrew AVR toolchain.
- If a build step is needed, prefer the repo's canonical AVR toolchain commands rather than introducing new cross-platform assumptions.
- When adding or modifying code, keep the compile target aligned with ATmega328P hardware requirements and avoid host-side libraries.

## Working rules for AI agents

- Keep changes minimal and aligned with the existing module boundaries.
- Do not rename public driver functions or enums without updating their call sites and configuration usage.
- If adding new I/O or peripheral config, extend the existing pattern instead of creating a separate ad hoc design.
- Preserve invariant behavior in interrupt-driven code and register-level logic; prioritize correctness over convenience.
- If the project later gains a build script or README, prefer matching that official workflow over the information in this file.
