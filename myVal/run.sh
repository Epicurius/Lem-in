#!/usr/bin/env bash
./generator --big-superposition | ../lem-in -info > run.output
./validator < run.output
rm run.output
