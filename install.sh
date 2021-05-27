#!/bin/bash

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
	sudo apt update
	sudo apt-get install xorg-dev
	sudo apt-get install libsdl2-dev
	sudo apt-get install libsdl2-ttf-dev
	sudo apt-get install libsdl2-image-dev
	sudo apt-get install libsdl2-mixer-dev
elif [[ "$OSTYPE" == "darwin"* ]]; then
	brew update
	brew install sdl2
	brew install sdl2_ttf
	brew install sdl2_image
	brew install sdl2_mixer
else
	echo "Other than Linux and OSX are not supported"
fi
