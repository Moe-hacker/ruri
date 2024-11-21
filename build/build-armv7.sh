BASE_URL="https://dl-cdn.alpinelinux.org/alpine/edge/releases/armv7"
ROOTFS_URL=$(curl -s -L "$BASE_URL/latest-releases.yaml" | grep "alpine-minirootfs" | grep "armv7.tar.gz" | head -n 1 | awk '{print $2}')
FULL_URL="$BASE_URL/$ROOTFS_URL"
wget "$FULL_URL"
mkdir armv7
tar -xvf "$ROOTFS_URL" -C armv7
sudo apt install -y qemu-user-static
sudo cp build.sh armv7/build.sh
sudo chmod +x armv7/build.sh
sudo ./ruri/ruri -a armv7 -q /usr/bin/qemu-arm-static ./armv7 /bin/sh /build.sh
mv armv7/*-noupx.tar ../armv7-noupx.tar
cp armv7/*.tar ../armv7.tar
