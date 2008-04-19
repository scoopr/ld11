
OBJS=main.o
LDFLAGS=-lGL -lGLU -lglut

TARGET=test


$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)



