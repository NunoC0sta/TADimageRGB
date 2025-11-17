# Nome do executável
EXEC = analiseIsEquals

# Compilador e flags
CC = gcc
CFLAGS = -Wall -O2

# Arquivos fonte
SRCS = analiseIsEquals.c instrumentation.c imageRGB.c

# Arquivos objeto
OBJS = $(SRCS:.c=.o)

# Regra padrão
all: $(EXEC)

# Compilar o executável
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

# Compilar cada .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpar arquivos compilados
clean:
	rm -f $(OBJS) $(EXEC)
