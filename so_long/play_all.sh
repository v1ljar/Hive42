#!/bin/bash

for map in ./maps/*.ber; do
    echo "Playing map: $map"
    ./so_long $map
done