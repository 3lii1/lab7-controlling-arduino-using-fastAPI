import time
import serial
from fastapi import FastAPI

app = FastAPI()

# --- Connect to Arduino ---
arduino = serial.Serial("COM7", 9600, timeout=1)
time.sleep(2)  # wait for Arduino to be ready


# --- Function to send command to Arduino ---
def send_command(command):
    arduino.write(f"{command}\n".encode())
    arduino.flush()
    time.sleep(0.05)


# --- FastAPI endpoints ---
@app.get("/led/on")
def all_on():
    send_command("ON")
    return {"status": "ok", "action": "all on"}


@app.get("/led/off")
def all_off():
    send_command("OFF")
    return {"status": "ok", "action": "all off"}


@app.get("/led/{color}")
def led_color(color: str):
    color = color.lower()

    if color == "red":
        send_command("1")
    elif color == "green":
        send_command("2")
    elif color == "blue":
        send_command("3")
    else:
        return {"status": "error", "message": "invalid color"}

    return {"status": "ok", "color": color}
