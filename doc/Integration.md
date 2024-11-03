## Using ruri as container implementation:
Here is a simple example, to build file command in an alpine container with ruri:
```sh
# Download and unpack rootfs
git clone https://github.com/moe-hacker/rootfstool
rootfstool/rootfstool d -d alpine -v edge
mkdir alpine
sudo tar -xvf rootfs.tar.xz -C alpine
# Get ruri
wget https://github.com/Moe-hacker/ruri/raw/refs/heads/main/getruri.sh
bash getruri.sh -s
# Copy build script
sudo cp build.sh alpine/build.sh
sudo chmod +x alpine/build.sh
# Run container
sudo ./ruri ./alpine /bin/sh /build.sh
```

build.sh:      
```sh
# Fix DNS problem
rm /etc/resolv.conf
echo nameserver 1.1.1.1 > /etc/resolv.conf
# Add testing source
echo https://dl-cdn.alpinelinux.org/alpine/edge/testing >> /etc/apk/repositories
apk add wget make clang git xz-dev libintl libbsd-static libsemanage-dev libselinux-utils libselinux-static xz-libs zlib zlib-static libselinux-dev linux-headers libssl3 libbsd libbsd-dev gettext-libs gettext-static gettext-dev gettext python3 build-base openssl-misc openssl-libs-static openssl zlib-dev xz-dev openssl-dev automake libtool bison flex gettext autoconf gettext sqlite sqlite-dev pcre-dev wget texinfo docbook-xsl libxslt docbook2x musl-dev gettext gettext-asprintf gettext-dbg gettext-dev gettext-doc gettext-envsubst gettext-lang gettext-libs gettext-static
apk add upx
mkdir output

# build file
git clone https://github.com/file/file
cd file
autoreconf -vif
./configure LDFLAGS="-static -Wl,--gc-sections -ffunction-sections -fdata-sections" --disable-nss --enable-static --disable-shared --disable-liblastlog2
make -j8 LDFLAGS="-all-static -Wl,--gc-sections -ffunction-sections -fdata-sections"
strip src/file
cp src/file ../output/file-static
cp magic/magic.mgc ../output/
cc -static -o file ../file.c
strip file
upx file
cp file ../output/file
cp COPYING ../output/LICENSE-file
cd ..
cd output
tar -cvf ../$(uname -m).tar .
exit 0
```
## Using ruri config file:
If you have a container in `/test`,      
Use `ruri -D -o test.conf /test` to dump the config into test.conf      
You can also add other options like `ruri -D -o test.conf -d cap_chmod -k cap_sys_admin -w -u /test /bin/sh`      
So next time, just use `ruri -c /path/to/test.conf` to run the container.      
## integrate with source:
If your project supports, you can also edit the main.c, remove `main()` function and use ruri as a lib. But make sure that you know how main.c works, especially how CONTAINER struct works.       