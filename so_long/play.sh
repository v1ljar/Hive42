#!/bin/bash

for map in ./maps/*.ber; do \
	echo "Inimese maja: $map"
	./so_long $map
done
