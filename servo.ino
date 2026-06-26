#include <Servo.h>

Servo a1x;
Servo a1y;
Servo a2x;
Servo a2y;
Servo a3u;
Servo a3d;

int v1x = 90;
int v1y = 90;
int v2x = 90;
int v2y = 90;
int v3u = 90;
int v3d = 90;

int t1x = 90;
int t1y = 90;
int t2x = 90;
int t2y = 90;
int t3u = 90;
int t3d = 90;

unsigned long p_tm = 0;

void setup() {
  Serial.begin(115200);
  
  a1x.attach(3);
  a1y.attach(5);
  a2x.attach(6);
  a2y.attach(9);
  a3u.attach(10);
  a3d.attach(11);
  
  a1x.write(v1x);
  a1y.write(v1y);
  a2x.write(v2x);
  a2y.write(v2y);
  a3u.write(v3u);
  a3d.write(v3d);
}

void loop() {
  if (Serial.available() > 0) {
    char data_hdr = Serial.read();
    if (data_hdr == '$') {
      t1x = Serial.parseInt();
      t1y = Serial.parseInt();
      t2x = Serial.parseInt();
      t2y = Serial.parseInt();
      t3u = Serial.parseInt();
      t3d = Serial.parseInt();
    }
  }

  unsigned long c_tm = millis();
  if (c_tm - p_tm >= 15) {
    p_tm = c_tm;
    
    if (v1x < t1x) v1x += 1;
    else if (v1x > t1x) v1x -= 1;
    
    if (v1y < t1y) v1y += 1;
    else if (v1y > t1y) v1y -= 1;
    
    if (v2x < t2x) v2x += 1;
    else if (v2x > t2x) v2x -= 1;
    
    if (v2y < t2y) v2y += 1;
    else if (v2y > t2y) v2y -= 1;
    
    if (v3u < t3u) v3u += 2;
    else if (v3u > t3u) v3u -= 2;
    if (abs(v3u - t3u) < 2) v3u = t3u;
    
    if (v3d < t3d) v3d += 2;
    else if (v3d > t3d) v3d -= 2;
    if (abs(v3d - t3d) < 2) v3d = t3d;
    
    a1x.write(v1x);
    a1y.write(v1y);
    a2x.write(v2x);
    a2y.write(v2y);
    a3u.write(v3u);
    a3d.write(v3d);
  }
}