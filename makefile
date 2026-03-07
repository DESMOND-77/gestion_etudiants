# ===============================
#  Student Management System
# ===============================

CC = gcc
CMD_CFLAGS = -Wall -Wextra -std=c99 -I./libs
GUI_CFLAGS = -Wall -Wextra -std=c99 -I./libs $(shell pkg-config --cflags gtk+-3.0)
GTK_FLAGS = `pkg-config --cflags --libs gtk+-3.0`
LDFLAGS =

# Console Version Sources
CMD_SRC = CMD_gestion/CMD_gestion_etudiants.c \
          functions/etudiant.c \
          functions/fonctions.c

# GUI Version Sources
GUI_SRC = GUI_gestion/GUI_gestion_etudiants.c \
          functions/fonctions.c

# Object files
CMD_OBJS = CMD_gestion/CMD_gestion_etudiants.o \
           functions/etudiant.o \
           functions/fonctions.o

GUI_OBJS = GUI_gestion/GUI_gestion_etudiants.o \
           functions/etudiant.o \
           functions/fonctions.o

CMD_TARGET = cmd_gestion_etudiants
GUI_TARGET = gui_gestion_etudiants


.PHONY: all clean run-cmd run-gui help cmd gui

# ===============================
# Default target: build both versions
# ===============================
all: cmd gui

# ===============================
# Explicit targets for each version
# ===============================
cmd: $(CMD_TARGET)

gui: $(GUI_TARGET)

# ===============================
# Console Version
# ===============================
$(CMD_TARGET): $(CMD_OBJS)
	$(CC) $(CMD_OBJS) -o $(CMD_TARGET) $(LDFLAGS)

CMD_gestion/%.o: CMD_gestion/%.c
	$(CC) $(CMD_CFLAGS)  -c $< -o $@

functions/%.o: functions/%.c
	$(CC) $(CMD_CFLAGS)  -c $< -o $@

# ===============================
# GUI Version
# ===============================
$(GUI_TARGET): $(GUI_OBJS)
	$(CC) $(GUI_OBJS) -o $(GUI_TARGET) $(LDFLAGS) $(GTK_FLAGS)

GUI_gestion/%.o: GUI_gestion/%.c
	$(CC) $(GUI_CFLAGS) -c $< -o $@

# Note: functions are compiled with CMD_CFLAGS for consistency
# If GUI-specific compilation is needed for functions, add a separate rule
functions/%.o: functions/%.c
	$(CC) $(CMD_CFLAGS) -c $< -o $@

# ===============================
# Nettoyage
# ===============================
clean:
	rm -f $(CMD_TARGET) $(GUI_TARGET) $(CMD_OBJS) $(GUI_OBJS)

# Execution
run-cmd: $(CMD_TARGET)
	./$(CMD_TARGET)

run-gui: $(GUI_TARGET)
	./$(GUI_TARGET)
	
# ===============================
# Aide
# ===============================
help:
	@echo "Cibles disponibles:"
	@echo "  all       - Compile les deux versions (cmd et gui)"
	@echo "  cmd       - Compile uniquement la version console"
	@echo "  gui       - Compile uniquement la version GUI"
	@echo "  clean     - Supprime les exécutables, fichiers objets et dépendances"
	@echo "  run-cmd   - Exécute la version console"
	@echo "  run-gui   - Exécute la version GUI"
	@echo "  help      - Affiche cette aide"
