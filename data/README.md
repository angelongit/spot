# Spot: Data

This folder holds every motion recording from Spot. It explains the file-naming rule, the folder layout, and which recordings may be used for scoring.

## The one rule that matters

**Only held-out recordings are used to score the requirements.** A held-out recording is one made *after* the counter code and its settings were frozen with a Git tag (for example `counter-v1-frozen`). Everything else is **tuning data**: it can be used to design, tune and debug the counter, but never to claim a requirement passed. See `docs/Spot_Requirements_v1.3.md`, section 2.3, and `docs/DECISIONS.md` D-007.

If the counter changes after testing, the held-out recordings that were used become tuning data, and new held-out recordings are made.

## Folder layout

```
data/
├── tuning/                               # all recordings made before a counter freeze
│   ├── Dumbbell_Curls/Initial_Testing/   # Oct 16, 2026: curls on the end-face mount, 100 Hz
│   └── No_Dumbell/                       # earliest recordings, wrist only, no dumbbell
└── heldout/                              # held-out recordings only (none yet)
    └── counter-v1-frozen/                # one folder per frozen counter version (the Git tag name)
        └── 2026-11-02_session1/
            ├── sets/                     # one CSV per set, named by the rule below
            ├── noise/                    # one CSV per noise recording
            └── session.json              # date, firmware tag, dumbbell, hand, notes
```

Anything outside `heldout/` is tuning data. **Videos are never committed** (size and privacy); they stay on the developer's computer, and `.gitignore` blocks common video formats.

The scores for every held-out session go in **`docs/Spot_Test_Log_v1.2.xlsx`**, one row per set, rest period, noise recording and movement.

## File-naming rule

**Sets (R1, R3, R4, R6):**

```
<exercise>_<hand>_<speed>_<form>_<NN>reps_<YYYYMMDD>_<HHMM>.csv
```

| Part | Allowed values |
|---|---|
| `exercise` | `curl`, `raise`, `press` |
| `hand` | `L` or `R`, the hand holding the dumbbell with the pod |
| `speed` | `slow`, `normal`, `fast` |
| `form` | `clean`, `momentum`, `mixed` (full reps followed by 2–4 partials) |
| `NN` | planned full reps, two digits: `06`, `08`, `12` |
| date and time | when the set was recorded, 24-hour time |

Example: `curl_R_normal_mixed_08reps_20261102_1405.csv`

The planned rep count in the name is a **target only**. The true count is the number of full reps the video shows (the video-reviewed count; partials are not counted as reps), and it goes in the test log, never in the file name.

**Noise recordings (R2):**

```
<mode>_noise_<types>_<YYYYMMDD>_<HHMM>.csv
```

`mode` is the exercise selected on Spot. `types` lists the noise actions joined by hyphens, for example `curl_noise_pickup-carry_20261102_1420.csv`. Use these short names: `handle`, `walk`, `pickup`, `carry`, `setdown`, `small`, `grip`, `kickup` (press only), and add `-between` when the recording was made between two real sets.

## CSV columns

| Column | Unit | Meaning |
|---|---|---|
| `t_ms` | ms | time since Spot started, from the board's clock |
| `ax`, `ay`, `az` | g | accelerometer, three axes |
| `gx`, `gy`, `gz` | deg/s | gyroscope, three axes |

Recordings from the current XIAO logger are at 100 Hz (a sample every 10 ms). The untethered logger (R7) will add a sample counter column so lost data can be detected.

## Existing recordings (all tuning data)

These were recorded before any counter was frozen. **None of them may be used to score a requirement.**

| File | Notes |
|---|---|
| `Dumbbell_Curls/Initial_Testing/curl_normal_set_8_reps.csv` | 100 Hz, curl, end-face mount |
| `Dumbbell_Curls/Initial_Testing/curl_normal_set_10_reps.csv` | label is questionable: the count on video should be checked |
| `Dumbbell_Curls/Initial_Testing/curl_normal_set_12_reps.csv` | |
| `Dumbbell_Curls/Initial_Testing/curl_momentum_10reps_20261016_210242.csv` | the only momentum recording so far |
| `Dumbbell_Curls/Initial_Testing/curl_partial_10reps_20261016_211012.csv` | |
| `Dumbbell_Curls/Initial_Testing/curls_incomplete_error.csv` | incomplete recording, kept for reference |
| `Dumbbell_Curls/Initial_Testing/noise_handling_0reps_20261016_211431.csv` | noise, 0 reps |
| `Dumbbell_Curls/Initial_Testing/noise_between_sets_0reps_20261016_211539.csv` | noise between sets, 0 reps |
| `No_Dumbell/curl_10reps_01_normal_speed.csv`, `_02_`, `_03_` | wrist only, no dumbbell |
| `No_Dumbell/curl_10reps_fast.csv`, `curl_10reps_slow.csv` | wrist only, no dumbbell |
| `No_Dumbell/wrist_noise.csv` | wrist only, noise |

These files keep their original names. Renaming them to the new rule is optional; if you do, record the old name in the Notes column of the test log.
