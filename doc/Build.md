# Dependency:
libcap, libseccomp, libpthread.      
# Build:
```
git clone https://github.com/Moe-hacker/ruri
cd ruri
aclocal
autoconf
./configure --enable-static
make
sudo cp ruri /usr/bin/ruri
```
# NOTE:
The test script has a part that must be run with `sudo`, `DO NOT` run `make test` on your devices!!!!      
# Build options:
Note: `--enable-core` will auto enable `--disable-libseccomp --disable-libcap --disable-rurienv`      