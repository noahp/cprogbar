FROM ubuntu:focal

# This makes apt-get work without interactive shell
ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    binutils-arm-none-eabi \
    build-essential \
    clang-10 \
    clang-format-10 \
    gcc-10 \
    gcc-10-multilib \
    gcc-arm-none-eabi \
    git

# get user id from build arg, so we can have read/write access to directories
# mounted inside the container. only the UID is necessary, UNAME just for
# cosmetics
ARG UID=1010
ARG UNAME=builder

RUN useradd --uid $UID --create-home --user-group ${UNAME} && \
    echo "${UNAME}:${UNAME}" | chpasswd && adduser ${UNAME} sudo

USER ${UNAME}
