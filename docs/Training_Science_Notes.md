# Training Science Notes for Spot

Reference for the lifting terms used in Spot's documents, and what the current research says where it affects Spot's design. Compiled 2026-10-21. Research summaries are as reported by the sources listed at the end; several key studies are preprints or used untrained participants, noted where relevant.

## Glossary

### Basics
| Term | Meaning |
|---|---|
| **Hypertrophy** | Muscle growth: an increase in muscle size (measured in studies as cross-sectional area or muscle thickness). |
| **Rep (repetition)** | One complete movement of an exercise. |
| **Set** | A group of reps done back to back, followed by rest. |
| **1RM (one-rep max)** | The heaviest load a person can lift for one rep. Loads are often written as a percentage of 1RM. |
| **Load** | The weight lifted. |
| **Intensity** | Ambiguous in gym talk: either load as %1RM, or effort (how close to failure). Say which. |
| **Progressive overload** | Doing more over time (more load, reps or sets) so the muscle keeps adapting. Needs accurate logs, which is part of Spot's purpose. |
| **Mechanical tension** | The force a muscle produces against resistance; considered the main driver of hypertrophy. |

### Volume
| Term | Meaning |
|---|---|
| **Volume (sets)** | Number of hard sets per muscle per week. The most common way to measure training dose for hypertrophy. |
| **Hard set** | A set taken reasonably close to failure (roughly 0–4 reps in reserve). |
| **Volume load** | Sets × reps × load. Useful, but it rewards light weights for many reps. |
| **Fractional sets** | Counting a set as 1 for the muscle that is the main mover and ½ for a muscle that only assists (for example, a row counts as ½ a biceps set). |

### Effort and failure
| Term | Meaning |
|---|---|
| **Failure (momentary muscular failure)** | The point where you can't complete another concentric (lifting) rep with good form despite full effort. |
| **RIR (reps in reserve)** | How many more reps you could have done before failure. 0 RIR = failure. |
| **RPE (rate of perceived exertion)** | A 1–10 effort score; in lifting, RPE 10 ≈ 0 RIR, RPE 8 ≈ 2 RIR. |
| **Proximity to failure** | How close to failure a set ends, usually given in RIR. |
| **Effective reps** | The idea that the last few reps before failure drive most of the growth. A popular model, not settled science. |

### Rep anatomy and tempo
| Term | Meaning |
|---|---|
| **Concentric** | The lifting phase: the muscle shortens (curling the dumbbell up, pressing it away from the chest). |
| **Eccentric** | The lowering phase: the muscle lengthens under control. |
| **Isometric** | A hold: the muscle works but doesn't change length (a pause at the top or bottom). |
| **Tempo** | The duration of each phase of a rep, written as four digits: eccentric – bottom pause – concentric – top pause. **3-1-2-0** means 3 s lowering, 1 s pause at the bottom, 2 s lifting, no pause at the top. **X** means "as fast as possible". The order starts with the eccentric because squats and barbell bench presses start at the top; for curls, raises and Spot's chest press, each rep starts with the concentric. |
| **Rep duration** | Total time for one rep. Spot v1 (R6a) measures this, not the four-phase tempo. |
| **Time under tension (TUT)** | Total time a muscle is working during a set (roughly the sum of rep durations). |

### Range of motion
| Term | Meaning |
|---|---|
| **Range of motion (ROM)** | How far the joint moves during a rep. |
| **Full ROM** | The whole movement the exercise allows. |
| **Partial rep** | A rep that covers only part of the range. |
| **Lengthened partial** | A partial in the stretched part of the range: the bottom of a curl (arm nearly straight), the bottom of a lateral raise (arms at the sides), the bottom of a press (dumbbells at the chest). **Every partial Spot defines (30°–70° for curl and raise, a quarter to half way for press) is a lengthened partial.** |
| **Shortened partial** | A partial in the contracted part of the range: the top half of a curl. Spot's current definitions can't count these, because the rep never returns to the starting position. |
| **Lengthened superset** | Continuing a set with lengthened partials after full reps reach failure. |

### Form
| Term | Meaning |
|---|---|
| **Form / technique** | How an exercise is performed: path, range, control, body position. |
| **Cheat rep (momentum rep)** | A rep helped by swinging the body or bouncing the weight. Spot calls this a momentum rep. |
| **Strict** | No momentum; only the target muscle moves the weight. Spot calls this a clean rep. |

### Measurement
| Term | Meaning |
|---|---|
| **VBT (velocity-based training)** | Using the speed of the bar or dumbbell to guide training. |
| **Mean concentric velocity (MCV)** | Average speed of the lifting phase, in m/s. The standard VBT measure. |
| **Velocity loss** | How much slower the reps get within a set, as a percentage of the fastest rep. Rises predictably as a set approaches failure. |

## What the research says, and what it means for Spot

**1. Rep speed barely matters for growth.** Schoenfeld et al. (2015) found similar hypertrophy across rep durations of 0.5–8 s. A 2025 meta-analysis (Enes et al., 14 trials, phases of 0.25–4.5 s each) found no clear advantage for fast or slow. A 2024 review recommends 2–8 s per rep with a controlled lowering.
*For Spot:* tempo feedback is valuable for **consistency and control** (doing the same rep every set, so progress is comparable), not for finding a "best" speed. Spot should not tell users a speed is wrong for growth.

**2. Partial reps in the stretched position are not bad form.** In a preacher-curl study (untrained women, 8 weeks), training only the initial range (0°–68°, arm nearly straight) produced more biceps growth at one site than training the final range (68°–135°). Other studies on lengthened partials (mostly calves and legs, some preprints) find them comparable to, or better than, full ROM.
*For Spot:* R6b's partial flag must be **information, not a warning**. A lifter may do lengthened partials on purpose, often after reaching failure. Spot should report "4 full reps, then 3 partials", not "bad form".

**3. Momentum reps may not hurt growth either.** A preprint (25 untrained people, 8 weeks, dumbbell curls and pushdowns) found similar arm growth with momentum and strict reps, and the momentum arm moved more total load.
*For Spot:* keep counting momentum reps (R1 already does); any future momentum flag (N6) should also be informational.

**4. Training closer to failure grows more muscle.** A 2024 meta-regression (preprint; Robinson et al.) found hypertrophy increases as sets end closer to failure, while strength gains were similar across a wide range of RIR.
*For Spot:* knowing how close to failure a set ended is one of the most useful things Spot could report.

**5. Velocity loss predicts reps in reserve.** In bench press and squat, velocity loss within a set tracked the share of possible reps completed very closely (R² = 0.97 bench press, 0.93 squat; Rodríguez-Rosell et al., 2020), though how many reps people can do varies widely between individuals.
*For Spot:* Spot already measures each rep's duration and gyro speed. **Rep slow-down across a set is a credible path to estimating effort (RIR)**, the feature point 4 says matters most. This is a strong candidate nice-to-have, more valuable than the four-phase tempo split.

**6. Weekly hard sets per muscle are the main dose measure.** A 2025 meta-regression (Pelland et al., 67 studies) found growth keeps rising with weekly sets, with diminishing returns per set past about 10 per week, counting indirect sets as ½.
*For Spot:* with exercise mode known (R5), Spot can count hard sets per muscle per week, a natural app feature.

## Sources
- Schoenfeld et al. 2015, *Sports Medicine*, repetition duration meta-analysis: https://pubmed.ncbi.nlm.nih.gov/25601394/ (summarised via https://www.setforset.com/blogs/news/new-research-on-tempo-training-and-rep-speed)
- Enes et al. 2025, tempo meta-analysis, summarised at https://www.setforset.com/blogs/news/new-research-on-tempo-training-and-rep-speed
- Wilk et al. 2024, review recommending 2–8 s reps: https://pmc.ncbi.nlm.nih.gov/articles/PMC10801605/
- OPEX, tempo notation: https://www.opexfit.com/blog/how-to-understand-and-use-tempo
- Initial vs final range in the arm curl: https://examine.com/summaries/study/9goqN9/
- Lengthened partials and supersets: https://www.strongerbyscience.com/?p=61260
- Momentum (cheat) reps preprint: https://biolayne.com/reps/issue-33/can-cheat-reps-deliver-results/ and https://pmc.ncbi.nlm.nih.gov/articles/PMC11970409/
- Proximity to failure meta-regression (Robinson et al., preprint): https://sportrxiv.org/index.php/server/preprint/download/295/699/654
- Velocity loss vs reps in reserve (Rodríguez-Rosell et al. 2020): https://www.uloyola.es/en/research-transfer/publications/relationship-between-velocity-loss-and-repetitions-in-reserve-in-the-bench-press-and-back-squat-exercises-article
- Weekly sets meta-regression (Pelland et al.): https://www.setforset.com/blogs/news/how-many-sets-to-build-muscle
