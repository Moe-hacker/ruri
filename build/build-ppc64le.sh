BASE_URL="https://dl-cdn.alpinelinux.org/alpine/edge/releases/ppc64le"
ROOTFS_URL=$(curl -s -L "$BASE_URL/latest-releases.yaml" | grep "alpine-minirootfs" | grep "ppc64le.tar.gz" | head -n 1 | awk '{print $2}')
FULL_URL="$BASE_URL/$ROOTFS_URL"
wget "$FULL_URL"
mkdir ppc64le
tar -xvf "$ROOTFS_URL" -C ppc64le
sudo apt install -y qemu-user-static
sudo cp build.sh ppc64le/build.sh
sudo chmod +x ppc64le/build.sh
sudo ./ruri/ruri -a ppc64le -q /usr/bin/qemu-ppc64le-static ./ppc64le /bin/sh /build.sh
mv ppc64le/*-noupx.tar ../ppc64le-noupx.tar
cp ppc64le/*.tar ../ppc64le.tar
