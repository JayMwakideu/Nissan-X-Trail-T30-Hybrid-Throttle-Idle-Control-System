#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <EEPROM.h>

// OLED setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pins
#define RPM_PIN 2
#define PSP_PIN 3
#define AC_PIN 4
#define TEMP_PIN 6
#define BTN_MENU 7
#define BTN_UP 8
#define SERVO_PIN 9
#define BTN_DOWN 10
#define BUZZER_PIN 11
#define VOLT_PIN A0

// EEPROM addresses
#define EEPROM_BASE 0
#define EEPROM_COLD 2
#define EEPROM_AC   4

// Variables
volatile int pulseCount = 0;
OneWire oneWire(TEMP_PIN);
DallasTemperature sensors(&oneWire);

float rpm = 0;
float temp = 0;
float voltage = 0;
int servoPos = 0;

// PID variables
float Kp = 0.35;
float Ki = 0.02;
float Kd = 0.08;
float error = 0;
float lastError = 0;
float integral = 0;

// Tuning parameters
int baseIdle = 750;
int coldIdle = 1000;
int acAdd = 100;

// Menu
int menuState = 0;

// Stall warning
int stallThreshold = 500;

// Servo
Servo throttle;

// Pulse counting
void countPulse() { pulseCount++; }

// EEPROM functions
void saveSettings() {
  EEPROM.put(EEPROM_BASE, baseIdle);
  EEPROM.put(EEPROM_COLD, coldIdle);
  EEPROM.put(EEPROM_AC, acAdd);
}

void loadSettings() {
  EEPROM.get(EEPROM_BASE, baseIdle);
  EEPROM.get(EEPROM_COLD, coldIdle);
  EEPROM.get(EEPROM_AC, acAdd);
}

// Boot animation
void bootScreen() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(10,5);
  display.println("X-Trail T30");
  display.setTextSize(1);
  display.setCursor(30,30);
  display.println("Jay Overlander");

  // Loading bar
  display.drawRect(10,50,108,8,WHITE);
  for(int i=0;i<=108;i+=4){
    display.fillRect(10,50,i,8,WHITE);
    display.display();
    delay(50);
  }
}

// Startup diagnostics
void startupDiagnostics() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);
  display.println("STARTUP CHECK");

  display.println(rpm>0?"RPM OK":"RPM FAIL");
  display.println(temp>0?"TEMP OK":"TEMP FAIL");
  display.println(voltage>0?"VOLT OK":"VOLT FAIL");

  throttle.write(5); // Servo test
  delay(500);
  throttle.write(0);

  display.display();
  delay(2000);
}

// Menu handler
void handleMenu() {
  static unsigned long lastPress = 0;
  unsigned long now = millis();
  
  if(!digitalRead(BTN_MENU) && now - lastPress > 300){
    menuState++;
    if(menuState>3) menuState=0;
    lastPress = now;
  }

  if(menuState==1){
    if(!digitalRead(BTN_UP)) { baseIdle+=10; delay(100); }
    if(!digitalRead(BTN_DOWN)) { baseIdle-=10; delay(100); }
  } else if(menuState==2){
    if(!digitalRead(BTN_UP)) { coldIdle+=10; delay(100); }
    if(!digitalRead(BTN_DOWN)) { coldIdle-=10; delay(100); }
  } else if(menuState==3){
    if(!digitalRead(BTN_UP)) { acAdd+=10; delay(100); }
    if(!digitalRead(BTN_DOWN)) { acAdd-=10; delay(100); }
  }

  // Long press MENU to save
  if(!digitalRead(BTN_MENU) && now - lastPress > 1000){
    saveSettings();
    lastPress = now;
  }
}

// Draw dashboard
void drawDashboard(int targetRPM, bool ac, bool steer){
  display.clearDisplay();
  display.setTextSize(1);

  // Text info
  display.setCursor(0,0);
  display.print("RPM:");
  display.print(rpm);
  display.print(" T:");
  display.print(targetRPM);

  display.setCursor(0,10);
  display.print("TMP:");
  display.print(temp);

  display.setCursor(64,10);
  if(voltage>0.1) display.print("V:"); else display.print("V:---");
  if(voltage>0.1) display.print(voltage);

  display.setCursor(0,20);
  display.print("AC:");
  display.print(ac?"ON":"OFF");

  display.setCursor(64,20);
  display.print("STR:");
  display.print(steer?"ON":"OFF");

  // Servo bar
  display.setCursor(0,32);
  display.print("SERVO");
  int servoBar = map(servoPos,0,30,0,108);
  display.drawRect(10,42,108,8,WHITE);
  display.fillRect(10,42,servoBar,8,WHITE);

  // Graphical RPM dial
  int centerX=100, centerY=54, radius=10;
  display.drawCircle(centerX, centerY, radius, WHITE);
  float angle = map(rpm,0,2000,135,45);
  float rad = angle * 3.1416 / 180.0;
  int x = centerX + radius * cos(rad);
  int y = centerY - radius * sin(rad);
  display.drawLine(centerX, centerY, x, y, WHITE);

  // Stall warning
  if(rpm<stallThreshold){
    display.setCursor(0,56);
    display.print("!!LOW RPM!!");
    digitalWrite(BUZZER_PIN,HIGH);
  } else digitalWrite(BUZZER_PIN,LOW);

  display.display();
}

void setup(){
  throttle.attach(SERVO_PIN);

  pinMode(RPM_PIN,INPUT);
  pinMode(PSP_PIN,INPUT_PULLUP);
  pinMode(AC_PIN,INPUT);
  pinMode(BTN_MENU,INPUT_PULLUP);
  pinMode(BTN_UP,INPUT_PULLUP);
  pinMode(BTN_DOWN,INPUT_PULLUP);
  pinMode(BUZZER_PIN,OUTPUT);

  attachInterrupt(digitalPinToInterrupt(RPM_PIN),countPulse,FALLING);

  sensors.begin();
  loadSettings();
  display.begin(SSD1306_SWITCHCAPVCC,0x3C);
  bootScreen();
  startupDiagnostics();
}

void loop(){
  delay(500);

  rpm = pulseCount*30;   // Calculate RPM from coil signal
  pulseCount = 0;

  sensors.requestTemperatures();  
  temp = sensors.getTempCByIndex(0); // Temperature from DS18B20

  voltage = analogRead(VOLT_PIN)*(15.0/1023.0); // Optional Battery Voltage input

  bool ac = digitalRead(AC_PIN); // Read AC signal
  bool steer = !digitalRead(PSP_PIN); // Read Power Steering Pressure Switch

  int targetRPM = baseIdle;
  if(temp<40) targetRPM = coldIdle;
  if(ac) targetRPM += acAdd;
  if(steer) targetRPM += 150;

  // PID control
  error = targetRPM - rpm;
  integral += error;
  float derivative = error - lastError;
  float output = Kp*error + Ki*integral + Kd*derivative;
  servoPos += output;
  servoPos = constrain(servoPos,0,30);
  throttle.write(servoPos
