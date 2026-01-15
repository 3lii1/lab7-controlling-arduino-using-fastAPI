import threading
import time

import requests
import serial
from fastapi import FastAPI

app = FastAPI()

# --- Connect to Arduino ---
arduino = serial.Serial("COM7", 9600, timeout=1)
time.sleep(2)  # wait for Arduino to be ready

# --- Button debounce setup ---
last_pressed = {"red": 0, "green": 0, "blue": 0}
DEBOUNCE = 0.3  # seconds

# --- Function to send command to Arduino ---
def send_command(command):
    arduino.write(f"{command}\n".encode())
    arduino.flush()
    time.sleep(0.05)

# --- Function to call API ---
def call_api(color):
    try:
        requests.get(f"http://127.0.0.1:8000/led/{color}")
    except:
        print("Failed to call API")

# --- Listen to button presses ---
def listen_buttons():
    while True:
        line = arduino.readline().decode().strip()
        now = time.time()

        if line == "BUTTON_RED" and now - last_pressed["red"] > DEBOUNCE:
            last_pressed["red"] = now
            print("Red button pressed")
            call_api("red")

        elif line == "BUTTON_GREEN" and now - last_pressed["green"] > DEBOUNCE:
            last_pressed["green"] = now
            print("Green button pressed")
            call_api("green")

        elif line == "BUTTON_BLUE" and now - last_pressed["blue"] > DEBOUNCE:
            last_pressed["blue"] = now
            print("Blue button pressed")
            call_api("blue")

# --- Run listener in background ---
threading.Thread(target=listen_buttons, daemon=True).start()

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
