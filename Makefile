CC ?= gcc

APP_NAME = lab1
OBJ_FILES = lab1.o

LIBS = .

all: $(APP_NAME)

$(APP_NAME) : $(OBJ_FILES)
	$(CC) $^ -o $@ $(LIBS) -lpthread


%.o: %.c
	$(CC) -o $@ -c $^ -g -lpthread

clean:
	rm *.o $(APP_NAME)



fresh:
	make clean
	make all
