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

BASE_URL="https://dl-cdn.alpinelinux.org/alpine/edge/releases/riscv64"
ROOTFS_URL=$(curl -s -L "$BASE_URL/latest-releases.yaml" | grep "alpine-minirootfs"|grep "riscv64.tar.gz"  | head -n 1|awk '{print $2}')
FULL_URL="$BASE_URL/$ROOTFS_URL"
wget "$FULL_URL"
mkdir alpine
tar -xvf "$ROOTFS_URL" -C alpine
git clone https://github.com/moe-hacker/ruri
cd ruri
cc -Wl,--gc-sections -static src/*.c src/easteregg/*.c -o ruri -lcap -lseccomp -lpthread
cd ..
sudo cp build.sh alpine/build.sh
sudo chmod +x alpine/build.sh
sudo ./ruri/ruri ./alpine /bin/sh /build.sh
cp alpine/$(uname -m).tar ../