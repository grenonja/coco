// Platform libraries.
#include <Arduino.h>  // To add IntelliSense for platform constants.

// Third-party libraries.
#include <ESP8266WiFi.h> //ned this to set Wemos to sleep

// My classes.
#include "speed-servo.h"
#include "status-led.h"
#include "proximity-sensor.h"

#include "config.h"  // To store configuration and secrets.

#define FPM_SLEEP_MAX_TIME 0xFFFFFFF

SpeedServo lidServo;
SpeedServo switchServo;
StatusLed led;
ProximitySensor sensor;
os_timer_t myTimer;

int lastSwitchState = 0;
int resetTime = 15000;
long playCount = 0;
bool isLidOpen = false;
bool monitorSensor = false;
bool tickOccured = false;

void setup() {
  initSerial();
  initServos();
  initLed();
  initSensor();
  pinMode(PIN_SWITCH, INPUT);
  initTimer();

  Serial.printf("Application version: %s\n", APP_VERSION);
  Serial.println("Setup completed.");
}


void timerCallback(void *pArg)
{
  tickOccured = true;
} 

void initTimer(void)
{
  os_timer_setfn(&myTimer, timerCallback, NULL);
  setTimer();
  tickOccured = false;
}

void setTimer(){
os_timer_arm(&myTimer, resetTime, true);
Serial.println("set Timer");
}

void initSerial() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Initializing serial connection DONE.");
}

void initServos() {
  lidServo.attach(PIN_LID_SERVO);
  lidServo.moveNowTo(LID_START_POSITION);

  switchServo.attach(PIN_SWITCH_SERVO);
  switchServo.moveNowTo(SWITCH_START_POSITION);
}

void initLed() {
  led.setPin(LED_BUILTIN);
  led.turnOff();
}


void initSensor() {
  sensor.attach(PIN_SENSOR_SDA, PIN_SENSOR_SCL, SENSOR_TRIGGER_THRESHOLD);
}

void lightSleep(){
  Serial.println("going to light sleep");
  gpio_pin_wakeup_enable(GPIO_ID_PIN(PIN_SWITCH), GPIO_PIN_INTR_LOLEVEL);
  wifi_set_opmode(NULL_MODE);
  wifi_fpm_set_sleep_type(LIGHT_SLEEP_T);
  wifi_fpm_open();
  wifi_fpm_set_wakeup_cb(callback);
  wifi_fpm_do_sleep(FPM_SLEEP_MAX_TIME);
}

void callback()
{
  Serial1.println("Callback");
  Serial.flush();
}

void loop() {
  int switchState = digitalRead(PIN_SWITCH);
  boolean isSwitchTurnedOn = (switchState != lastSwitchState) && (switchState == LOW);

  if (tickOccured == true)
  {
    Serial.println("Tick Occurred");
    resetBox();    
    lightSleep();
    delay(250);
  }

  if (isSwitchTurnedOn) {
    led.turnOn();
    run();
    isLidOpen = false;
    led.turnOff();
  } else {
    // Check the proximity sensor.
    if (sensor.isInRange()) {
      setTimer();
      if (!isLidOpen && monitorSensor) {
        openLidFast();
        isLidOpen = true;
      }
    } else {
      if (isLidOpen) {
        closeLidFast();
        isLidOpen = false;
      }
    }
  }

  lastSwitchState = switchState;

  // Wait 250 ms before next reading (required for the sensor).
  delay(250);
}

void resetBox(){
  playCount = 0;
  monitorSensor = false;
  tickOccured = false;
  Serial.println("reset box");
}

void run() {
  switch (playCount % 10) {
    case 0:
      runFastThenClap();   
        break;
      case 1:
        runSlow();
        monitorSensor = true;
        break;
      case 2:
        closeLidSlow();
        runWaitThenFast();
        break;
      case 3:
        closeLidFast();
        runFast();
        break;
      case 4:
        runFastThenClap();
        monitorSensor = true;
        break;
      case 5:
        runOpenCloseThenFast();
        monitorSensor = false;
        break;
      case 6:
        runPeekThenFast();
        break;
      case 7:
        runFastWithDelay();
        monitorSensor = true;
        break;
      case 8:
        runClap();
        monitorSensor = false;
        break;
      case 9:
        runHalf();
        break;
      default:
        break;
      }

      playCount++;
      setTimer();
}

void runSlow() {
  openLidSlow();
  flipSwitchSlow();
  closeLidSlow();
}

void runWaitThenFast() {
  delay(5000);
  flipSwitchFast();
  closeLidSlow();
}

void runFast() {
  flipSwitchFast();
  closeLidFast();
}

void runFastThenClap() {
  flipSwitchFast();
  clapLid();
}

void runOpenCloseThenFast() {
  openLidSlow();
  delay(2000);
  closeLidSlow();
  delay(2000);
  flipSwitchFast();
}

void runPeekThenFast() {
  switchServo.moveSlowTo(SWITCH_HALF_POSITION);
  delay(3000);
  switchServo.moveFastTo(SWITCH_START_POSITION);
  delay(3000);
  flipSwitchFast();
}

void runFastWithDelay() {
  openLidSlow();
  delay(4000);
  flipSwitchFast();
  closeLidFast();
}

void runClap() {
  clapLid();
  clapLid();
  openLidFast();
  flipSwitchFast();
  closeLidFast();
}

void runHalf() {
  switchServo.moveSlowTo(SWITCH_HALF_POSITION);
  delay(3000);
  switchServo.moveFastTo(SWITCH_END_POSITION);
  switchServo.moveFastTo(SWITCH_START_POSITION);
}

void openLidSlow() {
  lidServo.moveSlowTo(LID_END_POSITION);
}

void openLidFast() {
  lidServo.moveFastTo(LID_END_POSITION);
}

void closeLidSlow() {
  lidServo.moveSlowTo(LID_START_POSITION);
}

void closeLidFast() {
  lidServo.moveFastTo(LID_START_POSITION);
}

void clapLid() {
  openLidFast();
  closeLidFast();
  openLidFast();
  closeLidFast();
  openLidFast();
  closeLidFast();
}

void flipSwitchSlow() {
  switchServo.moveSlowTo(SWITCH_END_POSITION);
  switchServo.moveSlowTo(SWITCH_START_POSITION);
}

void flipSwitchFast() {
  switchServo.moveFastTo(SWITCH_END_POSITION);
  switchServo.moveFastTo(SWITCH_START_POSITION);
}
