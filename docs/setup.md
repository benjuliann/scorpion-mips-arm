# Quick Setup

Get a Windows laptop ready to run The Scorpion. Run all commands from the repo root.

## What you need

| Tool | Used for | Needed by |
|------|----------|-----------|
| Git | Cloning the repo | Everyone |
| Java (JRE/JDK 8+) | Running MARS | Everyone |
| MARS 4.5 (`Mars.jar`) | Running the MIPS program | Everyone |
| Python 3.10+ | Bridge and test tools | Everyone |
| Arduino IDE 2 + ESP32 board package | Uploading firmware | Whoever flashes the ESP32 |
| USB-serial driver (CP210x or CH340) | Talking to the ESP32 | If the ESP32 doesn't show up as a COM port |
| C compiler (optional) | Building `reference/*.c` | Whoever writes the C reference |

Check what you already have:

```
git --version
java -version
python --version
```

## 1. Clone the repo

```
git clone <repo-url>
cd scorpion-mips-arm
```

## 2. MARS

1. Download `Mars4_5.jar` from the MARS website (Missouri State University).
2. Save it as `tools/Mars.jar`. This is the path `bridge/config.py` expects.
3. Test it: `java -jar tools/Mars.jar nc mips/scorpion.asm`. It should exit with no errors.

## 3. Python

```
python -m venv .venv
.venv\Scripts\activate
pip install -r bridge/requirements.txt
```

This installs `pyserial` (talks to the ESP32) and `pygame` (reads the controller and the keyboard).

- Activate the venv (`.venv\Scripts\activate`) every time you open a new terminal.
- Don't commit `.venv/`.

## 4. ESP32 firmware

1. Install **Arduino IDE 2**.
2. **File > Preferences > Additional boards manager URLs**, add:
   `https://espressif.github.io/arduino-esp32/package_esp32_index.json`
3. **Tools > Board > Boards Manager**, install **esp32 by Espressif Systems**.
4. **Sketch > Include Library > Manage Libraries**, install **ESP32Servo** (unless the team decides to use LEDC directly).
5. Plug in the ESP32. In **Device Manager > Ports (COM & LPT)**, note its COM port.
   - If no port appears, install the CP210x or CH340 driver. Check the chip on your board to see which one.
6. Open `firmware/scorpion_esp32/scorpion_esp32.ino`, pick your board and COM port, then **Upload**.

## 5. Point the bridge at your ESP32

Edit `bridge/config.py` and set `SERIAL_PORT` to your COM port (e.g. `"COM5"`). Don't commit your own port number.

## 6. Controller

- Plug in or pair the controller before starting the bridge. Xbox and PlayStation controllers both work with `pygame`.
- If no controller is found, use the keyboard instead (backup input). The bridge window must have focus for key presses to register.

## Safety before powering the arm

- Servos run from the **separate 5-6 V supply**, never from the ESP32 or USB.
- Connect the supply ground to the ESP32 ground.
- Keep hands clear on first power-up; the servos can jump to position.
- See [wiring/pin-table.md](wiring/pin-table.md).

## Quick check

| Step | Command | Expected |
|------|---------|----------|
| MARS runs | `java -jar tools/Mars.jar nc mips/scorpion.asm` | Exits, no errors |
| Python deps | `python -c "import serial, pygame"` | No errors |
| ESP32 replies | `python tools/protocol_check.py` | All replies match (once implemented) |
