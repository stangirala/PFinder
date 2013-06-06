
OPENCV_FLAGS = `pkg-config --cflags --libs opencv`

CXXFLAGS = -Wall -ansi -pedantic -g $(OPENCV_FLAGS)


build: split_histogram

split_histogram: split_histogram.cpp
	$(CXX) $(CXXFLAGS) -o split_histogram split_histogram.cpp 

clean:
	rm -f split_histogram
