.PHONY: r build

r: build
	./build/nowrd

build:
	clear
	cmake . -B build
	make -C build -j12
