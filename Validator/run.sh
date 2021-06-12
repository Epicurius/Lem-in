#!/usr/bin/env bash
./test/generator --big-superposition | ../lem-in -info > run.output
./validator < run.output
rm run.output
