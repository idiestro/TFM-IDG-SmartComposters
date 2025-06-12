# TFM-IDG-SmartComposters

Este proyecto implementa un sistema completo para la monitorización y gestión inteligente de compostadores utilizando la plataforma **M5Stack Core ESP32** y el framework **PlatformIO**. El sistema integra sensores físicos, conectividad MQTT, dashboard web con Node-RED e integración con la plataforma FIWARE.

## Funcionalidades principales

### 1. **Sistema de medición dual**
   - **Sensores reales**: Lectura de sensores físicos conectados via I2C y 1-Wire
     - Sensor ambiental ENV IV (temperatura y humedad)
     - Sensor de gases ENS160 (CO2 y calidad del aire)
     - Sensor de temperatura DS18B20 (temperatura de biomasa)
   - **Modo simulación**: Generación de datos aleatorios para pruebas
   - **Medidas monitorizadas**:
     - Temperatura y humedad ambiental
     - Niveles de oxígeno y dióxido de carbono
     - Temperatura, peso, cantidad de lixiviados y pH de la biomasa
     - Nivel de batería del dispositivo M5Stack

### 2. **Conectividad y comunicación**
   - Conexión WiFi configurable
   - Cliente MQTT con publicación y suscripción a tópicos
   - Formato de datos compatible con FIWARE NGSIv2
   - Transmisión de datos cada 10 segundos

### 3. **Dashboard y visualización**
   - **Node-RED** integrado con flows completos para:
     - Simulador de datos para testing
     - Dashboard web con gauges y gráficas en tiempo real
     - Gestión de conexiones MQTT
     - Computación de borde
     - Integración con FIWARE
   - Interface web responsive con tema oscuro

### 4. **Sistema de logs avanzado**
   - Visualización de mensajes en pantalla LCD del M5Stack
   - Registro detallado en puerto serie (115200 bps)
   - Sistema de logs con diferentes niveles de información

## Estructura del proyecto

```
├── include/                    # Archivos de cabecera
│   ├── config/                # Configuraciones del sistema
│   │   ├── mainConfig.h       # Configuración principal
│   │   ├── wifiConfig.h       # Parámetros WiFi
│   │   └── mqttConnectionConfig.h  # Configuración MQTT
│   ├── data_payloads/         # Formatos de datos
│   │   └── fiwareDefaultFormatPayload.h  # Payload FIWARE NGSIv2
│   └── utils/                 # Utilidades y herramientas
│       ├── I2cScan.txt        # Código para escaneo I2C
│       └── 1WireScan.txt      # Código para escaneo 1-Wire
├── lib/                       # Librerías específicas del proyecto
│   ├── mqttConnection/        # Gestión de conexión MQTT
│   ├── measuresReader/        # Lectura de sensores reales
│   ├── simulatedMeasures/     # Simulación de medidas
│   ├── measuresDataHelper/    # Procesamiento de datos
│   ├── logsUtils/            # Sistema de logging
│   ├── jsonUtils/            # Manipulación JSON
│   └── configReader/         # Lectura de configuraciones
├── src/                      # Código fuente principal
│   └── main.cpp              # Punto de entrada del programa
├── node-red/                 # Flows de Node-RED
│   └── flows.json            # Configuración completa del dashboard
├── platformio.ini            # Configuración de PlatformIO
└── README.md                 # Este archivo
```

## Dependencias y hardware

### Hardware requerido
- **M5Stack Core ESP32**
- **Sensores opcionales**:
  - M5Unit-ENV IV (temperatura y humedad ambiental)
  - ENS160 (sensor de gases CO2/calidad aire)
  - DS18B20 (sensor de temperatura 1-Wire para biomasa)

### Dependencias de software
```ini
# Definidas en platformio.ini
- M5Unified                    # Framework M5Stack
- PubSubClient                 # Cliente MQTT
- ArduinoJson ^6.21.2         # Manipulación JSON
- M5Unit-ENV                  # Soporte sensor ambiental
- ENS160_driver               # Driver sensor gases
- OneWire                     # Protocolo 1-Wire
- DallasTemperature           # Sensor DS18B20
```

## Configuración inicial

### 1. Configuración de conectividad
Edita los archivos en `include/config/`:
- `wifiConfig.h`: Credenciales de red WiFi
- `mqttConnectionConfig.h`: Parámetros del broker MQTT

### 2. Configuración de sensores
Los sensores se auto-detectan en los puertos:
- **Puerto A (I2C)**: Pines SDA=32, SCL=33
- **Puerto B (1-Wire)**: Para sensores DS18B20

### 3. Dashboard Node-RED
1. Instala Node-RED en tu sistema
2. Importa el archivo `node-red/flows.json`
3. Configura la dirección del broker MQTT
4. Accede al dashboard web en `http://localhost:1880/ui`

## Uso

### Modo desarrollo
```bash
# Compilar y subir al dispositivo
pio run --target upload

# Monitor serie para logs
pio device monitor
```

### Modo producción
1. Conecta el M5Stack Core ESP32 a alimentación
2. El sistema se conectará automáticamente a WiFi y MQTT
3. Los datos se envían cada 10 segundos al broker configurado
4. Visualiza los datos en el dashboard Node-RED

## Integración FIWARE

El sistema genera datos en formato NGSIv2 compatible con FIWARE:
```json
{
    "id": "001",
    "type": "composter",
    "environmentTemperature": {"type": "Number", "value": 25.4},
    "environmentHumidity": {"type": "Number", "value": 65.2},
    "environmentGasCO2": {"type": "Number", "value": 0.8},
    "biomassTemperature": {"type": "Number", "value": 28.1},
    // ... más atributos
}
```

## Funcionalidades Node-RED

El dashboard incluye:
- **Simulador de datos**: Para testing sin hardware
- **Monitores en tiempo real**: Gauges y gráficas de todas las medidas
- **Control MQTT**: Gestión de conexiones y tópicos
- **Computación de borde**: Procesamiento local de datos
- **Integración FIWARE**: Envío automático a Context Broker

## Desarrollo y extensión

### Añadir nuevos sensores
1. Crea nuevos métodos en `MeasuresReader.cpp`
2. Actualiza el payload en `fiwareDefaultFormatPayload.h`
3. Modifica `MeasuresDataHelper.cpp` para incluir los nuevos datos

### Personalizar dashboard
1. Edita los flows en Node-RED
2. Exporta la configuración actualizada a `flows.json`

## Créditos

**Autor**: Ignacio Diestro Gil  
**Año**: 2025  
**Proyecto**: TFM - Sistema de Compostadores Inteligentes  
**Tecnologías**: M5Stack, PlatformIO, MQTT, Node-RED, FIWARE