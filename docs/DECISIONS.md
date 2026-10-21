# Spot — Decision Log

This log records the design and testing decisions behind Spot v1: what was chosen, why, and what was rejected. The requirements live in `Spot — Requirements.docx`; this file explains how they came to be. New decisions are added at the bottom with the next number, and a changed decision gets a new entry that points back to the one it replaces. Old entries are never edited.

**Format:** each entry has the decision, the reason, the alternatives considered, and the requirements it affects.

---

## Scope and hardware

### D-001 · Three exercises, all must-haves (2026-10-20)
- **Decision:** v1 covers dumbbell curl, dumbbell chest press and dumbbell lateral raise. All three are must-haves and share one counting pipeline.
- **Why:** three exercises with different motion (elbow rotation, shoulder abduction, vertical press) show the method generalises; a shared pipeline keeps the work manageable with no deadline pressure.
- **Alternatives:** curl only (too narrow to prove the idea); per-exercise pipelines (three times the work).
- **Affects:** R1a–R1c, R2, R3, R6.

### D-002 · Exercise chosen with a button, no automatic detection (2026-10-20)
- **Decision:** the user selects the exercise by pressing a center button that cycles curl → press → lateral raise. The phone app is deferred to winter break.
- **Why:** automatic exercise detection is a separate, harder problem; a button avoids building an app during the semester.
- **Alternatives:** selection in a phone app (adds app work now); automatic detection (out of scope).
- **Affects:** R5, N1, Out of scope.

### D-003 · Board: Seeed XIAO nRF52840 Sense at 100 Hz
- **Decision:** the XIAO nRF52840 Sense is the v1 board, with its IMU logged at 100 Hz.
- **Why:** small, has an IMU, BLE and on-board flash. Its IMU is motion-only (no magnetometer), so magnets in the mount do not affect the data.
- **Note:** the older Arduino Mega sketch ran at 75 Hz; 100 Hz is current.
- **Affects:** R7, Constraints.

### D-004 · Mount on the dumbbell's end face with a steel plate and VHB tape (2026-10-20)
- **Decision:** the pod mounts on the end face of the hex dumbbell (CAP 10 lb rubber-coated). A steel plate or fender washer is bonded to the end face with 3M VHB tape (5952, optional Primer 94), and the pod's magnets grip the plate.
- **Why:** the end face never touches the hand, and the mount is easy to attach and remove.
- **Alternatives:** strap socket around the handle (rejected, blocks the grip); a magnet directly on the dumbbell (a fridge magnet did not hold).
- **Open:** whether VHB holds on the rubber coating is untested.
- **Affects:** Section 3, Constraints.

### D-005 · Budget and deadline (2026-10-21)
- **Decision:** budget is open, ideally under $50 in parts. A working prototype by the end of the Fall 2026 semester is preferred, not required.
- **Affects:** Constraints.

---

## Testing method

### D-006 · Video-reviewed count is ground truth (2026-10-20)
- **Decision:** the true rep count is what a reviewer counts on video, before looking at Spot's count. The planned rep count is only a target. Any set where Spot differs by 2 or more reps gets a second look at the video.
- **Why:** lifters don't always do the reps they plan; counting before seeing Spot's number avoids bias toward Spot.
- **Affects:** R1–R6, Definitions.

### D-007 · Held-out sets and a frozen counter (2026-10-20)
- **Decision:** the counter code and all its settings are tagged in Git (for example `counter-v1-frozen`) before test recordings. Only sets recorded after the tag are scored. If the counter changes after testing, the sets used become tuning sets and new held-out sets must be recorded.
- **Why:** scoring on data used for tuning overstates accuracy.
- **Affects:** R1–R7, Definitions.

### D-008 · Pass rates as percentages (2026-10-20)
- **Decision:** requirements state a percentage of sets or reps, not a fixed count.
- **Why:** the number of recorded sets can grow without rewriting the requirement.

### D-009 · Tiered rep-count tolerance (2026-10-21)
- **Decision:** Spot's count is within ±1 rep of the video count on at least 90% of held-out sets, and within ±2 reps on every held-out set.
- **Why:** states both a target and a hard floor; with 27 sets, 25 must be within ±1.
- **Alternatives:** ±1 only (one miss allowed in 18 sets, very strict); ±2 only (up to 25% error on an 8-rep set, too loose to beat a smartwatch convincingly).
- **Affects:** R1a–R1c.

### D-010 · R1 test matrix and shared procedure (2026-10-21)
- **Decision:** per exercise, 3 speeds (slow, normal, fast) × 3 forms (clean, momentum, partial), 3 sets per combination with 6, 8 and 12 planned reps: at least 27 sets per exercise. One shared "Test Procedure R1" covers all three exercises; each row lists only what is exercise-specific.
- **Why:** momentum reps happen in real gym sets and must still be counted; one shared procedure can't drift out of sync.
- **Alternatives:** 2 forms (18 sets), dropped because momentum sets were missing; a separate procedure per exercise (redundant).
- **Affects:** R1a–R1c, R4, R6.

### D-011 · Rest timing (2026-10-21)
- **Decision:** rest is measured within ±5 s of video on at least 90% of at least 20 held-out rest periods per exercise, for rests of 30 s to 5 minutes. Rest boundaries come from the video's counted reps, not Spot's. Spot back-dates both ends of a rest to the rep boundaries. Extra held-out sets are recorded so each exercise has at least 21 consecutive sets.
- **Why:** ±3 s was too rigid for rest times people actually care about; using video boundaries keeps a counting error from being scored as a rest error.
- **Alternatives:** ±3 s; hand timer (rejected, less accurate than video).
- **Affects:** R3.

### D-012 · Automatic set and rest detection by stillness timeout (2026-10-21)
- **Decision:** a set ends when no rep starts within a stillness timeout (15 s placeholder). The timeout is frozen with the counter.
- **Why:** no button press needed between sets.
- **Note:** the "at least 4 reps" rule is Garmin's limit, used only in the R4 test, not a Spot rule.
- **Affects:** R3, R5, Definitions.

### D-013 · Noise rejection (2026-10-21)
- **Decision:** Spot counts 0 reps on every one of at least 20 held-out noise sets per exercise mode, and no noise set starts a new set. Noise types include handling, walking, picking up, carrying, setting down for 2–10 s, small movements below the 30° floor, adjusting grip and (press) kicking the dumbbells up. At least 5 of the 20 per mode are recorded between real sets. Existing noise recordings are tuning data.
- **Why:** false counts are the failure users notice most.
- **Alternatives:** 19 of 20 (less strict).
- **Affects:** R2.

### D-014 · Comparison with the Garmin Forerunner 165 (2026-10-21)
- **Decision:** on the R1 held-out sets, Spot's mean absolute count error must be lower than the watch's, per exercise. The watch is worn on the wrist holding the dumbbell, each set is ended with BACK, the count is recorded unedited, and a set the watch doesn't count is scored as 0.
- **Why:** the watch's inaccuracy is the reason Spot exists.
- **Affects:** R4.

### D-015 · Exercise button and LED (2026-10-21)
- **Decision:** curl = blue (1 blink), press = red (2 blinks), lateral raise = green (3 blinks), readable from 1 m. Spot starts in curl on every power-up. The mode locks while a set is in progress. Test: 30 presses, 3 power cycles, a visibility check and a lockout check, all must pass.
- **Why:** the blink count is a second cue for colour-blind users or bright light; a fixed default is predictable because users won't remember the last mode; the lock stops a bump from changing the mode mid-set.
- **Alternatives:** remember the last mode (rejected).
- **Affects:** R5.

---

## Form feedback

### D-016 · v1 form scope (2026-10-21)
- **Decision:** must-haves are tempo on all three exercises (R6a: rep duration within ±0.5 s on 90% of reps) and a per-rep partial flag for curl and lateral raise (R6b: flags at least 90% of partial reps, at most 10% of full reps). Rep consistency is calculated from rep durations, not tested separately.
- **Why:** both reuse the R1 recordings; per-rep scoring gives about 78 partial reps per exercise instead of 9 sets.
- **Alternatives:** per-set flag (9 partial sets means all 9 must pass).
- **Affects:** R6a, R6b.

### D-017 · Partial-rep cue is an LED flash (2026-10-21)
- **Decision:** a flagged rep gives a single 0.5 s white LED flash within 1 s of the end of the rep. White is not used by the mode colours.
- **Alternatives:** buzzer (the board has no speaker; it needs extra hardware and gym noise may mask it), moved to nice-to-haves.
- **Affects:** R6b, N5.

### D-018 · Deferred to nice-to-haves (2026-10-21)
- **Decision:** phone app and BLE (N1), chest-press partial flag (N2), chest-press range of motion (N3), absolute-degree range of motion (N4, needs gyro drift correction), buzzer (N5) and momentum flag (N6, detection unproven).

---

## Definitions

### D-019 · Rep definitions (2026-10-21)
- **Decision:**
  - A rep starts at the first movement away from the starting position and ends at the return to it, judged on video. "Returned" means within about 10° of the starting angle (curl, raise) or dumbbells back at chest level (press).
  - Curl and lateral raise: full rep at least 70° (parallel is about 90°); partial rep 30° to 70°; below 30° is not a rep.
  - Chest press: partial is between a quarter and a half of the way from chest to full extension; below a quarter is not a rep.
  - A partial rep still counts as a rep; the flag is additional.
  - Momentum: the weight is moved by swinging or bouncing it instead of the target muscle alone, with exercise-specific wording.
- **Why:** every requirement needs a rule that can be judged on video.
- **Affects:** Definitions, R1, R2, R6.

---

## Data logging

### D-020 · Untethered logging to on-board flash (2026-10-21)
- **Decision:** v1 must record a full test session (at least 30 sets of up to 60 s) on battery with no cable. Raw motion data at 100 Hz is logged during each set (plus about 2 s before and after), along with Spot's results. Data is downloaded over USB afterwards. The 2 MB on-board flash is used; no SD card for initial testing.
- **Why:** gym testing can't use a USB cable. Raw data is more honest than results only and allows failed sets to be debugged.
- **Alternatives:** results only (rejected, can't debug); microSD card (deferred, only if the session doesn't fit); BLE streaming (needs the app).
- **Risk:** 2 MB holds roughly 22–29 minutes of raw data, so a 30-set session may not fit. The R7 test answers this.
- **Affects:** R7, Constraints.

### D-021 · Video sync by three taps (2026-10-21)
- **Decision:** at the start of each session, tap the pod three times on camera. The spikes in the data align Spot's clock with the video to within 0.1 s.
- **Why:** free, no extra hardware, easy to see in both the video and the data.
- **Affects:** R7.

---

## Data and records

### D-022 · File naming and folder layout (2026-10-21)
- **Decision:** set files are named `<exercise>_<speed>_<form>_<NN>reps_<YYYYMMDD>_<HHMM>.csv` and noise files `<mode>_noise_<types>_<YYYYMMDD>_<HHMM>.csv`. Held-out recordings go in `Data/heldout/<counter tag>/<date>_session<N>/`. Existing recordings keep their names and locations and are all tuning data.
- **Why:** every file says what it is without opening it, and held-out data can never be confused with tuning data.
- **Affects:** Test Procedure R1, R2, `Data/README.md`.

### D-023 · One test log for all scoring (2026-10-21)
- **Decision:** all held-out results are recorded in `Spot_Test_Log_v1.xlsx`: one row per set (R1, R4), rest period (R3), noise recording (R2) and rep (R6). A Summary tab applies the pass rules. R5 and R7 are pass/fail checks recorded in the Project Log.
- **Why:** the pass rules are applied the same way every time, and the video count is entered before Spot's count.
- **Affects:** R1–R4, R6.

### D-024 · Tuning recordings over USB before untethered logging (2026-10-21)
- **Decision:** collect tuning data for the lateral raise and chest press (and a few curl momentum sets) with the current USB setup now, before R7 is built. The board stays on the end face in the same orientation as the curl recordings, the cable is tucked under the strap, and every set is filmed and named by the D-022 rule. All of it is tuning data.
- **Why:** the raise and press have no data at all, so counter work can't start without it; it also rehearses the full test process (video, naming, three-tap sync, test log) at home.
- **Alternatives:** build R7 first and record everything untethered (delays counter work for no gain).
- **Affects:** counter development, `Data/README.md`.

### D-025 · v1 scope stays as is; growth science deferred (2026-10-21)
- **Decision:** v1 keeps its current scope. Spot reports what happened (reps, partials, rep duration, rest), not whether it is good or bad for muscle growth. Research on lengthened partials, momentum and rep speed is recorded in `Training_Science_Notes.md` for later versions. One addition: N7, an effort estimate (reps in reserve) from rep slow-down across a set, added as a nice-to-have.
- **Why:** growth-related guidance needs a working counter first. Rep slow-down is the reason rep duration is measured at all, so it is recorded now even though it is built later.
- **Affects:** R6a design note, N7.

---

## Scope clarifications (v1.2)

### D-026 · Partial reps are not counted (2026-10-21) — replaces the partial-rep rule in D-019
- **Decision:** a partial rep (at least 30° but short of the full-rep threshold; press: a quarter to half way) is not counted as a rep. Spot logs and flags it as a partial. The video-reviewed count is full reps only.
- **Why:** this was the intended meaning all along; a rep that stops short is not a rep to a lifter.
- **Consequence:** every movement near the full-rep threshold now decides the count, so test partials stop clearly short (about half range). The chest press must be told full from partial by estimating distance from the accelerometer, which is now the highest-risk part of v1.
- **Affects:** Definitions, R1, R6b, test log.

### D-027 · Mixed sets replace partial-only sets (2026-10-21) — updates D-010
- **Decision:** the R1 form "partial" becomes "mixed": planned full reps followed by 2–4 partials. R1 forms are now clean, momentum and mixed.
- **Why:** a set of only partials has a correct count of 0, which tests little. Mixed sets match how partials are really done (after failure) and test that Spot counts the full reps and ignores the partials.
- **Affects:** R1, R6b, Test Procedure R1, file naming.

### D-028 · Momentum flag is a must-have (R6c) (2026-10-21) — replaces N6 in D-018
- **Decision:** momentum reps are counted and flagged in the data. Curl and raise: flag at least 80% of momentum reps and at most 10% of clean reps. Chest press: the same targets for reps that rebound off the chest. Hips or back lifting off the bench is out of scope.
- **Why:** 80% because detection is unproven (one momentum recording); revisit before the freeze. Hip lift happens in the body, not the dumbbell.
- **Affects:** R6c, Definitions, Out of scope.

### D-029 · Set timeout stays at 15 s; partials keep a set going (2026-10-21) — updates D-012
- **Decision:** a set ends when no rep or partial starts within 15 s. Partials keep a set going. Reported rest is back-dated to the end of the last rep or partial. A pause of 15 s or less mid-set does not split the set.
- **Why:** 15 s is generous to the prototype. Back-dating keeps the reported rest accurate despite the wait.
- **Alternatives:** 10 s (rejected for v1; splits sets with short mid-set pauses).
- **Affects:** Definitions, R3.

### D-030 · No required pause between reps (2026-10-21)
- **Decision:** users are not required to pause between reps. Pauses may be used in the first tuning session to make early data easier; held-out tests use normal, continuous reps.
- **Why:** real lifters don't pause, the Garmin doesn't need it, and rep boundaries can be found where the gyro reading reverses at the bottom of each rep.
- **Affects:** Test Procedure R1, counter design.

### D-031 · v1 scope limits (2026-10-21)
- **Decision:**
  - Alternating curls are out of scope; v1 keeps to three basic exercises that train different muscles and underlie many upper-body movements.
  - Spot must work on a dumbbell in either hand; held-out sets are split between hands.
  - The curl uses a supinated grip (palm forward, no wrist twist).
  - v1 is tested at home with the developer's own dumbbells, by the developer only, but must operate as if at a gym (no cable, laptop or wall power during sets). A gym-ready mount is the main goal of v2 (N6).
  - Choosing the right exercise mode is the user's responsibility; a wrong-mode warning is a nice-to-have (N2).
  - Camera views: curl and press from the side, lateral raise from the front; the pod is mounted on the end facing the camera so the LED is visible.
  - A failed final rep that stalls below the full-rep threshold is a partial.
- **Affects:** R1, Section 3, Constraints, Out of scope, N2, N6, Test Procedure R1.

### D-032 · Gaps closed in review (2026-10-21) — updates D-019, D-026, D-028
- **Decision:**
  - Chest press full rep: elbows within about 15° of straight. Partial: at least a quarter of the way up but short of that threshold (previously "a quarter to a half", which left 50–90% of the way undefined).
  - A swung movement that falls short of the full-rep threshold is a partial: partial takes precedence over momentum, so it is neither counted nor flagged as momentum.
  - On the raise and press, where both arms move, the video count is the reps of the arm holding the pod.
  - Rotating the wrists while holding the dumbbell is noise (R2).
  - "Tempo" is replaced by "rep duration" in the problem statement and R6a; four-phase tempo is a later feature.
- **Why:** each was an unwritten assumption or an undefined case that would have caused a scoring argument or an interview question without a clear answer.
- **Affects:** Definitions, R1c, R2, R6a, R6c, Test Procedure R1, problem statement.
