/*
    LogsUtils.H - Library for logs into lcd for M5Tough
    Created by Ignacio Diestro Gil - 2025
*/

#ifndef LOGS_UTILS_H
#define LOGS_UTILS_H

#include <M5Unified.h>

class LogsUtils {
  public:
    static void printLog(String message);

  private:
    static int line;
    static const int lineHeight = 20;
    static const int maxLines = 10;
};

#endif
