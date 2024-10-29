rm /etc/resolv.conf
echo nameserver 1.1.1.1 > /etc/resolv.conf
echo https://dl-cdn.alpinelinux.org/alpine/edge/testing >> /etc/apk/repositories
apk add wget make clang git  libseccomp-dev libseccomp-static libcap-static libcap-dev xz-dev libintl libbsd-static libsemanage-dev libselinux-utils libselinux-static xz-libs zlib zlib-static libselinux-dev linux-headers libssl3 libbsd libbsd-dev gettext-libs gettext-static gettext-dev gettext python3 build-base openssl-misc openssl-libs-static openssl zlib-dev xz-dev openssl-dev automake libtool bison flex gettext autoconf gettext sqlite sqlite-dev pcre-dev wget texinfo docbook-xsl libxslt docbook2x musl-dev gettext gettext-asprintf gettext-dbg gettext-dev gettext-doc gettext-envsubst gettext-lang gettext-libs gettext-static
apk add upx
mkdir output

# OK
git clone https://github.com/moe-hacker/ruri
cd ruri
./configure -s
make
strip ruri
upx ruri
cp ruri ../output/ruri
cp LICENSE ../output/LICENSE
cd ..
cd output
tar -cvf ../$(uname -m).tar .
exit 0
