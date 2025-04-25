# 编译

```sh
git clone https://github.com/Moe-hacker/ruri
cd ruri
aclocal
autoconf
./configure --enable-static
make
sudo cp ruri /usr/bin/ruri
```

::: info Dependency
libcap, libseccomp, libpthread.
:::

::: danger
测试脚本的一部分必须使用 `sudo` 运行，不要在您的设备上运行 `make test`！
:::

## 编译选项

```sh
  --enable-coreonly       Compile core only           仅编译核心
  --disable-libcap        Disable libcap support      禁用 libcap 支持
  --disable-libseccomp    Disable libseccomp support  禁用 libseccomp 支持
  --disable-rurienv       Disable .rurienv support    禁用 .rurienv 支持
  --enable-static         Enable static build         启用静态编译
  --enable-debug          Enable debug log            调试
  --enable-dev            Enable dev build            开发
```

::: tip
注意：`--enable-coreonly` 将自动启用 `--disable-libseccomp --disable-libcap --disable-rurienv`
:::

## 使用 CMake 编译

```sh
git clone https://github.com/Moe-hacker/ruri
cd ruri
cmake .
make
make install
```

## CMake 中的编译选项

```sh
  -DBUILD_LIB=on             Compile to shared library
  -DDISABLE_LIBCAP=on        Disable libcap support
  -DDISABLE_LIBSECCOMP=on    Disable libseccomp support
  -DDISABLE_RURIENV=on       Disable .rurienv support
  -DENABLE_STATIC=on         Enable static build
  -DENABLE_DEBUG=on          Enable debug log
```

::: tip

- -DENABLE_DEBUG=on 等效于传统的编译选项 --enable-dev 加上 --enable-debug
- 当 DISABLE_RURIENV 和 DISABLE_LIBSECCOMP 和 DISABLE_LIBCAP 同时启用时，它等效于传统的编译过程中的 --enable-coreonly
  :::

## 配置完成时 CMake 中的其他目标

```sh
  format      Run clang-format steps
  strip       Run strip steps
  tidy        Run clang-tidy steps
```
