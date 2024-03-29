#!/bin/bash

output_dir="valid_test_output"
mkdir -p $output_dir

echo "---------------------Valid Maps-------------------------"
map_dir="./test/valid_maps"

for map in $map_dir/*
do
	echo "./lem-in < $map"
	subdir="$output_dir/$map"
	mkdir -p $subdir
	output="$subdir/output"
	../lem-in < $map > $output
	./validator < $output
done

echo "---------------------Error Maps-------------------------"
map_dir="./test/error_maps"

for map in $map_dir/*
do
	echo "./lem-in -format=ants < $map"
	../lem-in -format=ants < $map
	echo ""
done

echo "---------------------Subject Maps-------------------------"
map_dir="./test/generator_maps"

for map in $map_dir/*
do
	echo "./lem-in < $map"
	subdir="$output_dir/$map"
	mkdir -p $subdir
	output="$subdir/output"
	../lem-in < $map > $output
	./validator < $output
done

echo "---------------------My Maps-------------------------"
map_dir="./test/my_maps"

for map in $map_dir/*
do
	echo "./lem-in < $map"
	subdir="$output_dir/$map"
	mkdir -p $subdir
	output="$subdir/output"
	../lem-in < $map > $output
	./validator < $output
done

rm -rf valid_test_output
