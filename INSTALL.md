## Installing FFmpreg

1. Type `./configure` to create the configuration. A list of configure
options is printed by running `configure --help`.

    `configure` can be launched from a directory different from the FFmpreg
sources to build the objects out of tree. To do this, use an absolute
path when launching `configure`, e.g. `/ffmpregdir/ffmpreg/configure`.

2. Then type `make` to build FFmpreg. GNU Make 3.81 or later is required.

3. Type `make install` to install all binaries and libraries you built.

NOTICE
------

 - Non system dependencies (e.g. libx264, libvpx) are disabled by default.
