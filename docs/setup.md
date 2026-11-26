# Quick Setup

Get a Windows laptop ready to run The Scorpion. Run all commands from the repo root.

## What you need

| Tool | Used for | Needed by |
|------|----------|-----------|
| Git | Cloning the repo | Everyone |
| Java (JRE/JDK 8+) | Running MARS | Everyone |
| MARS 4.5 (`tools/Mars.jar`, already in the repo) | Running the MIPS program | Everyone |
| Python 3.10+ | Bridge and test tools | Everyone |
| VS Code + PlatformIO (or Arduino IDE 2) | Uploading firmware | Whoever flashes the ESP32 |
| USB-serial driver (CP210x or CH340) | Talking to the ESP32 | If the ESP32 doesn't show up as a COM port |
| C compiler, e.g. gcc (optional) | Building and testing `reference/*.c` | Whoever writes the C reference |

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

1. MARS 4.5 is committed at `tools/Mars.jar`. This is the path `bridge/config.py` expects. Nothing to download.
2. Test it: `java -jar tools/Mars.jar nc mips/scorpion.asm`. It should exit with no errors.

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

Plug in the ESP32. In **Device Manager > Ports (COM & LPT)**, note its COM port.
- If no port appears, install the CP210x or CH340 driver. Check the chip on your board to see which one.

### Option A: PlatformIO (recommended)

The firmware folder is a PlatformIO project (`firmware/scorpion_esp32/platformio.ini`, board `esp32dev`). PlatformIO installs the ESP32 platform and the `ESP32Servo` library on the first build.

1. Install **VS Code**, then the **PlatformIO IDE** extension (VS Code suggests it when you open the folder).
2. **File > Open Folder**, pick `firmware/scorpion_esp32` (not the repo root).
3. Click **Upload** (→) in the bottom status bar. PlatformIO picks the COM port automatically; if it picks the wrong one, set `upload_port` in `platformio.ini` locally and don't commit it.
4. **Serial Monitor** (plug icon) opens at 115200 baud. Type a command (e.g. `PING`) and press Enter.

### Option B: Arduino IDE 2

1. Install **Arduino IDE 2**.
2. **File > Preferences > Additional boards manager URLs**, add:
   `https://espressif.github.io/arduino-esp32/package_esp32_index.json`
3. **Tools > Board > Boards Manager**, install **esp32 by Espressif Systems**.
4. **Sketch > Include Library > Manage Libraries**, install **ESP32Servo** (unless the team decides to use LEDC directly).
5. Open `firmware/scorpion_esp32/scorpion_esp32.ino`, pick **ESP32 Dev Module** and your COM port, then **Upload**.

## 5. C reference tests (optional)

```
gcc reference/tests/test_reference.c reference/joints.c reference/pwm.c -o test_reference
./test_reference
```

Exit code 0 means all tests passed. The compiled binary is ignored by git; don't commit it.

## 6. Point the bridge at your ESP32

Edit `bridge/config.py` and set `SERIAL_PORT` to your COM port (e.g. `"COM5"`). Don't commit your own port number.

## 7. Controller

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
| C reference | `./test_reference` (after building, step 5) | Exit code 0 |
| ESP32 replies | `python tools/protocol_check.py` | All replies match (once implemented) |
