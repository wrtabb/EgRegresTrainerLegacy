#!/bin/bash

export PATH=$PATH:./bin/$SCRAM_ARCH
export PYTHON27PATH=$PYTHON27PATH:python
export PYTHONPATH=$PYTHONPATH:python
export ROOT_INCLUDE_PATH=$ROOT_INCLUDE_PATH:$PWD/include

python scripts/runEleRegTrainings.py --era 2021Run3 
