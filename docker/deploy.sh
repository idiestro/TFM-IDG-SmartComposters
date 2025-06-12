#!/bin/bash

set -e  # Detener en caso de error

# === RUTAS RELATIVAS DESDE LA UBICACIÓN DEL SCRIPT ===
SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
MOSQUITTO_DIR="$SCRIPT_DIR/mosquitto"
NODE_RED_DIR="$SCRIPT_DIR/node-red"
COMPOSE_FILE="$SCRIPT_DIR/docker-compose.yml"

# === ACTUALIZACIÓN DEL REPO ===
if git -C "$SCRIPT_DIR/../" rev-parse --is-inside-work-tree > /dev/null 2>&1; then
  echo "📡 Actualizando el repositorio desde remoto..."
  git -C "$SCRIPT_DIR/../" pull
else
  echo "⚠️ No se detectó un repositorio Git válido. Se omite el pull."
fi

echo "🚀 Iniciando despliegue desde el sistema local..."

# === FUNCIONES ===

check_docker() {
  if ! command -v docker &> /dev/null; then
    echo "🛠️ Instalando Docker..."
    curl -fsSL https://get.docker.com -o get-docker.sh
    sh get-docker.sh
    sudo usermod -aG docker "$USER"
    echo "🔁 Docker instalado. Reinicia sesión o ejecuta 'newgrp docker'."
  else
    echo "✅ Docker ya está instalado."
  fi
}

check_docker_compose() {
  if ! docker compose version &> /dev/null; then
    echo "🛠️ Instalando Docker Compose v2..."
    DOCKER_CONFIG=${DOCKER_CONFIG:-$HOME/.docker}
    mkdir -p $DOCKER_CONFIG/cli-plugins
    ARCH=$(uname -m)
    if [[ "$ARCH" == "aarch64" ]]; then
      COMPOSE_ARCH="aarch64"
    elif [[ "$ARCH" == "armv7l" ]]; then
      COMPOSE_ARCH="armv7"
    else
      COMPOSE_ARCH="x86_64"
    fi
    curl -SL https://github.com/docker/compose/releases/download/v2.24.6/docker-compose-linux-$COMPOSE_ARCH -o $DOCKER_CONFIG/cli-plugins/docker-compose
    chmod +x $DOCKER_CONFIG/cli-plugins/docker-compose
    echo "✅ Docker Compose v2 instalado."
  else
    echo "✅ Docker Compose ya está instalado."
  fi
}

deploy_stack() {
  echo "📁 Creando carpetas necesarias..."
  mkdir -p "$MOSQUITTO_DIR/data"
  mkdir -p "$NODE_RED_DIR/data"

  echo "🔄 Verificando flows.json de Node-RED..."

  # Copiar flows.json si no existe ya en data
  TARGET_FLOW="$NODE_RED_DIR/data/flows.json"
  if [ ! -f "$TARGET_FLOW" ]; then
    echo "📥 Copiando flows.json inicial..."
    cp "$NODE_RED_DIR/flows.json" "$TARGET_FLOW"
  else
    echo "ℹ️ flows.json ya existe en 'data/', no se sobrescribe."
  fi

  echo "🚢 Lanzando contenedores..."
  docker compose -f "$COMPOSE_FILE" up -d

  echo "✅ Despliegue completado."
}

# === EJECUCIÓN ===

check_docker
check_docker_compose
deploy_stack
