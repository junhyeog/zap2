LDLIBS=
TARGET=zap2

all: $(TARGET)

$(TARGET): main.o zap2.o
	$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@

clean:
	rm -f  *.o $(TARGET)