#!/bin/bash

rm ./levelEditor

if gcc -Wall -pedantic -o levelEditor main.c dependencies/cJSON.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11; then
  echo compiled
else
  exit $?
fi

if test "$1" != check ; then
  ./levelEditor
fi
