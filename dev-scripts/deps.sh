#! /bin/sh

echo "Installing deps"

SCRIPT_LOCATION=$(dirname $0)

rosdep update
sudo apt update
rosdep install --from-paths $SCRIPT_LOCATION/../src --ignore-src -r -y

echo "Script has finished executing"
