# 🎲 Two-Player Arduino Dice Game with 7‑Segment Display

## Table of Contents
1. Overview
2. Features
3. Hardware Requirements
4. Wiring Summary
5. Game Logic
6. How the Two-Player Mode Works
7. LED Indicator Logic (Rolling a Six)
8. Button Behavior
9. How to Use
10. Customization Ideas
11. Notes & Troubleshooting

---

## 1. Overview
This project is a **two-player electronic dice game** built using an Arduino, a **single 7‑segment display**, two push buttons, a buzzer, and an LED indicator.

Each player rolls the dice using their own button. The result (1–6) is displayed on the 7‑segment display, and **when a player rolls a six, an LED lights up** to signal the special outcome.

This project is designed to be beginner-friendly, deterministic, and easy to extend.

---

## 2. Features
- Two-player input using two buttons
- Random dice roll (1–6)
- 7‑segment display output
- Buzzer feedback during rolls
- LED indicator when a six is rolled
- Clean, stable logic (no dynamic pin flipping)

---

## 3. Hardware Requirements
- Arduino Uno (or compatible)
- 1× 7‑segment display (common cathode or anode)
- 7× current-limiting resistors (220Ω–330Ω)
- 2× push buttons (Player 1 & Player 2)
- 1× LED + resistor
- 1× buzzer
- Breadboard & jumper wires

---

## 4. Wiring Summary

### 7‑Segment Display
- Each segment (a–g) is connected to a **dedicated Arduino pin** through a resistor
- Common pin:
  - **Common cathode** → GND
  - **Common anode** → 5V

### Buttons
- Player 1 button → A0
- Player 2 button → A1
- Buttons use `INPUT_PULLUP` and connect to **GND** when pressed

### LED Indicator
- LED connected to **pin 12**
- Includes a current-limiting resistor

### Buzzer
- Buzzer connected to **pin 10**

---

## 5. Game Logic
- When a button is pressed, a random number between **1 and 6** is generated
- The number is displayed on the 7‑segment display
- A short buzzer sound plays during the roll
- The system waits briefly to debounce the button

---

## 6. How the Two-Player Mode Works
- Each player has **their own button**
- Either player can roll at any time
- The display always shows the **most recent roll**
- Serial messages indicate which player rolled

This design keeps the hardware simple while allowing fair, turn-based play.

---

## 7. LED Indicator Logic (Rolling a Six)
- The LED turns **ON** whenever the displayed number is **6**
- The LED turns **OFF** for all other numbers

This provides an immediate visual cue for a special roll without affecting gameplay.

---

## 8. Button Behavior
- Buttons use Arduino’s internal pull-up resistors
- Logic state:
  - `LOW` → button pressed
  - `HIGH` → button released

A short delay is used after each roll to prevent accidental multiple triggers.

---

## 9. How to Use
1. Power the Arduino
2. Press Player 1 or Player 2 button
3. Watch the dice roll animation
4. View the result on the 7‑segment display
5. If a six is rolled, the LED lights up

---

## 10. Customization Ideas
- Add separate LEDs for each player
- Track and display player scores
- Add win conditions (first to roll six)
- Use multiple 7‑segment displays
- Add animations or blinking effects

---

## 11. Notes & Troubleshooting
- Ensure each segment has its **own resistor**
- Confirm the display type (common anode vs cathode)
- Avoid changing logic levels dynamically
- If segments don’t light, verify pin mapping

---

### ✅ Project Status
Stable, working, and ready for extension.

This project demonstrates clean embedded logic, proper hardware interfacing, and scalable design — a solid foundation for more advanced Arduino games.

