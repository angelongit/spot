# Spot

Equipment-mounted rep counter with real-time form feedback, built on the Seeed XIAO nRF52840 Sense.

Spot is a small motion-sensing pod that attaches to the end of a dumbbell. It measures how the dumbbell moves during each set and turns that motion into a rep count, rest times and form flags. The goal for v1 is to count reps and time rest correctly against video, and more accurately than a fitness watch.

## Status

**Requirements v1.3 complete; collecting tuning data.** Curl recordings exist; lateral raise and chest press tuning recordings are next, followed by untethered logging (R7) and the counter itself.

## What v1 does

- Counts **full reps** for the dumbbell curl (supinated grip), lateral raise and chest press, with the pod on a dumbbell in either hand. Momentum reps count; **partial reps do not**.
- Ignores movement that isn't an exercise (picking up, carrying, setting down, adjusting grip).
- Detects sets and times rest automatically.
- Selects the exercise with one button, shown by LED colour and blink count.
- Measures each rep's duration, flags partial reps (with an LED cue) and momentum reps.
- Records a whole session on battery with no cable.
- Must count more accurately than a Garmin Forerunner 165.

Every requirement has a number and a test: see [the requirements](docs/Spot_Requirements_v1.3.md). Results are scored against video, only on held-out data recorded after the counter is frozen.

## Repository layout

| Folder | Contents |
|---|---|
| [`docs/`](docs) | Requirements (`.md` to read here, `.docx` original), [decision log](docs/DECISIONS.md), [background](docs/background.md), training-science notes, test log spreadsheet, project log, concept images |
| [`firmware/`](firmware) | Arduino sketches. `spot_logger_strapped` is the current XIAO logger (100 Hz CSV over USB); the `mpu6050_*` and `i2c_scanner` sketches are earlier Arduino Mega + MPU6050 experiments |
| [`scripts/`](scripts) | Python scripts that save one set of IMU data per CSV file over USB |
| [`data/`](data) | Motion recordings and the [naming rules](data/README.md). Everything here so far is tuning data |

## Hardware

- Seeed XIAO nRF52840 Sense (LSM6DS3 6-axis IMU: accelerometer and gyroscope; no magnetometer)
- 10 lb rubber-coated hex dumbbells
- Planned mount: a steel plate bonded to the dumbbell's end face with 3M VHB tape, held by magnets in the pod
