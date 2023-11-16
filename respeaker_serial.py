from tuning import Tuning
import usb.core
import usb.util
import time
import serial

def send_angle_to_arduino(angle, arduino_serial):
    message = f"Angle: {angle}\n"
    arduino_serial.write(message.encode('utf-8'))

arduino_port = '/dev/ttyACM0'  
arduino_baud_rate = 115200

# Open serial connection to Arduino
try:
    #arduino_serial = serial.Serial(arduino_port, arduino_baud_rate)
    arduino_serial = serial.Serial(arduino_port, arduino_baud_rate)

    print(f"Connected to Arduino on port {arduino_port}")
except Exception as e:
    print(f"Error: {e}")
    exit()

# Find ReSpeaker 4 Mic Array device
dev = usb.core.find(idVendor=0x2886, idProduct=0x0018)

if dev:
    Mic_tuning = Tuning(dev)
    print(f"Initial Sound Source Angle: {Mic_tuning.direction}")

    try:
        while True:
            angle = Mic_tuning.direction
            print(f"Sound Source Angle: {angle}")
            send_angle_to_arduino(angle, arduino_serial)
            time.sleep(1)
    except KeyboardInterrupt:
        pass
    finally:
        arduino_serial.close()
        print("Serial connection to Arduino closed.")
else:
    print("ReSpeaker 4 Mic Array not found.")
