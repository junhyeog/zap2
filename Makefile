LDLIBS=
TARGET=zap

all: $(TARGET)

$(TARGET): main.o zap2.o
	gcc $^ $(LOADLIBES) $(LDLIBS) -o $@

clean:
	rm -f  *.o $(TARGET)