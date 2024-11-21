BASE_URL="https://dl-cdn.alpinelinux.org/alpine/edge/releases/riscv64"
ROOTFS_URL=$(curl -s -L "$BASE_URL/latest-releases.yaml" | grep "alpine-minirootfs" | grep "riscv64.tar.gz" | head -n 1 | awk '{print $2}')
FULL_URL="$BASE_URL/$ROOTFS_URL"
wget "$FULL_URL"
mkdir riscv64
tar -xvf "$ROOTFS_URL" -C riscv64
sudo apt install -y qemu-user-static
sudo cp build.sh riscv64/build.sh
sudo chmod +x riscv64/build.sh
sudo ./ruri/ruri -a riscv64 -q /usr/bin/qemu-riscv64-static ./riscv64 /bin/sh /build.sh
mv riscv64/*-noupx.tar ../riscv64-noupx.tar
cp riscv64/*.tar ../riscv64.tar
