# scorpion-mips-arm

## Repo layout

```
scorpion-mips-arm/
├── README.md
├── CLAUDE.md
├── SKELETON.md                   # scaffold spec
├── .gitignore
├── mips/                         # hand-written MIPS (runs in MARS)
│   ├── scorpion.asm              # main program
│   ├── joints.asm                # joint table accessors
│   ├── pwm.asm                   # angle -> pulse width
│   └── tests/
│       └── test_pwm.asm
├── reference/                    # C version, written first, hand-translated to mips/
│   ├── scorpion.c
│   ├── joints.c
│   └── pwm.c
├── bridge/                       # Python: controller/keyboard -> MARS -> ESP32
│   ├── bridge.py
│   ├── config.py
│   ├── requirements.txt
│   └── tests/
│       └── fake_esp32.py
├── firmware/
│   └── scorpion_esp32/           # ESP32 Arduino sketch (drives the servos)
│       ├── scorpion_esp32.ino
│       └── config.h
├── tools/                        # hardware/protocol test scripts
│   ├── servo_test.py
│   └── protocol_check.py
└── docs/
    ├── setup.md                  # install guide
    ├── protocol.md               # serial protocol
    ├── user-guide.md
    ├── report.md
    └── wiring/
        └── pin-table.md
```
