/*
    MeasuresDataHelper.h - Library for set measures into Json payload to send
    Created by Ignacio Diestro Gil - 2025
*/

#ifndef MEASURES_DATA_HELPER_H
#define MEASURES_DATA_HELPER_H

#include <stdlib.h>
#include <time.h>
#include <Arduino.h>

class MeasuresDataHelper {
    public:
        MeasuresDataHelper();
        String setMeasuresIntoJson();
        void setComposterId(String composterId);
};

#endif
