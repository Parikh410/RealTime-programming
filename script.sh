#!/bin/bash

gcc producer.c -o producer -lrt
gcc consumer.c -o consumer
./producer
./consumer