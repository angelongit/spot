"""
Rep Tracker - Phase 0: record one set of IMU data to a CSV file.

Setup (once):   pip install pyserial
Usage:          python log_set.py COM5 curl_10reps.csv
                (Mac/Linux port looks like /dev/cu.usbmodem1101 or /dev/ttyACM0)

Close the Arduino Serial Monitor first - only one program can use the port.
Press Ctrl+C when the set is done.
"""
import sys
import serial

if len(sys.argv) != 3:
    print("Usage: python log_set.py <serial_port> <output_file.csv>")
    sys.exit(1)

port, out_path = sys.argv[1], sys.argv[2]

with serial.Serial(port, 115200, timeout=1) as ser, open(out_path, "w") as f:
    print(f"Recording to {out_path}... press Ctrl+C to stop.")
    lines = 0
    try:
        while True:
            line = ser.readline().decode(errors="ignore").strip()
            if not line:
                continue
            f.write(line + "\n")
            lines += 1
            if lines % 100 == 0:
                print(f"  {lines} samples (~{lines / 100:.0f} s)")
    except KeyboardInterrupt:
        pass

print(f"Saved {lines} lines to {out_path}")
