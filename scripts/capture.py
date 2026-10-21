"""
Spot capture: saves one set of IMU data per CSV file.
Usage: python capture.py COM5 curl_good 10
Press Enter to start recording, Enter again to stop.
Close the Arduino Serial Monitor first.
"""
import os, sys, threading, time
from datetime import datetime
import serial

if len(sys.argv) < 4:
    print(__doc__); sys.exit(1)

port, label, reps = sys.argv[1], sys.argv[2], sys.argv[3]
os.makedirs("data", exist_ok=True)

ser = serial.Serial(port, 115200, timeout=1)
time.sleep(1)
ser.reset_input_buffer()

input(f"[{label}, {reps} reps] Press Enter to START...")
ser.reset_input_buffer()
rows, stop = [], threading.Event()

def reader():
    while not stop.is_set():
        line = ser.readline().decode(errors="ignore").strip()
        parts = line.split(",")
        if len(parts) == 7 and parts[0].isdigit():
            rows.append(line)

t = threading.Thread(target=reader, daemon=True)
t.start()
input("Recording... press Enter to STOP.")
stop.set(); t.join(); ser.close()

stamp = datetime.now().strftime("%Y%m%d_%H%M%S")
path = os.path.join("data", f"{label}_{reps}reps_{stamp}.csv")
with open(path, "w") as f:
    f.write("t_ms,ax,ay,az,gx,gy,gz\n")
    f.write("\n".join(rows) + "\n")
print(f"Saved {len(rows)} samples to {path}")