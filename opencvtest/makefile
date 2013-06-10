
OPENCV_FLAGS = `pkg-config --cflags --libs opencv`

CXXFLAGS = -Wall -ansi -pedantic -g $(OPENCV_FLAGS)


build: split_histogram

split_histogram: split_histogram.cpp
	$(CXX) $(CXXFLAGS) -o combined_histogram combined_histogram.cpp

clean:
	rm -f combined_histogram

run: clean build
	./combined_histogram ~/Downloads/5fb1c6e6acf63c82892ba015562aacdf.jpg
