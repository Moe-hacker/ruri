sudo apt install qemu-user-static qemu-system-misc binfmt-support
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
cp ./debian/loong64.tar ../loong64.tar