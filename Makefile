SOURCES = ims.cpp Tank.cpp Stats.cpp WaterSupply.cpp Irrigation.cpp Weather.cpp
all:
	g++ -std=c++17 $(SOURCES) -o ims
clean:
	-rm ims
