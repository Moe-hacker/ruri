BASE_URL="https://dl-cdn.alpinelinux.org/alpine/edge/releases/x86"
ROOTFS_URL=$(curl -s -L "$BASE_URL/latest-releases.yaml" | grep "alpine-minirootfs" | grep "x86.tar.gz" | head -n 1 | awk '{print $2}')
FULL_URL="$BASE_URL/$ROOTFS_URL"
wget "$FULL_URL"
mkdir x86
tar -xvf "$ROOTFS_URL" -C x86
sudo cp build.sh x86/build.sh
sudo chmod +x x86/build.sh
sudo ./ruri/ruri ./x86 /bin/sh /build.sh
mv x86/*-noupx.tar ../i386-noupx.tar
cp x86/*.tar ../i386.tar
