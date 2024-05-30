import network
import socket
import time
from machine import Pin, PWM

# Connect to Wi-Fi
ssid = 'Thomas netwerk 2.4G'  # Replace with your SSID
password = '37652357'  # Replace with your Wi-Fi password

wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect(ssid, password)

# Wait for connection
max_wait = 10
while max_wait > 0:
    if wlan.status() < 0 or wlan.status() >= 3:
        break
    max_wait -= 1
    print('Waiting for connection...')
    time.sleep(1)

# Handle connection failure
if wlan.status() != 3:
    raise RuntimeError('Network connection failed')
else:
    print('Connected to', ssid)
    ip = wlan.ifconfig()[0]
    print('IP Address:', ip)

# Set up the RGB LED pins
red = PWM(Pin(2))
green = PWM(Pin(3))
blue = PWM(Pin(4))

red2 = PWM(Pin(6))
green2 = PWM(Pin(8))
blue2 = PWM(Pin(9))

red3 = PWM(Pin(10))
green3 = PWM(Pin(12))
blue3 = PWM(Pin(13))

red.freq(1000)
green.freq(1000)
blue.freq(1000)

red2.freq(1000)
green2.freq(1000)
blue2.freq(1000)

red3.freq(1000)
green3.freq(1000)
blue3.freq(1000)

# Function to set the color of the RGB LED
def set_color(i, r, g, b):
    if i == 1:
        red.duty_u16(int(r * 65535 / 255))
        green.duty_u16(int(g * 65535 / 255))
        blue.duty_u16(int(b * 65535 / 255))
        print(f'Set color to R: {r}, G: {g}, B: {b}')
    elif i == 2:   
        red2.duty_u16(int(r * 65535 / 255))
        green2.duty_u16(int(g * 65535 / 255))
        blue2.duty_u16(int(b * 65535 / 255))
        print(f'Set color to R: {r}, G: {g}, B: {b}')
    elif i == 3:   
        red3.duty_u16(int(r * 65535 / 255))
        green3.duty_u16(int(g * 65535 / 255))
        blue3.duty_u16(int(b * 65535 / 255))
        print(f'Set color to R: {r}, G: {g}, B: {b}')
        
# Define a function to start the TCP server
def start_tcp_server():
    addr = socket.getaddrinfo(ip, 1234)[0][-1]  # Listen on all interfaces, port 1234
    s = socket.socket()
    s.bind(addr)
    s.listen(1)
    print('Listening on', addr)

    while True:
        cl, addr = s.accept()
        print('Client connected from', addr)
        cl_file = cl.makefile('rwb', 0)
        while True:
            line = cl_file.readline()
            if not line or line == b'\r\n':
                break
            print('Received:', line)
            # Decode the line and parse the RGB values
            command = line.decode('utf-8').strip()
            try:
                parts = command.split()
                i = int(parts[0].split('=')[1])
                r = int(parts[1].split('=')[1])
                g = int(parts[2].split('=')[1])
                b = int(parts[3].split('=')[1])
                set_color(i, r, g, b)
            except Exception as e:
                print('Failed to parse command:', e)
            cl.send(b'ACK\n')
        cl.close()
        print('Client disconnected')

# Start the TCP server
start_tcp_server()