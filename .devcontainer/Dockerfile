FROM mcr.microsoft.com/devcontainers/base:jammy

# add CA certificates so docker can download packages and vscode can download extensions
COPY ./zscaler-root-ca.crt /usr/local/share/ca-certificates/
ENV NODE_EXTRA_CA_CERTS=/usr/local/share/ca-certificates/zscaler-root-ca.crt
RUN chmod 644 /usr/local/share/ca-certificates/*.crt && update-ca-certificates

#install the required Linux packages
RUN apt-get update && \
    apt-get install -y \
    wget \
    software-properties-common \
    git \
    python3-pip \
    python3-venv \
    python-is-python3 \
    python3-tk \
    black \
    cmake \
    ninja-build \
    srecord \
    clang-format \
    clang-tidy \
    build-essential \
    libncursesw5 
RUN apt-get clean


# Install a specific version of CMAKE
ARG REINSTALL_CMAKE_VERSION_FROM_SOURCE="3.26.4"
COPY ./reinstall-cmake.sh /tmp/
RUN if [ "${REINSTALL_CMAKE_VERSION_FROM_SOURCE}" != "none" ]; then \
    chmod +x /tmp/reinstall-cmake.sh && /tmp/reinstall-cmake.sh ${REINSTALL_CMAKE_VERSION_FROM_SOURCE}; \
    fi \
    && rm -f /tmp/reinstall-cmake.sh

# Download arm-gnu toolchain
ARG ARM_TOOLCHAIN_VERSION=12.2.rel1
RUN \
    # python3.8 required to run GDB in linux
    sudo add-apt-repository ppa:deadsnakes/ppa && \
    sudo apt install -y python3.8 && \
    wget -O arm-gnu-toolchain.tar.xz -P /tmp \ 
    https://armkeil.blob.core.windows.net/developer/Files/downloads/gnu/${ARM_TOOLCHAIN_VERSION}/binrel/arm-gnu-toolchain-${ARM_TOOLCHAIN_VERSION}-x86_64-arm-none-eabi.tar.xz \
    && mkdir /opt/gcc-arm-none-eabi \
    && tar xf arm-gnu-toolchain.tar.xz --strip-components=1 -C /opt/gcc-arm-none-eabi \
    && rm -rf /tmp/arm-gnu-toolchain.tar.xz

# Add toolchain to path
ENV PATH="$PATH:/opt/gcc-arm-none-eabi/bin"
