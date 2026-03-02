# ===============================
#  Student Management System
# ===============================

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I./CMD_gestion/lib -I./GUI_gestion/lib
GTK_FLAGS = `pkg-config --cflags --libs gtk+-3.0`

SRC_CMD = CMD_gestion/CMD_gestion_etudiants.c \
          CMD_gestion/etudiant.c \
          CMD_gestion/fonctions.c

SRC_GUI = GUI_gestion/gestion_etudiants_gui.c \
          GUI_gestion/fonctions.c

BIN_DIR = bin

CMD_TARGET = $(BIN_DIR)/gestion_etudiants
GUI_TARGET = $(BIN_DIR)/gestion_etudiants_gui

# ===============================
# Default
# ===============================
all: cmd

# ===============================
# Console Version
# ===============================
cmd: prepare
	$(CC) $(CFLAGS) $(SRC_CMD) -o $(CMD_TARGET)

# ===============================
# GUI Version
# ===============================
gui: prepare
	$(CC) $(CFLAGS) $(SRC_GUI) -o $(GUI_TARGET) $(GTK_FLAGS)

# ===============================
# Create bin directory
# ===============================
prepare:
	mkdir -p $(BIN_DIR)

# ===============================
# Clean
# ===============================
clean:
	rm -rf $(BIN_DIR)

# ===============================
# Rebuild
# ===============================
re: clean all