SOURCES = ims.cpp
all:
	g++ $(SOURCES) -o ims
clean:
	-rm ims
