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

## Despliegue en Raspberry PI

El proyecto incluye un sistema completo de despliegue con **Docker** diseñado específicamente para ejecutarse en **Raspberry PI**. Esta solución proporciona una infraestructura robusta y escalable que incluye el broker MQTT y el dashboard Node-RED ejecutándose como servicios containerizados.

### Arquitectura del despliegue

La solución de contenedores incluye:
- **Mosquitto MQTT Broker**: Servicio de mensajería ejecutándose en puerto 1884
- **Node-RED**: Dashboard web y motor de flujos en puerto 1880
- **Red Docker interna**: Para comunicación segura entre servicios
- **Persistencia de datos**: Volúmenes montados para mantener configuraciones y datos

### Estructura de archivos Docker

```
docker/
├── docker-compose.yml          # Orquestación de servicios
├── deploy.sh                   # Script de despliegue automatizado
├── mosquitto/
│   ├── mosquitto.conf         # Configuración del broker MQTT
│   └── data/                  # Datos persistentes de Mosquitto
└── node-red/
    ├── flows.json            # Configuración de flujos Node-RED
    └── data/                 # Datos persistentes de Node-RED
```

### Configuración de servicios

#### Mosquitto MQTT Broker
- **Puerto**: 1884 (no estándar para evitar conflictos)
- **Conexiones anónimas**: Habilitadas para facilitar desarrollo
- **Persistencia**: Datos guardados en `./mosquitto/data`
- **Configuración**: Archivo extenso con todas las opciones disponibles

#### Node-RED
- **Puerto**: 1880 (estándar)
- **Imagen**: `nodered/node-red:latest`
- **Flows**: Configuración inicial copiada automáticamente
- **Persistencia**: Datos guardados en `./node-red/data`

### Instalación automática

El script `deploy.sh` proporciona una instalación completamente automatizada:

#### Características del script:
- **Detección de Git**: Actualiza automáticamente el repositorio
- **Instalación de Docker**: Instala Docker si no está presente
- **Instalación de Docker Compose v2**: Compatible con arquitecturas ARM
- **Detección de arquitectura**: Soporte para aarch64, armv7l y x86_64
- **Creación de directorios**: Estructura necesaria para persistencia
- **Configuración inicial**: Copia automática de flows.json

#### Ejecución del despliegue:

```bash
# Navegar a la carpeta docker
cd docker/

# Ejecutar el script de despliegue
chmod +x deploy.sh
./deploy.sh
```

### Instalación manual paso a paso

Si prefieres un control manual del proceso:

#### 1. Preparar el sistema
```bash
# Actualizar el sistema
sudo apt update && sudo apt upgrade -y

# Instalar Docker (si no está instalado)
curl -fsSL https://get.docker.com -o get-docker.sh
sh get-docker.sh
sudo usermod -aG docker $USER

# Reiniciar sesión o ejecutar
newgrp docker
```

#### 2. Instalar Docker Compose v2
```bash
# Crear directorio para plugins
mkdir -p ~/.docker/cli-plugins

# Descargar Docker Compose para Raspberry PI (ARM64)
curl -SL https://github.com/docker/compose/releases/download/v2.24.6/docker-compose-linux-aarch64 \
  -o ~/.docker/cli-plugins/docker-compose

# Dar permisos de ejecución
chmod +x ~/.docker/cli-plugins/docker-compose
```

#### 3. Preparar configuraciones
```bash
# Crear directorios necesarios
mkdir -p docker/mosquitto/data
mkdir -p docker/node-red/data

# Copiar configuración inicial de Node-RED
cp docker/node-red/flows.json docker/node-red/data/flows.json
```

#### 4. Lanzar los servicios
```bash
# Desde la carpeta docker
docker compose up -d
```

### Verificación del despliegue

#### Comprobar estado de los contenedores:
```bash
# Ver servicios ejecutándose
docker compose ps

# Ver logs de los servicios
docker compose logs mosquitto
docker compose logs node-red
```

#### Acceso a los servicios:
- **Node-RED Dashboard**: `http://[IP_RASPBERRY]:1880/ui`
- **Node-RED Editor**: `http://[IP_RASPBERRY]:1880`
- **MQTT Broker**: `[IP_RASPBERRY]:1884`

### Configuración de dispositivos M5Stack

Para conectar los dispositivos M5Stack a la Raspberry PI, actualiza los archivos de configuración:

#### `include/config/mqttConnectionConfig.h`:
```cpp
// Cambiar la IP por la de tu Raspberry PI
#define MQTT_SERVER_IP "192.168.1.XXX"  // IP de la Raspberry PI
#define MQTT_SERVER_PORT 1884            // Puerto configurado en Docker
```

### Gestión del sistema

#### Comandos útiles:
```bash
# Parar todos los servicios
docker compose down

# Reiniciar servicios
docker compose restart

# Ver logs en tiempo real
docker compose logs -f

# Actualizar servicios (después de cambios en configuración)
docker compose down && docker compose up -d

# Limpiar recursos no utilizados
docker system prune -f
```

#### Backup y restauración:
```bash
# Backup de configuraciones
tar -czf backup-docker-$(date +%Y%m%d).tar.gz docker/

# Restaurar desde backup
tar -xzf backup-docker-YYYYMMDD.tar.gz
```

### Monitorización y mantenimiento

#### Ver uso de recursos:
```bash
# Estadísticas de contenedores
docker stats

# Espacio usado por Docker
docker system df
```

#### Logs del sistema:
```bash
# Logs de arranque de la Raspberry PI
sudo journalctl -b

# Logs específicos de Docker
sudo journalctl -u docker
```

### Solución de problemas comunes

#### Error de permisos:
```bash
# Añadir usuario al grupo docker
sudo usermod -aG docker $USER
newgrp docker
```

#### Puerto ocupado:
```bash
# Verificar puertos en uso
sudo netstat -tlnp | grep :1880
sudo netstat -tlnp | grep :1884
```

#### Problemas de conectividad MQTT:
```bash
# Probar conexión MQTT desde línea de comandos
mosquitto_pub -h localhost -p 1884 -t test/topic -m "hello"
mosquitto_sub -h localhost -p 1884 -t test/topic
```

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