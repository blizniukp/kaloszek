#!/bin/bash

PREPARE_SMALL_ICONS=N
PREPARE_BIG_ICONS=N
PREPARE_WIND_ICONS=N
PREPARE_INFO_ICONS=N
PREPARE_INFO_SMALL_ICONS=Y

SMALL_SIZE_H=50
BIG_SIZE_H=100
WIND_DIR_SIZE_H=50
INFO_SIZE_H=35
INFO_SMALL_SIZE_H=19

#PATH_ICONS_SRC="$PWD/weathericons_src" ## pierwszy zestaw ikon
PATH_ICONS_SRC="$PWD/accuweather2_src"  ## drugi zestaw ikon
PATH_ICONS_WIND_SRC="$PWD/winddirection_src"  ## ikony przedstawiające kierunek wiatru
PATH_ICONS_INFO_SRC="$PWD/info_src"  ## ikony przedstawiające symbole informacyjne
PATH_ICONS_INFO_SMALL_SRC="$PWD/info_small_src"  ## ikony przedstawiające symbole informacyjne (ostatni rząd)

PATH_ICONS_SMALL="$PWD/icons_small"
PATH_ICONS_BIG="$PWD/icons_big"
PATH_ICONS_INFO="$PWD/icons_info"
PATH_ICONS_INFO_SMALL="$PWD/icons_info_small"

if [ "$PREPARE_SMALL_ICONS" == "Y" ]; then
	rm $PATH_ICONS_SMALL/*
fi

if [ "$PREPARE_BIG_ICONS" == "Y" ]; then
	rm $PATH_ICONS_BIG/*
fi
if [ "$PREPARE_INFO_ICONS" == "Y" ]; then
	rm $PATH_ICONS_INFO/*
fi
if [ "$PREPARE_INFO_SMALL_ICONS" == "Y" ]; then
	rm $PATH_ICONS_INFO_SMALL/*
fi

# Przygotowanie ikon przedstawiających pogodę (mały i duzy rozmiar)
for fullfile in $PATH_ICONS_SRC/*.svg; do
	filename=$(basename -- "$fullfile")
	extension="${filename##*.}"
	filename="${filename%.*}"
    	echo "fullfile: $fullfile filename: $filename extension: $extension"

	if [ "$PREPARE_SMALL_ICONS" == "Y" ]; then
		inkscape -z -e "$PATH_ICONS_SMALL/$filename.png" -h $SMALL_SIZE_H $fullfile
		convert "$PATH_ICONS_SMALL/$filename.png" -threshold 100% "$PATH_ICONS_SMALL/bw_$filename.png"
	fi

	if [ "$PREPARE_BIG_ICONS" == "Y" ]; then
		inkscape -z -e "$PATH_ICONS_BIG/$filename.png" -h $BIG_SIZE_H $fullfile
		convert "$PATH_ICONS_BIG/$filename.png" -threshold 100% "$PATH_ICONS_BIG/bw_$filename.png"
	fi
done

if [ "$PREPARE_WIND_ICONS" == "Y" ]; then
	# Przygotowanie ikon przedstawiających kierunek wiatru
	for fullfile in $PATH_ICONS_WIND_SRC/*.svg; do
		filename=$(basename -- "$fullfile")
		extension="${filename##*.}"
		filename="${filename%.*}"
	    	echo "fullfile: $fullfile filename: $filename extension: $extension"
		inkscape -z -e "$PATH_ICONS_SMALL/$filename.png" -h $WIND_DIR_SIZE_H $fullfile
		convert "$PATH_ICONS_SMALL/$filename.png" -threshold 100% "$PATH_ICONS_SMALL/bw_$filename.png"
	done
fi

if [ "$PREPARE_INFO_ICONS" == "Y" ]; then
	# Przygotowanie ikon przedstawiających symbole informacyjne
	for fullfile in $PATH_ICONS_INFO_SRC/*.svg; do
		filename=$(basename -- "$fullfile")
		extension="${filename##*.}"
		filename="${filename%.*}"
	    	echo "fullfile: $fullfile filename: $filename extension: $extension"
		inkscape -z -e "$PATH_ICONS_INFO/$filename.png" -h $INFO_SIZE_H $fullfile
		convert "$PATH_ICONS_INFO/$filename.png" -threshold 100% "$PATH_ICONS_INFO/bw_$filename.png"
	done
fi

if [ "$PREPARE_INFO_SMALL_ICONS" == "Y" ]; then
	# Przygotowanie ikon przedstawiających symbole informacyjne (ostatni rząd)
	for fullfile in $PATH_ICONS_INFO_SMALL_SRC/*.svg; do
		filename=$(basename -- "$fullfile")
		extension="${filename##*.}"
		filename="${filename%.*}"
	    	echo "fullfile: $fullfile filename: $filename extension: $extension"
		inkscape -z -e "$PATH_ICONS_INFO_SMALL/$filename.png" -h $INFO_SMALL_SIZE_H $fullfile
		convert "$PATH_ICONS_INFO_SMALL/$filename.png" -threshold 100% "$PATH_ICONS_INFO_SMALL/bw_$filename.png"
	done
	for fullfile in $PATH_ICONS_INFO_SMALL_SRC/*.png; do
		filename=$(basename -- "$fullfile")
		extension="${filename##*.}"
		filename="${filename%.*}"
	    	echo "fullfile: $fullfile filename: $filename extension: $extension"
		inkscape -z -e "$PATH_ICONS_INFO_SMALL/$filename.png" -h $INFO_SMALL_SIZE_H $fullfile
		convert "$PATH_ICONS_INFO_SMALL/$filename.png" -threshold 100% "$PATH_ICONS_INFO_SMALL/bw_$filename.png"
	done
fi
