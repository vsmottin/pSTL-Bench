# Use a base image with Spack installed
FROM spack/ubuntu-jammy

# Install essential tools and libraries
RUN apt-get update && apt-get upgrade -y
RUN apt install -y build-essential cmake git wget curl

# Install GCC-12
RUN apt install -y gcc-12 g++-12
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-12 100

# Install and load Intel OneAPI
RUN wget -O- https://apt.repos.intel.com/intel-gpg-keys/GPG-PUB-KEY-INTEL-SW-PRODUCTS.PUB | gpg --dearmor |  tee /usr/share/keyrings/oneapi-archive-keyring.gpg > /dev/null
RUN echo "deb [signed-by=/usr/share/keyrings/oneapi-archive-keyring.gpg] https://apt.repos.intel.com/oneapi all main" |  tee /etc/apt/sources.list.d/oneAPI.list
RUN apt update -y
RUN apt install -y intel-basekit

# Install and load NVIDIA HPC SDK
RUN curl https://developer.download.nvidia.com/hpc-sdk/ubuntu/DEB-GPG-KEY-NVIDIA-HPC-SDK | gpg --dearmor -o /usr/share/keyrings/nvidia-hpcsdk-archive-keyring.gpg
RUN echo 'deb [signed-by=/usr/share/keyrings/nvidia-hpcsdk-archive-keyring.gpg] https://developer.download.nvidia.com/hpc-sdk/ubuntu/amd64 /' | tee /etc/apt/sources.list.d/nvhpc.list
RUN apt-get update -y
RUN apt install -y nvhpc-24-5

# Install HPX
RUN spack install hpx

# Additional libraries
RUN apt install -y libnuma-dev libbenchmark-dev

# Set the entrypoint to bash to allow running commands in the container
ENTRYPOINT [ "/bin/bash", "-l" ]
