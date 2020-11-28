SOURCES = ims.cpp Tank.cpp Stats.cpp
all:
	g++ -std=c++17 $(SOURCES) -o ims
clean:
	-rm ims
