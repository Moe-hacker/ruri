BASE_URL="https://dl-cdn.alpinelinux.org/alpine/edge/releases/aarch64"
ROOTFS_URL=$(curl -s -L "$BASE_URL/latest-releases.yaml" | grep "alpine-minirootfs" | grep "aarch64.tar.gz" | head -n 1 | awk '{print $2}')
FULL_URL="$BASE_URL/$ROOTFS_URL"
wget "$FULL_URL"
mkdir aarch64
tar -xvf "$ROOTFS_URL" -C aarch64
sudo apt install -y qemu-user-static
sudo cp build.sh aarch64/build.sh
sudo chmod +x aarch64/build.sh
sudo ./ruri/ruri -a aarch64 -q /usr/bin/qemu-aarch64-static ./aarch64 /bin/sh /build.sh
mv aarch64/*-noupx.tar ../aarch64-noupx.tar
cp aarch64/*.tar ../aarch64.tar
