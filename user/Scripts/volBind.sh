#!/bin/bash
# Makes a file that is read by dwmbar to know when to show volume information

echo "1" > /tmp/dwmbar_volume

sleep 10

echo "" > /tmp/dwmbar_volume
