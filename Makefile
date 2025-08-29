CC = gcc
CFLAGS = -Wall -Wextra -pedantic
LDFLAGS = -lncurses -lpthread

.PHONY: all run clean docs show_docs pdf show_pdf help

IFLAGS = -Isrc/visual \
				 -Isrc/runtime \
				 -Isrc/semaphore \
				 -Isrc/listener

SRC = src/main.c \
			src/listener/listener.c \
			src/semaphore/semaphore.c \
			src/runtime/runtime.c \
			src/visual/visual.c

TARGET = danca-das-cadeiras

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ $^ $(LDFLAGS)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)

docs:
	doxygen

pdf: docs
	$(MAKE) -C docs/latex

show_docs: docs
	xdg-open "docs/html/index.html"

show_pdf: pdf
	xdg-open "docs/latex/refman.pdf"

help:
	@echo "Comandos disponíveis:"
	@echo "  make all        -> Compila o projeto (ação padrão)."
	@echo "  make run        -> Compila e executa o programa."
	@echo "  make clean      -> Remove o executável e arquivos temporários."
	@echo "  make docs       -> Gera os arquivos base da documentação (HTML e LaTeX)."
	@echo "  make pdf        -> Gera a documentação em PDF (requer LaTeX)."
	@echo "  make show_docs  -> Gera e abre a documentação HTML no navegador."
	@echo "  make show_pdf   -> Gera e abre a documentação em PDF."
	@echo "  make help       -> Mostra esta mensagem de ajuda."
