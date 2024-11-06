git clone https://github.com/moe-hacker/rootfstool
rootfstool/rootfstool d -d alpine -v edge
mkdir alpine
sudo tar -xvf rootfs.tar.xz -C alpine
sudo cp build.sh alpine/build.sh
sudo chmod +x alpine/build.sh
sudo ./ruri/ruri ./alpine /bin/sh /build.sh
cp alpine/$(uname -m).tar ../
