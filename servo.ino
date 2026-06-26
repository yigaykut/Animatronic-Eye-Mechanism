#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pca = Adafruit_PWMServoDriver();

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

void s_drv(uint8_t ch, int ang) {
  int pw = map(ang, 0, 180, 150, 600);
  pca.setPWM(ch, 0, pw);
}

void setup() {
  Serial.begin(115200);
  pca.begin();
  pca.setOscillatorFrequency(27000000);
  pca.setPWMFreq(50);
  
  s_drv(0, v1x);
  s_drv(1, v1y);
  s_drv(2, v2x);
  s_drv(3, v2y);
  s_drv(4, v3u);
  s_drv(5, v3d);
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
    
    s_drv(0, v1x);
    s_drv(1, v1y);
    s_drv(2, v2x);
    s_drv(3, v2y);
    s_drv(4, v3u);
    s_drv(5, v3d);
  }
}
