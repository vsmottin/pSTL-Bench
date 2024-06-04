# Use a base image with Spack installed
FROM spack/ubuntu-jammy

# Install essential tools and libraries
RUN apt-get update && apt-get upgrade -y
RUN apt install -y build-essential cmake git wget curl

# Install GCC-12
RUN apt install -y gcc-12 g++-12
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-12 100

# Install TBB
RUN apt install -y libtbb-dev

# Install HPX
# RUN spack install hpx

# Additional libraries
RUN apt install -y libnuma-dev libbenchmark-dev

# Set the entrypoint to bash to allow running commands in the container
ENTRYPOINT [ "/bin/bash", "-l" ]
