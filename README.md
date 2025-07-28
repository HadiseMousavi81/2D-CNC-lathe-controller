#  2-Axis CNC Lathe Controller (STM32F103 + PlatformIO)

⚙ This project is a 2-axis CNC lathe motion controller developed from scratch using an STM32F103C8T6 microcontroller (Blue Pill). It is entirely implemented in C at the register level — without relying on GRBL, Marlin, HAL, or STM32CubeMX.

> Built from the ground up for maximum control and learning — no abstraction layers, no firmware reuse.

---

##  Project Status: In Development

This project is actively being developed. The following core modules have been implemented and tested:

- ✅ Stepper motor control (pulse generation using hardware timers)
- ✅ Linear motion module (based on Bresenham’s algorithm)
- ✅ Circular/arc motion module (G2/G3 interpolation logic)




##  Technical Overview

| Feature           | Details                                |
|------------------|----------------------------------------|
| MCU              | STM32F103C8T6 (ARM Cortex-M3, 72 MHz)  |
| Language         | C (pure register-level, no HAL)        |
| Framework        | PlatformIO with VSCode                 |
| Control Type     | 2-axis motion (X/Y)                    |
| Protocol Support | G0, G1, G2, G3 (Manual Implementation) |
| Architecture     | Modular (Motion / Drivers / Utils / etc.) |
| Dependencies     | None (No GRBL, no Marlin, no HAL)      |

---

##  Project Structure
ProjectRoot/
│
├── Core/ ← Entry point and system initialization
├── Motion/ ← Line and arc motion control (G1, G2, G3)
├── Drivers/ ← Low-level control of GPIO, Timers, Steppers
├── Utils/ ← Math helpers (e.g., angle normalization)
├── Inc/ ← Global constants and type definitions
└── platformio.ini ← PlatformIO build configuration



---

##  Goals

- Create a lightweight, low-latency CNC motion controller from scratch
- Learn and demonstrate real-time motion control using STM32 at the register level
- Build a modular and extensible codebase ready for G-code parsing and future expansion
- Avoid external firmware like GRBL or Marlin for maximum control and clarity

---

##  Note

This project is not based on GRBL, Marlin, or any existing CNC firmware. All code is handcrafted with direct register access for educational and performance-focused development.

---

> If you're passionate about embedded systems, CNC, or bare-metal STM32 programming, give this project a ⭐ star and follow along!




