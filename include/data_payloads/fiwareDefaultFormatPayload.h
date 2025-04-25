#ifndef FIWARE_DEFAULT_FORMAT_PAYLOADS_H
#define FIWARE_DEFAULT_FORMAT_PAYLOADS_H


const char* fiwareFormatPayload = 
R"({
    "biomassFluidAmount": {
        "type": "Number",
        "value": 0
    },
    "biomassPh": {
        "type": "Number",
        "value": 0
    },
    "biomassTemperature": {
        "type": "Number",
        "value": 0
    },
    "biomassWeight": {
        "type": "Number",
        "value": 0
    },
    "environmentGasCO2": {
        "type": "Number",
        "value": 0
    },
    "environmentGasO2": {
        "type": "Number",
        "value": 0
    },
    "environmentHumidity": {
        "type": "Number",
        "value": 0
    },
    "environmentTemperature": {
        "type": "Number",
        "value": 0
    },
    "m5BateryLevel": {
        "type": "Number",
        "value": 0
    },
    "id": "001",
    "type": "composter"
})";

#endif