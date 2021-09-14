#!/usr/bin/env bash
./Validator/test/generator --big-superposition | ./lem-in -info > run.output
./Validator/validator < run.output
rm run.output
