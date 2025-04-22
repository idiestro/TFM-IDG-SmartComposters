/*
    LogsUtils.cpp - Library for logs into lcd for M5Tough
    Created by Ignacio Diestro Gil - 2025
*/

#include "LogsUtils.h"

#include <M5Unified.h>

//Line counter
int LogsUtils::line=0;


/*
* Print a message to the serial port and LCD screen.
* If the LCD is full, it clears the screen and starts from the top.
* @param message: The message to print.
*/
void LogsUtils::printLog(String message) {
  //Print into serial port
  Serial.println(message);

  //Clean LCD if empty
  if (line >= maxLines || line == 0) {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setTextColor(WHITE);
    line = 0;
  }

  M5.Lcd.setCursor(10, 10 + line * lineHeight); // Coordenadas X, Y
  M5.Lcd.print(message);
  line++;
}