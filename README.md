# Lattice Gas Automata HPP Model

The purpose of this project is to learn CUDA and SFML \

https://www.youtube.com/watch?v=r5hwWegJK1E&ab_channel=gersondemo
[![Demo](https://i.imgur.com/3b7JDCe.png)](https://www.youtube.com/watch?v=r5hwWegJK1E&ab_channel=gersondemo)

## Description

The Hardy–Pomeau–Pazzis (HPP) model is a fundamental lattice gas automaton for the simulation of gases and liquids. It was a precursor to the lattice Boltzmann methods. From lattice gas automata, it is possible to derive the macroscopic Navier-Stokes equations. Interest in lattice gas automaton methods levelled off in the early 1990s, due to rising interest in the lattice Boltzmann methods. \

Reference: https://www.wikiwand.com/en/HPP_model


## Experiments

### Experiment 1

### Experiment 2


## Requirements

- Cuda Toolkit 12.x
- SFML 2.5.x
- Patience
- Windows 11 (Optional)

## How to run
Go to the root folder, and run this: \
``` nvcc -I ./src -I ./include --library-path=./lib --library=sfml-graphics --library=sfml-window --library=sfml-system -o bin/test ./src/main.cu ``` \
Press **space** to start the sim


## License
