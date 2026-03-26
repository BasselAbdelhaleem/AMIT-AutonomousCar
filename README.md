# 🚗 AVR Self-Driving Car — Obstacle-Avoiding Robot

> A fully functional obstacle-avoiding autonomous car built on bare-metal AVR C — no Arduino framework, no shortcuts, just registers.

---

## 🧠 What Is This?

An obstacle-avoiding autonomous car implemented from scratch in **bare-metal C** on an **AVR ATmega microcontroller** — no Arduino framework, no HAL abstractions, just direct register manipulation.

The car drives forward autonomously. When an obstacle is detected within a threshold distance, it stops, sweeps a servo-mounted ultrasonic sensor left and right to evaluate both directions, then steers toward the clearer path. Distance readings are displayed in real time on a 16×2 LCD.

What makes this project stand out is the **software architecture**: the codebase is structured as a proper **layered driver stack** — MCAL → HAL → APP — mirroring the design patterns used in professional automotive and embedded firmware teams.

---

## ✨ Key Features

- **Fully autonomous obstacle avoidance** — stop, scan, decide, steer
- **Servo-mounted ultrasonic scanning** — left/right sweep to choose optimal direction
- **Real-time LCD feedback** — distance displayed live on 2×16 LCD
- **Bare-metal AVR C** — all peripherals driven via direct register access (DIO, Timers, Interrupts)
- **Layered firmware architecture** — clean MCAL / HAL / APP separation
- **PWM motor control** — DC motor speed controlled via timer-generated PWM
- **4-bit LCD mode** — configured for pin-constrained AMIT learning kit

---

## 🏗️ System Architecture

The firmware is organized into three strict layers — each layer only calls downward, never upward:

```
┌─────────────────────────────────────────┐
│             APP LAYER                   │
│  main.c — autonomous driving logic      │
│  Obstacle detect → scan → decide → steer│
└──────────────────┬──────────────────────┘
                   │ calls
┌──────────────────▼──────────────────────┐
│             HAL LAYER                   │
│  Servo · LCD · Ultrasonic · DC Motor    │
│  (external peripheral drivers)          │
└──────────────────┬──────────────────────┘
                   │ calls
┌──────────────────▼──────────────────────┐
│            MCAL LAYER                   │
│  DIO · Timers · Interrupts · Registers  │
│  (MCU internal peripheral drivers)      │
└─────────────────────────────────────────┘
```

---

## 🔧 Hardware

### Components

| Component | Quantity | Role |
|---|---|---|
| AVR ATmega MCU (AMIT Kit) | 1 | Main controller |
| DC Motors | 2 | Drive wheels |
| Servo Motor | 1 | Rotates ultrasonic sensor |
| Ultrasonic Sensor (HC-SR04) | 1 | Obstacle distance measurement |
| LCD 2×16 | 1 | Real-time distance display |
| Car Chassis Kit | 1 | Platform + wheels |

### Wiring Overview

- **LCD** — wired in **4-bit mode** to conserve GPIO pins on the AMIT kit; data sent in two nibbles per byte
- **Servo** — driven via software delay PWM (0.5ms = 0°, 1.5ms = 90°, 2.5ms = 180°)
- **Ultrasonic** — trigger pulse sent, echo pulse timed via timer to compute distance
- **DC Motors** — driven directly via GPIO + PWM (H-bridge workaround; see Challenges)

---

## 💻 Firmware

### MCAL Layer — Microcontroller Abstraction

Direct register-level drivers for all ATmega internal peripherals:

| Module | Functionality |
|---|---|
| `dio.c / dio.h` | GPIO pin direction, read, write |
| `timers.c / timers.h` | Timer configuration, PWM generation, delay |
| `interrupt.c / interrupt.h` | Global/peripheral interrupt enable/disable |
| `registers.h` | Raw register definitions and bit-manipulation macros |
| `std_types.h` | Portable type definitions (`uint8_t`, `uint16_t`, etc.) |
| `macros.h` | SET_BIT, CLR_BIT, TOG_BIT, GET_BIT helpers |

### HAL Layer — Hardware Abstraction

Peripheral drivers built on top of MCAL — hardware-independent interfaces:

| Module | Functionality |
|---|---|
| `lcd.c / lcd.h` | 4-bit LCD init, send command, print string/integer |
| `servo.c / servo.h` | Set servo angle via software PWM delays |
| `ultrasonic.c / ultrasonic.h` | Trigger pulse, echo timing, distance calculation |
| `dc_motor.c / dc_motor.h` | Forward, reverse, stop, speed via PWM duty cycle |

### APP Layer — Application Logic

```
main.c
```

The autonomous driving state machine:

```
IDLE → drive forward
    → obstacle detected (distance < threshold)
        → stop motors
        → servo scan LEFT  → measure distance_left
        → servo scan RIGHT → measure distance_right
        → servo return CENTER
        → if distance_left > distance_right: steer LEFT
          else: steer RIGHT
        → resume forward
```

---

## ⚙️ Key Implementation Details

### Servo Control — Software PWM

Timer 1's input capture unit was needed by the ultrasonic sensor, making hardware PWM for the servo impossible without conflict. The servo is instead driven via **calibrated software delays**:

### Ultrasonic Distance Measurement

A trigger pulse is sent for 10 microseconds, then the echo pulse is measured and used to calculate the distance.

### 4-Bit LCD Mode

To work within the pin constraints of the AMIT learning kit, the LCD is driven in **4-bit mode** — each byte is sent as two 4-bit nibbles, halving the GPIO lines required.

---

## 🧩 Challenges & How They Were Solved

### 1. Timer Resource Conflict — Servo vs. Ultrasonic
**Problem:** Both the servo (PWM) and ultrasonic (echo timing) required Timer 1's input capture unit simultaneously.

**Solution:** Moved servo control to **software delay-based PWM**, freeing Timer 1 exclusively for echo pulse timing. This gave the ultrasonic sensor deterministic, accurate timing while keeping servo control functional.

### 2. DC Motor H-Bridge Failure
**Problem:** The DC motors would not respond to the H-bridge module. After extensive simulation testing, the H-bridge was confirmed non-functional with the available hardware.

**Solution:** Rewired the motors directly to GPIO + PWM output pins. Speed is controlled via PWM duty cycle; direction is fixed to forward drive. The aged motors also required higher supply voltage than the kit's default — power supply was adjusted accordingly.

### 3. LCD 4-Bit Mode Configuration
**Problem:** The AMIT learning kit's limited GPIO required a non-standard LCD wiring scheme not covered in coursework.

**Solution:** Implemented full 4-bit LCD protocol from scratch — init sequence, nibble-split data transmission, enable pulse timing — entirely from the HD44780 datasheet.

---

## 📁 Repository Structure

```
AVR-SelfDrivingCar/
├── APP/
│   └── main.c                  # Autonomous driving state machine
├── HAL/
│   ├── LCD/
│   │   ├── lcd.c
│   │   └── lcd.h
│   ├── Servo/
│   │   ├── servo.c
│   │   └── servo.h
│   ├── Ultrasonic/
│   │   ├── ultrasonic.c
│   │   └── ultrasonic.h
│   └── DC_Motor/
│       ├── dc_motor.c
│       └── dc_motor.h
├── MCAL/
│   ├── DIO/
│   │   ├── dio.c
│   │   └── dio.h
│   ├── Timers/
│   │   ├── timers.c
│   │   └── timers.h
│   ├── Interrupt/
│   │   ├── interrupt.c
│   │   └── interrupt.h
│   └── Registers/
│       └── registers.h
├── Utils/
│   ├── std_types.h
│   └── macros.h
└── README.md
```

---

## 🚀 Getting Started

### Prerequisites

- AVR-GCC toolchain
- AVRDUDE (for flashing)
- ATmega development board (AMIT kit or equivalent)

### Build & Flash

```bash
# Compile
avr-gcc -mmcu=atmega32 -Os -o main.elf APP/main.c HAL/**/*.c MCAL/**/*.c

# Convert to hex
avr-objcopy -O ihex main.elf main.hex

# Flash to MCU
avrdude -c usbasp -p m32 -U flash:w:main.hex
```

---

## 🧩 Skills Demonstrated

| Domain | Demonstrated Skills |
|---|---|
| **Embedded C** | Bare-metal AVR register programming, bit manipulation, peripheral configuration |
| **Firmware Architecture** | 3-layer MCAL / HAL / APP driver stack — industry-standard embedded design pattern |
| **Timers & PWM** | Timer configuration, PWM generation, microsecond delay implementation |
| **Sensor Integration** | HC-SR04 ultrasonic trigger/echo timing, distance calculation |
| **Peripheral Drivers** | LCD (4-bit mode), servo motor, DC motor, GPIO from scratch |
| **Debugging** | Hardware/simulation co-debugging, H-bridge fault isolation, resource conflict resolution |

---

## 👥 Team

| Name | Role |
|---|---|
| **Bassel Khaled Abdelhaleem** | Embedded firmware, driver stack, hardware debugging |
| **Malak Khaled Ibrahim** | Embedded firmware, hardware debugging |

---

<p align="center">
  <i>No framework. No abstractions. Just registers, patience, and C.</i>
</p>
