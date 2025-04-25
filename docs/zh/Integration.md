# 快速开始

```bash
# 下载并解压rootfs
bash -c ". <(curl -sL https://get.ruri.zip/rurima) -s"
./rurima lxc pull -o alpine -v edge -s ./alpine

# 获取ruri (rurima 已完整内置了ruri，事实上只需要一个 rurima 即可)
bash -c ". <(curl -sL https://get.ruri.zip/ruri) -s"

# 运行容器
sudo ./ruri ./alpine
```

## 示例：使用 ruri 构建一个 alpine 容器中的 file 命令

```bash
# 下载并解压rootfs
bash -c ". <(curl -sL https://get.ruri.zip/rurima) -s"
./rurima lxc pull -o alpine -v edge -s ./alpine

# 获取ruri
bash -c ". <(curl -sL https://get.ruri.zip/ruri) -s"

# 复制构建脚本
sudo cp build.sh alpine/build.sh
sudo chmod +x alpine/build.sh

# 运行容器
sudo ./ruri ./alpine /bin/sh /build.sh
```

::: code-group

```sh [build.sh]
# 修复DNS问题
rm /etc/resolv.conf
echo nameserver 1.1.1.1 > /etc/resolv.conf

# 添加测试源
echo https://dl-cdn.alpinelinux.org/alpine/edge/testing >> /etc/apk/repositories
apk add wget make clang git xz-dev libintl libbsd-static libsemanage-dev libselinux-utils libselinux-static xz-libs zlib zlib-static libselinux-dev linux-headers libssl3 libbsd libbsd-dev gettext-libs gettext-static gettext-dev gettext python3 build-base openssl-misc openssl-libs-static openssl zlib-dev xz-dev openssl-dev automake libtool bison flex gettext autoconf gettext sqlite sqlite-dev pcre-dev wget texinfo docbook-xsl libxslt docbook2x musl-dev gettext gettext-asprintf gettext-dbg gettext-dev gettext-doc gettext-envsubst gettext-lang gettext-libs gettext-static
apk add upx
mkdir output

# 构建file
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

:::

## 使用 ruri 配置文件

如果你有一个容器在`/test`，
使用`ruri -D -o test.conf /test`将配置文件转储到 test.conf
你也可以添加其他选项，比如`ruri -D -o test.conf -d cap_chmod -k cap_sys_admin -w -u /test /bin/sh`
下次，只需使用`ruri -c /path/to/test.conf`运行容器。

## 与源码集成

main()已经被替换为 ruri，ruri 中的每个函数都有`ruri*`或`nekofeng*`前缀，所以你不需要担心符号冲突。
如果你的项目支持，你可以删除`main()`函数并使用 ruri 作为库。但请确保你了解 ruri.c 的工作原理，特别是 RURI_CONTAINER 结构的工作原理。
一个例子是[rurima](https://github.com/Moe-hacker/rurima)，我使 ruri 成为它的子命令。所以`rurima r`与`ruri`有相同的效果。
