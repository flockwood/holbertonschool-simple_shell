# C - Simple Shell

## Description

Simple Shell es un intérprete de comandos UNIX desarrollado en C que emula funcionalidades básicas de `sh`.  
Permite ejecutar comandos desde la línea de comandos, tanto en modo interactivo como no interactivo.

## File Structure

| Archivo            | Descripción                                           |
|--------------------|-------------------------------------------------------|
| `main.c`           | Contiene la función principal que inicia el shell.    |
| `executor.c`       | Maneja la ejecución de comandos externos.             |
| `builtins.c`       | Implementa comandos internos como `exit` y `env`.     |
| `utils.c`          | Funciones de utilidad para tokenizar y limpiar entrada. |
| `path.c`           | Busca comandos en los directorios especificados en `PATH`. |
| `main.h`           | Archivo de encabezado con definiciones y prototipos.  |

## Installation

1. Clona este repositorio:
   git clone https://github.com/flockwood/holbertonschool-simple_shell.git

2. Compila el programa:
   gcc -Wall -Werror -Wextra -pedantic *.c -o hsh

## Usage

- **Modo interactivo**:
  ./hsh
  El shell mostrará un prompt y esperará comandos del usuario.

- **Modo no interactivo**:
  echo "ls -l" | ./hsh
  El shell ejecutará los comandos proporcionados y luego saldrá.

## Features

- Ejecución de comandos externos encontrados en `PATH`.
- Soporte para comandos internos: `exit`, `env`.
- Manejo de modo interactivo y no interactivo.
- Manejo de errores similar a `/bin/sh`.

## Built-in Commands

- `exit`: Termina el shell.
- `env`: Muestra las variables de entorno actuales.

## Authors

- Fernando Lockwood  
- Andrés Mora

