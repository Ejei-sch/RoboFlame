#include <RobotixInnoBot.h>

int FireDetected = 0;

RobotixInnoBot bot;
long temps200=0 ;

void setup() {
  bot.begin();
  Serial.begin(115200);

  bot.rjLdrInit(bot.port_1);
  bot.rjIrInit(bot.port_1);
  bot.rjIrInit(bot.port_2);
    bot.clearLCD();
  bot.drawString(10,4,"RoboFlame", FONT_SMALL);

}

void loop() {
    if ((millis()-temps200)>=200) {
      temps200=millis();
      bot.addModToMonitor(bot.port_1);
      Serial.println(bot.getMonitorData());
    }
    if (FireDetected == 0) {
      if (bot.rjIrRead(bot.port_1) < 675 & bot.rjIrRead(bot.port_2) < 675) {
        bot.setMotorSpeed(bot.motor_1,-0);
        bot.setMotorSpeed(bot.motor_2,-0);
      } else if (bot.rjIrRead(bot.port_1) > 675) {
        bot.setMotorSpeed(bot.motor_1,-70);
        bot.setMotorSpeed(bot.motor_2,-0);
      } else if (bot.rjIrRead(bot.port_2) < 675) {
        bot.setMotorSpeed(bot.motor_1,-0);
        bot.setMotorSpeed(bot.motor_2,-100);
      } else {
        bot.setMotorSpeed(bot.motor_1,-100);
        bot.setMotorSpeed(bot.motor_2,-70);
      }
    }
    if (FireDetected == 1) {
      bot.setMotorSpeed(bot.motor_1,-0);
      bot.setMotorSpeed(bot.motor_2,-0);
      bot.setMotorSpeed(bot.motor_3,-250);
      delay(2*1000);
      bot.setMotorSpeed(bot.motor_3,-0);
      FireDetected = 0;
    }
    if (FireDetected == 0) {
      if (bot.rjLdrRead(bot.port_1) > 580) {
        FireDetected = 1;
      }
    }

}