# TFM-IDG-SmartComposters

Este proyecto implementa un sistema para la monitorización y gestión de compostadores inteligentes utilizando la plataforma **M5Stack Tough** y el framework **PlatformIO**. El sistema incluye simulación de medidas, conexión a un broker MQTT y registro de logs en pantalla y en el puerto serie.

## Funcionalidades principales

1. **Simulación de medidas**:
   - Temperatura y humedad ambiental.
   - Niveles de oxígeno y dióxido de carbono.
   - Temperatura, peso, cantidad de fluido y pH de la biomasa.

2. **Conexión MQTT**:
   - Conexión a una red WiFi y a un broker MQTT.
   - Publicación y suscripción a tópicos MQTT.

3. **Registro de logs**:
   - Visualización de mensajes en la pantalla LCD del M5Stack Tough.
   - Registro de mensajes en el puerto serie.

## Estructura del proyecto
├── config/ # Archivos de configuración

├── lib/ # Librerías específicas del proyecto

├── src/ # Código fuente principal │ ├── main.cpp # Punto de entrada del programa

├── test/ # Pruebas del proyecto

├── platformio.ini # Archivo de configuración de PlatformIO

## Configuración inicial

1. Configura los parámetros de conexión WiFi y MQTT en los archivos de configuración dentro de la carpeta `config/`.
2. Compila y sube el código al dispositivo utilizando PlatformIO.

## Uso

1. Conecta el M5Stack Tough a tu computadora.
2. Abre el monitor serie para visualizar los logs y datos generados.
3. El sistema comenzará a simular medidas y enviarlas al broker MQTT configurado.

## Créditos

Creado por Ignacio Diestro Gil - 2025.