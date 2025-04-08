#!/bin/bash

set -e

git clone https://github.com/ocornut/imgui ./external/imgui --depth 1
git clone https://github.com/mruby/mruby ./external/mruby --depth 1

cd external/mruby
make -j4