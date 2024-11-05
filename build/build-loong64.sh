sudo apt install qemu-user-static pkg-config libglib2.0-dev qemu-system-misc python3-tomli binfmt-support debootstrap ninja-build
git clone https://github.com/qemu/qemu.git
cd qemu
./configure --static --disable-system --target-list=loongarch64-linux-user
make -j$(nproc)
sudo cp build/loongarch64-linux-user/qemu-loongarch64 /usr/bin/qemu-loongarch64-static
sudo cp build/qemu-loongarch64 /usr/bin/qemu-loongarch64-static
sudo cp qemu-loongarch64 /usr/bin/qemu-loongarch64-static
cd ..
sudo debootstrap --foreign --arch=loong64 --variant=buildd --include=debian-ports-archive-keyring --verbose --components=main --resolve-deps --extra-suites=unreleased unstable ./debian http://ftp.ports.debian.org/debian-ports
sudo cp /usr/bin/qemu-loongarch64-static debian/usr/bin/
sudo chroot ./debian /debootstrap/debootstrap --second-stage
cat <<EOF >> ./debian/build.sh
rm /etc/resolv.conf
echo nameserver 1.1.1.1 > /etc/resolv.conf
apt update
apt install -y wget make clang git libseccomp-dev libcap-dev libc-dev binutils
git clone https://github.com/moe-hacker/ruri
cd ruri
./configure -s
make
tar -cvf ../loong64.tar ./ruri ./LICENSE
EOF
sudo chmod +x ./debian/build.sh
sudo ./ruri/ruri -a loong64 -q qemu-loongarch64-static ./debian /bin/sh /build.sh
cp ./debian/loong64.tar ../loongarch64.tar