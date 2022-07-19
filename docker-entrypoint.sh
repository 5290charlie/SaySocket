#!/usr/bin/env bash

# set -e

# COLORS! :)
red='\033[0;31m'
cyan='\033[0;36m'
blue='\033[0;34m'
yellow='\033[0;33m'
nocolor='\033[0m'

error() {
  prefix="[ERROR] "
  echo
  echo -e "${red}${prefix}${1}${nocolor}"
  echo
}

warn() {
  prefix="[WARNING] "
  echo
  echo -e "${yellow}${prefix}${1}${nocolor}"
  echo
}

log() {
  prefix="[INFO] "
  echo
  echo -e "${cyan}${prefix}${1}${nocolor}"
  echo
}

$APP_DIR/wait-for-it.sh ${DB_HOSTNAME}:${DB_PORT:-3306} --strict --timeout=60

APP_ENV=${APP_ENV:-local}
INI_PATH=/usr/local/etc/php
INI_MAIN=$INI_PATH/php.ini
INI_ENV=$INI_PATH/php-$APP_ENV.ini

if [ -f $INI_ENV ]; then
  log "Using php.ini for APP_ENV=$APP_ENV ($INI_ENV)"
  cp $INI_ENV $INI_MAIN
fi


nginx -t

exec "$@"
