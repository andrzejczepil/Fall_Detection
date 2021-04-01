#include <WiFiNINA.h>
#include <Arduino_LSM6DS3.h>
#include <Wire.h>
#include <Base64.h>
#include "DANE.h"
#include <Arduino.h>
#include "wiring_private.h"

Uart mySerial (&sercom0, 5, 6, SERCOM_RX_PAD_1, UART_TX_PAD_0);
void SERCOM0_Handler(){
    mySerial.IrqHandler();
}
IPAddress ip(192, 168, 10, 80);
WiFiServer server(80);
WiFiClient sse;

char ssid[] = nazwa_sieci;
char pass[] = haslo_sieci;
char webpage_base64[] = "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";
float accelX,            accelY,             accelZ,            
      gyroX,             gyroY,              gyroZ,
      gyroDriftX,        gyroDriftY,         gyroDriftZ,             
      gyroRoll,          gyroPitch,          acc,                   
      still_lying,       lying1,             lying2;           
float gyroRoll_prefall,  gyroPitch_prefall,                     
      gyroRoll_postfall, gyroPitch_postfall,                    
      RollDifference,    PitchDifference,
      PreDifference,     PostDifference,                       
      RollandPitchDifference;                                         
boolean fall = false;
boolean phase1 = true;
boolean phase2 = false;
boolean phase3 = false;
boolean phase4 = false;
float Max_Angle = 60;
float acc_max = 3;
float acc_min = 0.8;
int time_of_falling_phase = 500; //chosen by numerous experiments
int time_of_lying_phase = 500; //chosen by numerous experiments
float zmienna=0;
boolean on = false;
unsigned long previousGravityMillis = 0;

void setup() {
  pinPeripheral(5, PIO_SERCOM_ALT);
  pinPeripheral(6, PIO_SERCOM_ALT);
  mySerial.begin(9600);
  //Serial.begin(9600);
  delay(500);
  mySerial.write("ATE0\r");
  delay(500);
  mySerial.write("ATS0=1\r");
  delay(500);
  WiFiConnect();
  if (!IMU.begin()) {
    while (1);
  }
  calibrateIMU(500);
}

void calibrateIMU(int calibrationMillis) {
  int calibrationCount = 0;
  float sumX, sumY, sumZ;
  int startTime = millis();
  while (millis() < startTime + calibrationMillis) {
    if (readIMU()) {
      sumX += gyroX;
      sumY += gyroY;
      sumZ += gyroZ;
      calibrationCount++;
    }
  }
  if (calibrationCount == 0) {
    //Serial.println("Failed to calibrate");
  }
  gyroDriftX = sumX / calibrationCount;
  gyroDriftY = sumY / calibrationCount;
  gyroDriftZ = sumZ / calibrationCount;
}

bool readGYRO() {
  if (IMU.gyroscopeAvailable() ) {
    IMU.readGyroscope(gyroX, gyroY, gyroZ);
    return true;
  }
  return false;
}
bool readACCEL() {
  if (IMU.accelerationAvailable() ) {
    IMU.readAcceleration(accelX, accelY, accelZ);
    return true;
  }
  return false;
}
bool readIMU() {
  if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable() ) {
    IMU.readAcceleration(accelX, accelY, accelZ);
    IMU.readGyroscope(gyroX, gyroY, gyroZ);
    return true;
  }
  return false;
}

void loop() {
 if (WiFi.status() != WL_CONNECTED) {
    sse.stop();
    WiFi.end();
    WiFiConnect();
  }
  WiFiClient client = server.available();  
  if (client) {
    String header = "";
    String elname = "";
    String value = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c != '\r') {
          header += c;
        }
        if (header.substring(header.length() - 2) == "\n\n") {
          if (header.indexOf("HEAD /?") > -1) {
            client.println("HTTP/1.1 200 OK");
            client.println("");
            client.stop();
            header.remove(0, header.indexOf("?")+1);
            header.remove(header.indexOf(" "));
            elname = header.substring(0, header.indexOf("="));
            boolean goodSettings = true;
            if (elname == "switch") {
              on = "true";
            }
            else {
              goodSettings = false;
            }
            if (goodSettings) {
              sse.println("data: Serwer Działa" );
            } else {
              sse.println("Bad data; ignored");
            }
            sse.println("");
          } 
          else if (header.indexOf("event-stream") > -1) {
            if (sse.connected()) {
              sse.stop();
            }
            client.println("HTTP/1.1 200 OK\nConnection: Keep-Alive");
            client.println("Content-Type: text/event-stream\nCache-Control: no-cache\n");
            sse = client;
            break;
          } 
          else if (header.indexOf("POST / HTTP") > -1) {
            client.println("HTTP/1.1 200 OK\n");
            client.stop();
            sse.stop();
          } 
          else if (header.indexOf("GET / HTTP") > -1) {
            client.println("HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Encoding: gzip\n");
            const int webpage_base64_length = sizeof(webpage_base64);
            const int webpage_gz_length = base64_dec_len(webpage_base64, webpage_base64_length);
            char webpage_gz[webpage_gz_length];
            base64_decode(webpage_gz, webpage_base64, webpage_base64_length);
            int packetsize = 512;
            int done = 0;
            while (webpage_gz_length > done) {
              if (webpage_gz_length - done < packetsize) {
                packetsize = webpage_gz_length - done;
              }
              client.write(webpage_gz + done, packetsize * sizeof(char));
              done = done + packetsize;
            }
            client.stop();
          } 
          else {
            client.println("HTTP/1.1 404 Not Found\nContent-Type: text/plain; charset=utf-8\n\n404 Not Found\n");
            client.stop();
          }
        }
      }
    }
 }  
 if(fall==true){
   emergency();
   delay(1000);
   fall=false;
   phase1 = true;
   phase2 = false;
   phase3 = false;
   phase4 = false;
 }
 else{
  if(phase4==true){
    int lying = 0;
    if(readACCEL()){
      doCalculationsACCEL();
      lying1=acc;
    }
    int counter2=0;
     while(counter2<time_of_lying_phase){
        counter2++;
    }
    if(readACCEL()){
      doCalculationsACCEL();
      lying2=acc;
    }
    doCalculations_lying_DIFFR();
    if(still_lying<2){
      fall=true;
      phase1 = false;
      phase2 = false;
      phase3 = false;
      phase4 = false;
    }
    else{
      phase1 = true;
      phase2 = false;
      phase3 = false;
      phase4 = false;
    }
  }
  else if(phase3==true){
    int counter=0;
    while(counter<100){
      if(readGYRO()){
        doCalculationsGYRO();
        counter++;
      }
    }
    doCalculationsGYRO();
    gyroRoll_postfall = gyroRoll;
    gyroPitch_postfall = gyroPitch;
    doCalculations_falling_DIFFR();
    if(RollandPitchDifference>Max_Angle){
      phase1 = false;
      phase2 = false;
      phase3 = false;
      phase4 = true;
    }
    else{
      phase1 = true;
      phase2 = false;
      phase3 = false;
      phase4 = false;
    }
  }
  else if(phase2==true){
    int falling = 0;
    while(falling<time_of_falling_phase){
      if(readIMU()){
        doCalculationsACCEL();
        doCalculationsGYRO();
        if(acc>acc_max){
          phase1 = false;
          phase2 = false;
          phase3 = true;
          phase4 = false;
          break;
        }
        else{
          falling++;
        }
      }
    }
    if(phase3 != true){
      phase1 = true;
      phase2 = false;
      phase3 = false;
      phase4 = false;
    }
  }
  else if(phase1==true){
    if(readIMU()){
      doCalculationsGYRO();
      doCalculationsACCEL();
      if(acc<acc_min){
        gyroRoll_prefall = gyroRoll;
        gyroPitch_prefall = gyroPitch;
        phase1 = false;
        phase2 = true;
        phase3 = false;
        phase4 = false;
      }
      else{
        phase1 = true;
        phase2 = false;
        phase3 = false;
        phase4 = false;
      }
    }
  }
 }
 if(sse.connected()) {
  unsigned long currentGravityMillis = millis();
  if ((currentGravityMillis - previousGravityMillis) > 500) {
    previousGravityMillis = currentGravityMillis;
    if(fall==true){
      zmienna = 1;
    }
    else if(acc>1.5||acc<0.5){
      zmienna = 2;
    }
    else{
      zmienna = 0;
    }
    sse.println("event: gravity\ndata: " + String(acc,1) + "\n");
    sse.println("event: alert\ndata: "+String(zmienna) + "\n");
    }
  }
}

void WiFiConnect() {
  WiFi.config(ip);
  WiFi.setHostname("nano-webserver");
  while (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, pass);
    delay(5000);
  }
  server.begin();
  //Serial.println("connected to wifi");
  WiFi.lowPowerMode();
}

void doCalculationsGYRO() {
  gyroPitch = gyroPitch + ((gyroX - gyroDriftX) / IMU.gyroscopeSampleRate());
  gyroRoll = gyroRoll + ((gyroZ - gyroDriftZ)  / IMU.gyroscopeSampleRate());
}

void doCalculationsACCEL() {
  acc = pow(pow(accelX,2)+pow(accelY,2)+pow(accelZ,2),0.5);
}

void doCalculations_falling_DIFFR(){
  RollDifference = abs(gyroRoll_postfall-gyroRoll_prefall);
  PitchDifference = abs(gyroPitch_postfall-gyroPitch_prefall);
  RollandPitchDifference=pow(pow(RollDifference,2)+pow(PitchDifference,2),0.5);
}

void doCalculations_lying_DIFFR(){
  still_lying = abs(abs(lying2)-abs(lying1));
}
void emergency(){
  delay(5000);
  mySerial.write("ATD+ +48100200300;\r"); 
  delay(60000);
  mySerial.write("ATH\r");
  delay(1000);
  mySerial.write("AT+CMGF=1\r");
  delay(500);
  mySerial.write("AT+CMGS=\"+48100200300\"\r");  
  delay(500);
  mySerial.write("Fall Detected"); 
  delay(500);
  mySerial.write((char)26);
  delay(500);
  mySerial.write("\r");
}
