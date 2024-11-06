apt update
apt install -y sudo
sudo apt install -y git wget
yes | sudo apt install --no-install-recommends -y curl xz-utils \
  make \
  clang \
  libseccomp-dev \
  libcap-dev \
  libc6-dev \
  binutils
# Build ruri
git clone https://github.com/moe-hacker/ruri
cd ruri
cc -Wl,--gc-sections -static src/*.c src/easteregg/*.c -o ruri -lcap -lseccomp -lpthread
cd ..
sudo apt install qemu-user-static pkg-config libglib2.0-dev qemu-system-misc python3-tomli binfmt-support debootstrap ninja-build
# Build qemu-loongarch64
git clone https://github.com/qemu/qemu.git
cd qemu
./configure --static --disable-system --target-list=loongarch64-linux-user
make -j$(nproc)
sudo cp build/loongarch64-linux-user/qemu-loongarch64 /usr/bin/qemu-loongarch64-static
sudo cp build/qemu-loongarch64 /usr/bin/qemu-loongarch64-static
sudo cp qemu-loongarch64 /usr/bin/qemu-loongarch64-static
cd ..
