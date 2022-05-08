# KiCAD files for the project.

Contains both PCBs and mounting parts. PCBs ordered from JLCPCB, mounting parts
laser-cut ordered from Sculpteo.

* `led-matrix-pcbs`:
  * Main PCB, hosting the LEDs and the LED drivers. Each PCB contains 12 RGB
  LEDs in a 3x4 grid (36 LEDs total).
  * With 24 PCBs aranged in a 6x4 grid, one can get a 16x16 grid of RGB LEDs.
  * Each LED on a PCB is controlled via the onboard driver. The driver is
  controlled by a I2C interface, for which pinout is available on the PCB. The
  I2C address of the driver can be adjusted via the ADR pin (see driver
  datasheet).
* `led-matrix-bridge-pcbs`:
  * Connector PCB to join the `led-matrix-pcbs`. Each connector PCB can connect
  4 `led-matrix-pcbs` on a row.
  * This highly simplifies the I2C connections, the ADR configuration, and
  power delivery.
  * Connection between `led-matrix-pcbs` and `led-matrix-bridge-pcbs` is easy
  with pin headers.
  * With 6 PCBs, one can connect 6 rows of 4 `led-matrix-pcbs` to reach 256 RGD
  LEDs.
  * `led-matrix-bridge-pcbs` are easily connected to each other for power
  and for the SCL line of the I2C protocol. Pinout is available for the SDA line
  of the I2C protocol.
* `spacers-laser-cut`:
  * Design for laser-cut plates that hold the PCBs while letting the light of
  the LEDs through.

The main controller (that gives instructions to the LED drivers) is an Arduino
Nano Every. Timekeeping is performed by a DS3231M (breakout board from DFRobot).

## Bill of Materials

### Mounting parts

Laser-cut plates (Scultpeo):
  * 1x backplate-decor, MDF 3mm
  * 1x spacer-mount-leds, Ondulated cardboard 2.8mm
  * 1x spacer-mount-leds, Standard MDF 3mm
  * 2x spacer-nomount-leds-solderjoints, Grey compact cardboard 1mm

Screws (vis-express):
  * Screw M1.6X16 inox
  * Bolt M1.6 inox
  * Washer M2 nylon

### PCBs

PCBs (JLCPCB):
  * 24x led-matrix-pcbs, FR4 1.6mm
  * 6x led-matrix-bridge-pcbs, FR4 1.6mm

Electronic components (ordered from Mouser and hand-solder, or assembled by JLCPCB):

Count | Part description    | Manufacturer reference | Manufacturer | Odered from
------|---------------------|----------------|--------------|---------------------------
256 | RGB LED               | IN-P32TATRGB   | Inolux   | Mouser
24  | 36 channel LED driver | IS31FL3236A    | Integrated Silicon Solution | JLCPCB (C246443)
24  | 100 kOhm              | 0603WAF1003T5E | Uniroyal | JLCPCB (C25803)
24  | 3.83 kOhm             | 0603WAF3831T5E | Uniroyal | JLCPCB (C22982)
24  | 4.7 kOhm              | 0603WAJ0472T5E | Uniroyal | JLCPCB (C25999)
48  | 100 nF                | CC0603KRX7R9BB104 | Yageo | JLCPCB (C14663)
24  | 1 uF                  | CL10A105KB8NNNC | Samsung Electro-Mechanics | JLCPCB (C15849)


## Stack layers of PCB, mounting, components:

```
..........................................................  glass window
------------------          ------------------------------  paper with letter matrix cutout
~~~~~~\    /~~~~~~          ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  ondulated cardboard (spacer-mount-leds)
       \__/                                                 16mm screw
XXXXXXXX||XXXXXXXX          XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX  MDF (spacer-mount-leds)
XXXXXXXX||XXXXXXXX          XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
XXXXXXXX||XXXXXXXX \light / XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
::::::::||:::::     \cone/     ::::::::::    :::::::::::::  Compact cardboard  (spacer-nomount-leds-solderjoints)
::::::::||::::: __==========__ :::::::::: /\ :::::::::::::  Compact cardboard  (spacer-nomount-leds-solderjoints)
        ||    _/     LED      \_        _/  \_              Solder joints and LEDs
========||===============================|  |=============  PCB (led-matrix-pcbs)
========||===============================|  |=============
        ||                               |  |               Connector pin
        ||                               |  |
        ||                               |  |
========||===============================|  |=============  PCB (led-matrix-bridge-pcbs)
========||===============================|  |=============
      --||--                             \  /               Solder joints, screw washer
      BB||BB                              \/                Screw bold
        ||
```
