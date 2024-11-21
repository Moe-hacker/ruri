BASE_URL="https://dl-cdn.alpinelinux.org/alpine/edge/releases/s390x"
ROOTFS_URL=$(curl -s -L "$BASE_URL/latest-releases.yaml" | grep "alpine-minirootfs" | grep "s390x.tar.gz" | head -n 1 | awk '{print $2}')
FULL_URL="$BASE_URL/$ROOTFS_URL"
wget "$FULL_URL"
mkdir s390x
tar -xvf "$ROOTFS_URL" -C s390x
sudo apt install -y qemu-user-static
sudo cp build.sh s390x/build.sh
sudo chmod +x s390x/build.sh
sudo ./ruri/ruri -a s390x -q /usr/bin/qemu-s390x-static ./s390x /bin/sh /build.sh
mv s390x/*-noupx.tar ../s390x-noupx.tar
cp s390x/*.tar ../s390x.tar
