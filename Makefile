
OBJS=main.o
LDFLAGS=-lGL -lGLU -lglut

TARGET=test
RM=rm -f

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)


clean:
	$(RM) $(TARGET) $(OBJS)


