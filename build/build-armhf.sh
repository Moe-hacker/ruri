BASE_URL="https://dl-cdn.alpinelinux.org/alpine/edge/releases/armhf"
ROOTFS_URL=$(curl -s -L "$BASE_URL/latest-releases.yaml" | grep "alpine-minirootfs" | grep "armhf.tar.gz" | head -n 1 | awk '{print $2}')
FULL_URL="$BASE_URL/$ROOTFS_URL"
wget "$FULL_URL"
mkdir armhf
tar -xvf "$ROOTFS_URL" -C armhf
sudo apt install -y qemu-user-static
sudo cp build.sh armhf/build.sh
sudo chmod +x armhf/build.sh
sudo ./ruri/ruri -a armhf -q /usr/bin/qemu-arm-static ./armhf /bin/sh /build.sh
mv armhf/*-noupx.tar ../armhf-noupx.tar
cp armhf/*.tar ../armhf.tar
