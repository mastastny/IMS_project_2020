SOURCES = ims.cpp Tank.cpp Stats.cpp WaterSupply.cpp Irrigation.cpp Weather.cpp Roof.cpp split.cpp
all:
	g++ -std=c++17 $(SOURCES) -o ims
clear:
	-rm ims
