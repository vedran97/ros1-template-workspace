#! /bin/sh

USERNAME=$1
USER_UID=$2
USER_GID=$3

SCRIPT_LOCATION=$(dirname $0)

groupadd --gid $USER_GID $USERNAME
useradd -s /bin/bash --uid $USER_UID --gid $USER_GID -m $USERNAME
apt-get update
apt-get install -y sudo
echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME
chmod 0440 /etc/sudoers.d/$USERNAME
# permissions for executing vs code tasks
chmod u+rwx $SCRIPT_LOCATION/../dev-scripts