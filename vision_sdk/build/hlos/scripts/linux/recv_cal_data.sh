#!/bin/bash

cd /tmp

while [ true ]; do
    name=$(nc -l 2000)
    echo "Writing to ${name}"
    nc -l 2000 > $name
done
