import cv2
import serial
import time
import json
import requests
import base64

with open('config.json', 'r') as f:
    cfg = json.load(f)

p_port = cfg['hardware']['serial_port']
b_rate = cfg['hardware']['baud_rate']
c_id = cfg['hardware']['camera_index']
url = cfg['model_settings']['local_api_url']
m_name = cfg['model_settings']['model_name']

ser = serial.Serial(p_port, b_rate, timeout=1)
cap = cv2.VideoCapture(c_id)

time.sleep(2)

val1x = 90
val1y = 90
val2x = 90
val2y = 90
val3u = 90
val3d = 90

while True:
    ret, frame = cap.read()
    if not ret:
        continue

    _, img_buf = cv2.imencode('.jpg', frame)
    b64_data = base64.b64encode(img_buf).decode('utf-8')

    req_body = {
        "model": m_name,
        "messages": [
            {
                "role": "user",
                "content": [
                    {"type": "text", "text": "Return the center coordinates X and Y of the main target as 'X,Y' scaled strictly between 0 and 180. Output nothing else."},
                    {"type": "image_url", "image_url": {"url": f"data:image/jpeg;base64,{b64_data}"}}
                ]
            }
        ],
        "temperature": 0.2
    }

    try:
        response = requests.post(f"{url}/chat/completions", json=req_body, timeout=4)
        raw_res = response.json()
        text_out = raw_res['choices'][0]['message']['content'].strip()
        
        if "," in text_out:
            split_vals = text_out.split(",")
            raw_x = int(float(split_vals[0].strip()))
            raw_y = int(float(split_vals[1].strip()))
            
            if raw_x < 0: raw_x = 0
            if raw_x > 180: raw_x = 180
            if raw_y < 0: raw_y = 0
            if raw_y > 180: raw_y = 180

            val1x = raw_x
            val1y = raw_y
            val2x = 180 - raw_x
            val2y = raw_y
            val3u = raw_y
            val3d = 180 - raw_y
    except:
        pass

    packet = f"${val1x} {val1y} {val2x} {val2y} {val3u} {val3d}\n"
    ser.write(packet.encode())

    cv2.imshow('preview', frame)
    if cv2.waitKey(30) & 0xFF == ord('q'):
        break

cap.release()
ser.close()
cv2.destroyAllWindows()