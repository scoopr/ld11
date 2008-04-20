

# LNX=1
WIN=1
# OSX=1

# Sane defaults
EXE=
RM=rm -f



ifdef WIN
	LDFLAGS+= -lopengl32 -Lwin -lglut32
	CFLAGS+= -Iwin
	EXE=.exe
	RM=del /q
	CC=gcc
endif

ifdef LNX
	LDFLAGS+=-lGL -lGLU -lglut
endif

ifdef OSX
  ## TODO:
  LDFLAGS+=-framework OpenGL -framework GLUT
endif


OBJS=main.o

TARGET=test$(EXE)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)


clean:
	$(RM) $(TARGET) $(OBJS)


