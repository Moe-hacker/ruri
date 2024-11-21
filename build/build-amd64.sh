git clone https://github.com/moe-hacker/rootfstool
rootfstool/rootfstool d -d alpine -v edge
mkdir alpine
sudo tar -xvf rootfs.tar.xz -C alpine
sudo cp build.sh alpine/build.sh
sudo chmod +x alpine/build.sh
sudo ./ruri/ruri ./alpine /bin/sh /build.sh
echo $(pwd)/x86_64.tar
mv alpine/*-noupx.tar ./x86_64-noupx.tar
mv alpine/*.tar ./x86_64.tar
cp *.tar ../
