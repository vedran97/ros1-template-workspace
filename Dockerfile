FROM ros:noetic

ARG USERNAME=vedant
ARG USER_UID=1000
ARG USER_GID=$USER_UID
ARG WORKSPACE_PATH=/workspaces/ros1-template-workspace

COPY . /install/

RUN export DEBIAN_FRONTEND=noninteractive &&\
    /install/scripts/create-user.bash $USERNAME $USER_UID $USER_GID &&\
    /install/scripts/setup-ros-dev-environment.bash $USERNAME $WORKSPACE_PATH &&\
    rm -rf /install-resources &&\
    rm -rf /var/lib/apt/lists/*

USER $USERNAME

ENV SHELL /bin/bash