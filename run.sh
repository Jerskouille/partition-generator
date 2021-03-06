#!/bin/bash

echo 'In run'

handler() {
    pkill coffee
    pkill node
    pkill watch >/dev/null 2>&1
}

make
coffee ./server.coffee -n &
sleep 2

trap handler SIGINT

while watch -n 1 -d -g '\ls -l index.html server.coffee Makefile `find src/ -type f`' | cat >/dev/null; do
    pkill coffee
    pkill node
    make
    coffee ./server.coffee -n &
    sleep 2
    echo
done

