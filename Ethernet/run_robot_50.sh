#!/bin/sh

iterations=0
for i in {1..50}
do
	robot .
    echo -e "Iterations: $i"
done