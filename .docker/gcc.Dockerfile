# Use a base image with Spack installed
FROM spack/ubuntu-jammy

# Install essential tools and libraries
RUN apt-get update && apt-get upgrade -y
RUN apt install -y build-essential cmake git wget curl

# Slow things first
# Install HPX
RUN spack install hpx

# Install GCC-11
RUN apt install -y gcc-11 g++-11
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 100
RUN update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-11 100

# Install TBB
RUN apt install -y libtbb-dev

# Additional libraries
RUN apt install -y libnuma-dev libbenchmark-dev

# Set the entrypoint to bash to allow running commands in the container
ENTRYPOINT [ "/bin/bash", "-l" ]
