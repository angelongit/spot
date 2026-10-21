**Spot — Requirements**

Version 1.3 · October 21, 2026

*Defines what “done” means for Spot v1. Every must-have needs a number and a way to fail it.*

# 1. Problem statement

General gym-goers have a hard time keeping track of details of their sets when working out: general form, rep amount, and rep speed. Inconsistent form and miscounted reps lead to inefficient results and make progress hard to measure. Spot aims to fix these problems by doing the analysis for the user: counting reps, timing rest, measuring how long each rep takes, and flagging partial and momentum reps.

Spot is a small motion-sensing pod that attaches to the end of a dumbbell. It measures how the dumbbell moves during each set and turns that motion into a rep count, rest times and form feedback.

# 2. Definitions

*Sections 2.1 and 2.2 are for readers new to the gym or to the hardware. Sections 2.3 and 2.4 are the exact rules the tests use.*

## 2.1 Gym terms

| **TERM**                 | **MEANING**                                                                                                                                                                                                                    |
|--------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **Rep (repetition)**     | One complete movement of an exercise: the weight moves away from the starting position and back.                                                                                                                               |
| **Dumbbell**             | A short handheld weight, held in one hand.                                                                                                                                                                                     |
| **Hex dumbbell**         | A dumbbell whose two ends are six-sided (hexagonal) so it does not roll. The flat outer face of each end is the end face, where Spot mounts. The test dumbbells are CAP 10 lb rubber-coated hex dumbbells.                     |
| **Dumbbell curl**        | Standing with the arm hanging down and the palm facing forward, the user bends the elbow to lift the dumbbell toward the shoulder, then lowers it. Works the biceps.                                                           |
| **Dumbbell chest press** | Lying on the back on a flat bench, the user pushes the dumbbells from the chest straight up until the arms are nearly straight, then lowers them. Works the chest.                                                             |
| **Lateral raise**        | Standing with the arms hanging down, the user lifts the dumbbells out to the sides until the arms are about level with the shoulders, then lowers them. Works the shoulders.                                                   |
| **Supinated grip**       | Palm facing forward (and up at the top of a curl), held that way for the whole rep with no wrist twist. v1’s curl uses this grip.                                                                                              |
| **Form**                 | How correctly an exercise is done: moving through the full range, under control, without swinging.                                                                                                                             |
| **Tempo**                | In lifting, the time spent in each phase of a rep: lowering, pause at the bottom, lifting, pause at the top (for example 3-1-2-0). Spot v1 measures only the total duration of each rep (R6a); phase tempo is a later feature. |
| **Range of motion**      | How far the weight travels during a rep.                                                                                                                                                                                       |
| **Rack**                 | The stand where dumbbells are stored at the gym.                                                                                                                                                                               |

## 2.2 Technical terms

| **TERM**           | **MEANING**                                                                                                                                                                               |
|--------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **IMU**            | Inertial measurement unit: the motion sensor on Spot’s board. It combines an accelerometer (measures acceleration, including gravity) and a gyroscope (measures how fast it is rotating). |
| **100 Hz**         | 100 readings per second.                                                                                                                                                                  |
| **BLE**            | Bluetooth Low Energy, the wireless link a phone app would use.                                                                                                                            |
| **LED**            | The small colored light on Spot.                                                                                                                                                          |
| **Git tag**        | A named snapshot of the code in version control. Once tagged, that exact version can always be recovered.                                                                                 |
| **VHB tape**       | 3M “Very High Bond” double-sided foam tape, used to bond the steel plate to the dumbbell.                                                                                                 |
| **Sample counter** | A number Spot stores with every reading, counting up by one. A skipped number shows that data was lost.                                                                                   |

## 2.3 Counting and testing terms

| **TERM**                 | **DEFINITION**                                                                                                                                                                                                                                                                                                                                                                                                        |
|--------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **Rep start and end**    | A rep starts at the first movement away from the starting position and ends when the dumbbell is back at the starting position, both judged on video.                                                                                                                                                                                                                                                                 |
| **Full rep**             | A rep that reaches the exercise’s full-rep threshold (see 2.4) and returns to the starting position.                                                                                                                                                                                                                                                                                                                  |
| **Clean rep**            | A full rep with no momentum.                                                                                                                                                                                                                                                                                                                                                                                          |
| **Partial rep**          | A movement begun at the starting position that sweeps at least 30 degrees (press: a quarter of the way up) but does not reach the full-rep threshold, then returns. A partial rep is NOT counted as a rep; Spot logs it and flags it as a partial.                                                                                                                                                                    |
| **Momentum rep**         | A full rep in which the weight is moved by swinging or bouncing it with the body, instead of by the target muscle alone. A momentum rep IS counted as a rep, and Spot flags it as momentum. If a swung rep does not reach the full-rep threshold, it is a partial: partial takes precedence, so it is not counted and not flagged as momentum.                                                                        |
| **Mixed set**            | A set of full reps followed by partial reps, for example partials done after the user can no longer complete a full rep.                                                                                                                                                                                                                                                                                              |
| **Set**                  | Consecutive reps and partials with gaps of 15 s or less. Partials keep a set going. A set ends when no rep or partial starts within 15 s (the timeout), so a pause of 15 s or less in the middle of a set does not split it.                                                                                                                                                                                          |
| **Rest**                 | From the end of the last rep or partial of one set (back at the starting position) to the start of the first rep or partial of the next. Spot only knows a set has ended after the 15 s timeout, so it back-dates the rest start.                                                                                                                                                                                     |
| **Noise set**            | A recording in which no rep is performed, confirmed by video.                                                                                                                                                                                                                                                                                                                                                         |
| **Video-reviewed count** | The number of full reps (including momentum reps) of the arm holding the pod, as a reviewer counts them by watching the video of the set, before looking at Spot’s count. Partials are counted separately, as the video partial count. Movements below the 30° floor (press: below a quarter of the way up) are neither. Any set where Spot differs from the video by 2 or more reps gets a second look at the video. |
| **Frozen counter**       | The counter code and all its settings (thresholds, stillness timeout) tagged in Git, for example counter-v1-frozen.                                                                                                                                                                                                                                                                                                   |
| **Held-out set**         | A set recorded after the counter is frozen and used only for scoring, never for tuning or debugging.                                                                                                                                                                                                                                                                                                                  |
| **Tuning set**           | Any other recorded set, including every recording made before the counter is frozen.                                                                                                                                                                                                                                                                                                                                  |
| **Still / resting**      | Motion below a threshold for longer than the timeout. The threshold is a design parameter, set from tuning data and frozen with the counter. It is not a requirement.                                                                                                                                                                                                                                                 |

## 2.4 Exercise-specific terms

| **TERM**                          | **CURL**                                                                                                                                                             | **CHEST PRESS**                                                                                                                                                                                                                          | **LATERAL RAISE**                                                                                                                                                                                                       |
|-----------------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **Starting position**             | The position where the hand holding the dumbbell is at the user's side, palm facing forward (supinated grip)                                                         | The position where the dumbbell is in line with the user's chest                                                                                                                                                                         | The position where the hand holding the dumbbell is at the user's side                                                                                                                                                  |
| **Full rep**                      | The user begins the rep with arms straight to their side, bends the elbow to at least 70 degrees of rotation, then returns to the initial position as seen on video. | The user begins the rep, dumbbells held at chest level, handles running side to side across the chest. The user presses upward until the elbows are within about 15° of straight, then returns to the initial position as seen on video. | The user begins the rep with the arms straight to their side. The user raises their arms to the side, and sweeps at least 70 degrees out from starting position, then returns to the initial position as seen on video. |
| **Partial rep**                   | 30° to 70°                                                                                                                                                           | Pressed at least a quarter of the way from the chest but short of the full-rep threshold (elbows within about 15° of straight). Less than a quarter is not a rep.                                                                        | 30° to 70°                                                                                                                                                                                                              |
| **Returned to starting position** | Within about 10° of the starting angle.                                                                                                                              | The dumbbells are back at chest level.                                                                                                                                                                                                   | Within about 10° of the starting angle.                                                                                                                                                                                 |
| **Momentum rep**                  | The weight is swung up using the hips, knees or torso instead of the biceps, producing a visible swing.                                                              | A rep where the weights rebound off the chest without a pause, or the hips or back visibly lift off the bench. Spot only detects the rebound (R6c).                                                                                      | The weight is swung up using the hips, knees or torso instead of the shoulders, producing a visible swing.                                                                                                              |

# 3. Users and use cases

- **User:** Gym-goers who want to track their progress, from beginner to experienced lifters. Spot provides information that is useful for those who simply want to count their reps, and those who care about metrics such as lifting speed, and uniformity.

- **Exercises:** Dumbbell curl, dumbbell chest press and dumbbell lateral raise (see 2.1).

- **Equipment and mount:** Spot attaches to hex dumbbells for the prototype. A steel plate (or fender washer) is bonded to the end face of the dumbbell with 3M VHB tape, and the pod’s magnets grip the plate. The pod sits on the end face so it never covers the handle. It must work on a dumbbell in either hand.

- **Testing:** v1 is tested at home with the developer’s own CAP dumbbells, by the developer as the only lifter, but it must operate as if it were at a gym: no cable, laptop or wall power during sets. Making Spot fully gym-ready is the main goal of v2.

- **Exercise selection:** The user presses a center button that cycles through the three planned exercises, with an LED changing color based on the selection.

# 4. Must-have requirements

*Each requirement states the exercise and mount, the allowed error, how often it must be met (pass rate), how many sets are tested, and what it is compared against (ground truth, normally the video). “How I’ll test it” gives the procedure. A requirement is met only if its test passes.*

<table>
<colgroup>
<col style="width: 6%" />
<col style="width: 30%" />
<col style="width: 50%" />
<col style="width: 13%" />
</colgroup>
<thead>
<tr class="header">
<th><strong>ID</strong></th>
<th><strong>REQUIREMENT</strong></th>
<th><strong>HOW I'LL TEST IT</strong></th>
<th><strong>STATUS</strong></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td><strong>R1a</strong></td>
<td>Dumbbell curl (supinated grip). Pod on the end face of the hex dumbbell, either hand. Spot’s rep count (full reps only; partial reps are not counted) is within ±1 rep of the video-reviewed count on at least 90% of held-out sets, and within ±2 reps on every held-out set.</td>
<td><p>See Test Procedure R1.</p>
<p><strong>Exercise-specific:</strong> 3 speeds (slow, normal, fast) × 3 forms (clean, momentum, mixed), at least 3 sets per combination, so at least 27 sets, split between the left and right hand. Partials in mixed sets stop at about half range, clearly between the 30° floor and the 70° full-rep threshold (see Definitions).</p></td>
<td><strong>Not started</strong></td>
</tr>
<tr class="even">
<td><strong>R1b</strong></td>
<td>Dumbbell lateral raise. Pod on the end face of the hex dumbbell, either hand. Spot’s rep count (full reps only; partial reps are not counted) is within ±1 rep of the video-reviewed count on at least 90% of held-out sets, and within ±2 reps on every held-out set.</td>
<td><p>See Test Procedure R1.</p>
<p><strong>Exercise-specific:</strong> 3 speeds (slow, normal, fast) × 3 forms (clean, momentum, mixed), at least 3 sets per combination, so at least 27 sets, split between the left and right hand. Partials in mixed sets stop at about half range, clearly between the 30° floor and the 70° full-rep threshold (see Definitions).</p></td>
<td><strong>Not started</strong></td>
</tr>
<tr class="odd">
<td><strong>R1c</strong></td>
<td>Dumbbell chest press. Pod on the end face of the hex dumbbell, either hand. Spot’s rep count (full reps only; partial reps are not counted) is within ±1 rep of the video-reviewed count on at least 90% of held-out sets, and within ±2 reps on every held-out set.</td>
<td><p>See Test Procedure R1.</p>
<p><strong>Exercise-specific:</strong> 3 speeds (slow, normal, fast) × 3 forms (clean, momentum, mixed), at least 3 sets per combination, so at least 27 sets, split between the left and right hand. Partials in mixed sets stop at about half way, clearly between a quarter of the way up and the full-rep threshold (see Definitions).</p></td>
<td><strong>Not started</strong></td>
</tr>
<tr class="even">
<td><strong>R2</strong></td>
<td>Spot counts 0 reps on every one of at least 20 held-out noise sets per exercise mode (see Definitions), and no noise set starts a new set.</td>
<td><ul>
<li><p>Sets: record at least 20 noise sets for each exercise mode (curl, press, lateral raise), each with that mode selected, each 30 to 60 seconds long, with the mode and noise type in the file name.</p></li>
<li><p>Noise types: handling the dumbbell, rotating the wrists while holding it, walking as one would in the gym, picking it up from the rack or floor, carrying it between stations, setting it down for 2 to 10 seconds, small movements below the 30° partial floor, and adjusting grip or posture. Press only: bringing the dumbbells from the thighs up to the chest to get into position on the bench, and setting them down afterwards. Each type appears in at least 2 recordings per mode.</p></li>
<li><p>Between sets: at least 5 of the 20 recordings per mode are made between two real sets of that exercise, so noise during rest is tested.</p></li>
<li><p>Ground truth: video confirms that no rep was performed in each recording.</p></li>
<li><p>Pass rule: Spot reports 0 reps on all 20 noise sets for the mode. Any counted rep, or any noise that starts a new set, is a fail.</p></li>
<li><p>Frozen counter: same rule as Test Procedure R1. Record the noise sets after the tag; earlier noise recordings are tuning data.</p></li>
</ul></td>
<td><strong>Not started</strong></td>
</tr>
<tr class="odd">
<td><strong>R3</strong></td>
<td>Spot’s measured rest time is within ±5 seconds of video-reviewed rest, on at least 90% of at least 20 held-out rest periods per exercise, for rests from 30 s to 5 minutes.</td>
<td><ul>
<li><p>Sets: record the R1 held-out sets plus extra held-out sets, so each exercise has at least 21 consecutive sets (at least 20 rest periods), in blocks of several consecutive sets, with rests varied across the range (about 30 s up to 5 minutes).</p></li>
<li><p>Ground truth: from video, the time from the end of the last rep of one set (back at the starting position) to the start of the first rep of the next. Not a hand timer.</p></li>
<li><p>Comparison: Spot’s reported rest against the video rest, per rest period, with rest boundaries taken from the video’s reps and partials, not Spot’s.</p></li>
<li><p>Pass rule: at least 90% of rest periods within ±5 s.</p></li>
<li><p>Exclusions: rests over 5 minutes aren’t performed. If one happens by accident, log it and exclude it in writing before you score anything.</p></li>
<li><p>Frozen counter and timeout: same rule as Test Procedure R1.</p></li>
</ul>
<p><strong>Design note:</strong> Spot back-dates both ends of a rest: the start to the end of the last rep, and the end to the start of the first rep of the next set (not the moment the rep is detected).</p></td>
<td><strong>Not started</strong></td>
</tr>
<tr class="even">
<td><strong>R4</strong></td>
<td>On the same held-out sets as R1, Spot’s mean absolute rep-count error against the video count is lower than that of a Garmin Forerunner 165 smartwatch, for each exercise.</td>
<td><ul>
<li><p>Wear the watch on the wrist of the arm holding the dumbbell, every time. Start a strength workout on the watch (automatic set detection off) and select the exercise on Spot, then perform each exercise as described in R1.</p></li>
<li><p>End each set by pressing the watch’s BACK button. Record the count the watch shows when its rest timer appears, and never edit it. Film the watch screen so the count is on video.</p></li>
<li><p>If the watch shows no count for a set, record it as 0 reps.</p></li>
<li><p>Both devices are scored against the video count of full reps. For each device, calculate the mean absolute error: the average, over all sets, of the difference between the device’s count and the video count, ignoring the sign.</p></li>
<li><p>Pass if Spot's mean error is lower than the watch's for each exercise.</p></li>
</ul></td>
<td><strong>Not started</strong></td>
</tr>
<tr class="odd">
<td><strong>R5</strong></td>
<td>Pressing the center button cycles the exercise mode curl → press → lateral raise → curl. The LED shows the current mode by color and blink count (curl = blue, 1 blink; press = red, 2 blinks; lateral raise = green, 3 blinks), readable from 1 m in normal room lighting. Spot starts in curl mode every time it is powered on.</td>
<td><ul>
<li><p>Cycling: starting in curl, press the button 30 consecutive times (10 full cycles). Each press must move to the correct next mode, with the correct LED color and blink count, checked on video.</p></li>
<li><p>Power cycle: leave Spot in press mode, then in lateral raise mode, then in press mode again, switching it off and on each time. It must start in curl every time.</p></li>
<li><p>Visibility: check the LED color and blink count from 1 m in normal room lighting.</p></li>
<li><p>Lockout: during a set, press the button 5 times. The mode must not change.</p></li>
<li><p>Pass rule: all 30 presses, all 3 power cycles, the visibility check and the lockout check are correct.</p></li>
</ul>
<p><strong>Design note:</strong> The mode is locked while a set is in progress, from the first rep until the set ends (see Definitions), so a bump during a set cannot change the exercise mid-set. The default is curl, not the last mode used, because users will not always remember the previous mode.</p></td>
<td><strong>Not started</strong></td>
</tr>
<tr class="even">
<td><strong>R6a</strong></td>
<td>Rep duration. Spot’s reported rep duration (first movement away from the starting position to the return to it) is within ±0.5 s of the video-reviewed duration on at least 90% of reps in the R1 held-out sets, for each exercise.</td>
<td><ul>
<li><p>Sets: use the R1 held-out sets. No new recordings.</p></li>
<li><p>Ground truth: the duration of each rep from the video, with rep start and end as defined in Definitions, timed frame by frame.</p></li>
<li><p>Logging: Spot logs the duration of every counted rep to the set’s data file.</p></li>
<li><p>Comparison: pair each video rep with the Spot rep that overlaps it in time. A video rep with no Spot rep counts as a miss.</p></li>
<li><p>Pass rule: at least 90% of video reps are paired and within ±0.5 s, per exercise.</p></li>
<li><p>Frozen counter: same rule as Test Procedure R1.</p></li>
</ul>
<p><strong>Design note:</strong> Rep-to-rep consistency (the spread of rep durations in a set) is calculated from these durations and is not tested separately. Revisit it when form check is implemented. Per-rep durations are also the input for the effort estimate (N7), which is why R6a is scored per rep, not as a set average.</p></td>
<td><strong>Not started</strong></td>
</tr>
<tr class="odd">
<td><strong>R6b</strong></td>
<td>Partial-rep detection. For each exercise, Spot logs at least 90% of the video’s partial reps as partials and logs at most 10% of full reps as partials, and shows each partial with an LED cue within 1 s of the end of the movement.</td>
<td><ul>
<li><p>Sets: use the R1 held-out mixed sets and clean sets for each exercise.</p></li>
<li><p>Ground truth: on video, label every movement as a full rep or a partial before looking at Spot’s data.</p></li>
<li><p>Logging: Spot logs every partial with its time.</p></li>
<li><p>Pass rule, per exercise: at least 90% of video partials are logged as partials, and at most 10% of full reps are logged as partials.</p></li>
<li><p>LED cue: on video, in at least 3 mixed sets and 3 clean sets per exercise, the LED cue appears within 1 s of the end of each logged partial and at no other time.</p></li>
<li><p>Frozen counter: same rule as Test Procedure R1.</p></li>
</ul>
<p><strong>Design note:</strong> The cue is a single 0.5 s white flash, a color not used by the mode LEDs in R5. Because partials are not counted, every movement near the full-rep threshold decides the count; test partials stop clearly short (about half range) so that the test is not decided by borderline reps. The press has no rotation to measure, so Spot must estimate how far the dumbbell travelled from the accelerometer; this is the highest-risk part of v1 and is checked first in the press tuning data.</p></td>
<td><strong>Not started</strong></td>
</tr>
<tr class="even">
<td><strong>R6c</strong></td>
<td>Momentum flag. For curl and lateral raise, Spot flags at least 80% of momentum reps and at most 10% of clean reps as momentum. For the chest press, the same targets apply to reps that rebound off the chest. Momentum reps are still counted (R1); the flag is logged in the data. The flag applies only to full reps: a swung movement that falls short of the full-rep threshold is a partial.</td>
<td><ul>
<li><p>Sets: use the R1 held-out momentum and clean sets for each exercise. Chest press momentum sets use the rebound only.</p></li>
<li><p>Ground truth: each rep is labelled by its set type and checked on video. Exclude any rep the video shows did not follow its set type, and log the exclusions in writing before scoring.</p></li>
<li><p>Logging: Spot logs a momentum flag (yes/no) for every counted rep.</p></li>
<li><p>Pass rule, per exercise: at least 80% of momentum reps are flagged, and at most 10% of clean reps are flagged.</p></li>
<li><p>Frozen counter: same rule as Test Procedure R1.</p></li>
</ul>
<p><strong>Design note:</strong> 80% is lower than the other targets because momentum detection is unproven: only one momentum recording exists. Revisit the target once tuning data shows what is realistic, before the counter is frozen. Hips or back lifting off the bench during the press happens in the body, not the dumbbell, so it is out of scope.</p></td>
<td><strong>Not started</strong></td>
</tr>
<tr class="odd">
<td><strong>R7</strong></td>
<td>Untethered logging. Spot records a full test session on battery with no cable attached: at least 30 sets of up to 60 s each, logging raw motion data at 100 Hz during each set (plus about 2 s before and after) and its results (count, rep durations, partial flags, rest times). After the session, all of it downloads over USB with no lost data, and it lines up with the video to within 0.1 s.</td>
<td><ul>
<li><p>Session: charge Spot fully, disconnect the cable, and record a filmed session of at least 30 sets of up to 60 s each.</p></li>
<li><p>Sync: at the start of the session, tap the pod three times on camera.</p></li>
<li><p>Download: after the session, connect USB and download all data.</p></li>
<li><p>Checks: every set on the video is present in the data; the sample counter has no gaps within any set; results are present for every set; the three tap spikes line up with the taps on video to within 0.1 s.</p></li>
<li><p>Pass rule: all checks pass.</p></li>
</ul>
<p><strong>Design note:</strong> Data is stored in the board’s 2 MB on-board flash, recording only during sets. At 100 Hz this holds roughly 22 to 29 minutes of raw data, so a 30-set session may not fit; if it does not, add a microSD card module. The SD card is skipped for initial testing. Raw data is logged, not results only, so failed sets can be debugged.</p></td>
<td><strong>Not started</strong></td>
</tr>
</tbody>
</table>

## Test Procedure R1

Shared by R1a, R1b and R1c. Each exercise is scored on its own.

- Mount Spot on the end face of the hex dumbbell that faces the camera (the same dumbbells for every set) and record each set as a separate file, with exercise, hand, speed, form and planned rep count in the file name.

- Per exercise, perform at least 3 sets for each combination of speed (slow, normal, fast) and form (clean = full reps with no momentum; momentum = full reps with momentum; mixed = full reps followed by 2 to 4 partials), at least 27 sets. In each combination, perform one set each of 6, 8 and 12 planned full reps, and use each hand in every combination. The planned count is a target only; the video count is ground truth.

- Film every set so every rep is visible: curl and chest press from the side with the whole arm in view; lateral raise from the front. Count the full reps and partials of the arm holding the pod on the video before looking at Spot’s data.

- Log each set in the test log: Spot count, video count (full reps), difference, within ±1 (yes/no), within ±2 (yes/no), plus video and Spot partial counts.

- Pass if, for the exercise, the count is within ±1 rep of the video count on at least 90% of sets (at least 25 of 27) and within ±2 reps on every set.

- Frozen counter: tag the counter code and its settings (including the stillness timeout) in Git before recording, and use only sets recorded after the tag. If the counter is changed after testing, the sets used become tuning sets and new held-out sets must be recorded.

# 5. Nice-to-have requirements

Features that must not block the must-haves.

| **ID** | **REQUIREMENT**                                                                                                                                                                      | **WHY IT'S NOT A MUST-HAVE**                                                                                                                                                                               |
|--------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **N1** | Phone app and BLE.                                                                                                                                                                   | There is no app until winter break. v1 is judged on counting, rest and the device’s own cues, with data logged to file.                                                                                    |
| **N2** | Wrong-mode warning: flash the LED when the movement does not match the selected exercise.                                                                                            | Telling the press from the curl or raise is likely easy (a push versus a rotation), but the curl and raise look almost the same to the sensor. Choosing the right mode is the user’s responsibility in v1. |
| **N3** | Range-of-motion feedback for the chest press (how far each press travelled).                                                                                                         | R6b only needs to tell a full press from a partial; reporting the distance is extra. Defer until the press counter works.                                                                                  |
| **N4** | Absolute-degree range of motion for curl and lateral raise.                                                                                                                          | The gyroscope’s readings slowly drift, so absolute angles need correction. The relative partial flag (R6b) is enough for v1.                                                                               |
| **N5** | Sound cue (buzzer) for partial reps.                                                                                                                                                 | The board has no speaker. It needs a piezo buzzer on a spare pin, plus pod space, and gym noise may mask it. The LED cue covers v1.                                                                        |
| **N6** | Mount that attaches to gym-owned dumbbells, so the pod can move between weights.                                                                                                     | The steel-plate mount only works on the developer’s own dumbbells. A gym-ready mount is the main goal of v2.                                                                                               |
| **N7** | Effort estimate from rep slow-down: as a set nears failure, reps get slower, so the increase in rep duration (velocity loss) across a set estimates how many reps the user had left. | Builds on accurate per-rep durations (R6a), which must work first. Needs its own validation against sets taken to failure.                                                                                 |

# 6. Constraints

- **Deadline:** A working prototype by the end of the Fall 2026 semester is preferred, but not a hard deadline. The phone app is planned for winter break.

- **Hardware:** Seeed XIAO nRF52840 Sense. Its IMU is motion-only (no magnetometer), so the magnets in the mount do not affect the motion data.

- **Size and grip:** The pod must fit within the end face of the hex dumbbell and must not reach the handle or block the grip.

- **Mount:** The pod must not shift relative to the dumbbell during a set, since any slip shows up as motion.

- **Data logging:** Spot must record sets without a USB cable attached, so it can be tested at the gym (see R7).

- **Battery life:** At least one full test session per charge (about 90 minutes, see R7).

- **Budget:** Open, ideally under \$50 in parts.

# 7. Out of scope

- Equipment other than hex dumbbells (machines, barbells, cables). v1 proves the method on one kind of equipment first.

- Exercises other than curl (supinated grip), chest press and lateral raise, including alternating curls. v1 keeps to three basic exercises that train different muscles and underlie many upper-body movements.

- Detecting hips or back lifting off the bench during the press: it happens in the body, not the dumbbell.

- Shortened partials (top-half reps that never return to the starting position): neither counted nor flagged in v1.

- Lifters other than the developer, and gym-owned dumbbells (v2).

- Automatic exercise detection. The user selects the exercise with the button (R5).

- Phone app and BLE (N1), planned for winter break.

- Muscle-activation sensing (EMG) and barbell tilt or balance measurement.

# 8. Open questions

- Does VHB tape hold a steel plate on the rubber-coated end face of the CAP dumbbells through a full workout? (Untested.)

- Does a 30-set session fit in the 2 MB on-board flash? The R7 test answers this; if not, add a microSD card.

- Can Spot tell a full chest press from a partial by estimating distance from the accelerometer? Highest-risk item; check it first in the press tuning data.

- Does a recognisable momentum pattern exist in the curl and raise data? Only one momentum recording so far.

- What rejection rule, beyond the 30° floor, keeps noise from counting (R2)? High off-axis motion is one idea, untested.

- Is the 15 s set timeout right? Kept generous for the prototype.

- Which gyro axis dominates the lateral raise on the end-face mount? Needs lateral-raise recordings.

- Momentum sets for all three exercises still need to be recorded.

# Revision history

| **DATE**   | **CHANGE**                                                                                                                                                                                                                 | **REASON**                                |
|------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-------------------------------------------|
| 2026-10-20 | Created document                                                                                                                                                                                                           |                                           |
| 2026-10-21 | Rewrote R1a–R1c with tiered tolerance, added shared Test Procedure R1, rewrote R2, R3 and R5, added R6a and R6b, filled nice-to-haves, completed Definitions, drafted sections 3 and 6 to 8, added R7 (untethered logging) | Working session decisions                 |
| 2026-10-21 | Version 1.0: consistency review, added gym and technical glossaries, clarified R4                                                                                                                                          | Readable for readers new to the gym       |
| 2026-10-21 | Version 1.1: added N7, effort estimate from rep slow-down                                                                                                                                                                  | The purpose behind measuring rep duration |
| 2026-10-21 | Version 1.2: partial reps no longer counted, mixed sets replace partial sets, added R6c momentum flag, either hand, supinated curl, home testing, scope limits                                                             | Unwritten assumptions made explicit       |
| 2026-10-21 | Version 1.3: press full-rep threshold and partial range, partial takes precedence over momentum, video counts the pod arm, wrist rotation added as noise, tempo wording replaced by rep duration                           | Closing gaps found in review              |
