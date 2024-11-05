apt update
apt install -y sudo
sudo apt install -y git wget
yes|sudo apt install --no-install-recommends -y curl xz-utils \
              make \
              clang \
              libseccomp-dev \
              libcap-dev \
              libc6-dev \
              binutils 
git clone https://github.com/moe-hacker/rootfstool
rootfstool/rootfstool d -d alpine -v edge
mkdir alpine
sudo tar -xvf rootfs.tar.xz -C alpine
git clone https://github.com/moe-hacker/ruri
cd ruri
cc -Wl,--gc-sections -static src/*.c src/easteregg/*.c -o ruri -lcap -lseccomp -lpthread
cd ..
sudo cp build.sh alpine/build.sh
sudo chmod +x alpine/build.sh
sudo ./ruri/ruri ./alpine /bin/sh /build.sh
cp alpine/$(uname -m).tar ../
bash build-loong64.sh
bash build-riscv64.sh
bash build-arm64.sh
bash build-armhf.sh
bash build-armv7.sh
bash build-x86.sh
bash build-ppc64le.sh
bash build-s390x.sh