<p align=center>
  <a href="https://www.vincent-os.cf/">
    <img alt="Vincent OS" src="https://github.com/Vincent-OS/website/blob/master/img/logo.png">
  </a>
  Vincent OS
</p>

---

## Quick Links
[Website](https://www.vincent-os.cf/) &bull;
[Community Discord](https://discord.gg/YMpAM8qT8E) &bull;

## What is Vincent OS?

Vincent OS is an Open Source based on ReactOS™.

The code of Vincent OS is licensed under [GNU GPL 2.0](https://github.com/Vincent-OS/Vincent-OS/blob/master/COPYING).

### Product quality warning

**Vincent OS is currently an Pre-Alpha quality operating system.** This means that Vincent OS is under heavy development and you have to be ready to encounter some problems. Different things may not work well and it can corrupt the data present on your hard disk. It is HIGHLY recommended to test Vincent OS on a virtual machine or on a computer with no sensitive or critical data!

## Building

To build the system it is strongly advised to use the _ReactOS Build Environment (RosBE)._
Up-to-date versions for Windows and for Unix/GNU-Linux are available from our download page at: ["Build Environment"](https://reactos.org/wiki/Build_Environment).

Alternatively one can use Microsoft Visual C++ (MSVC) version 2015+. Building with MSVC is covered here: ["Visual Studio or Microsoft Visual C++"](https://reactos.org/wiki/CMake#Visual_Studio_or_Microsoft_Visual_C.2B.2B).

See ["Building ReactOS"](https://reactos.org/wiki/Building_ReactOS) article for more details.

### Binaries

To build Vincent OS you must run the `configure` script in the directory you want to have your build files. Choose `configure.cmd` or `configure.sh` depending on your system. Then run `ninja <modulename>` to build a module you want or just `ninja` to build all modules.

### Bootable images

To build a bootable CD image run `ninja bootcd` from the build directory. This will create a CD image with a filename `bootcd.iso`.

You can always download fresh binary builds of bootable images from the ["Daily builds"](https://reactos.org/getbuilds/) page.

## Installing

By default, Vincent OS currently can only be installed on a machine that has a FAT16 or FAT32 partition as the active (bootable) partition.
The partition on which Vincent OS is to be installed (which may or may not be the bootable partition) must also be formatted as FAT16 or FAT32.
Vincent OS Setup can format the partitions if needed.

Starting with 0.4.10 of ReactOS, Vincent OS can be installed using the BtrFS file system. But consider this as an experimental feature and thus regressions not triggered on FAT setup may be observed.

To install Vincent OS from the bootable CD distribution, extract the archive contents. Then burn the CD image, boot from it, and follow the instructions.

See ["Installing ReactOS"](https://reactos.org/wiki/Installing_ReactOS) Wiki page or [INSTALL](INSTALL) for more details.

## Testing

If you discover a bug in ReactOS search on Issues first - it might be reported already. If not report the bug providing logs and as much information as possible.

## Contributing

We are always looking for developers! Check [how to contribute](CONTRIBUTING.md) if you are willing to participate.

__Legal notice__: If you have seen proprietary Microsoft Windows source code (including but not limited to the leaked Windows NT 3.5, NT 4, 2000 source code and the Windows Research Kernel), your contribution won't be accepted because of potential copyright violation.

You can also support Vincent OS by [donating](https://reactos.org/donate/)!

## More information

Vincent OS is a Free and Open Source operating system based on ReactOS who is basend on the Windows architecture,
providing support for existing applications and drivers, and an alternative to the current dominant consumer operating system.

Also see the [media/doc](/media/doc/) subdirectory for some sparse notes.

## Who is responsible

Active devs are listed as members of [GitHub organization](https://github.com/orgs/reactos/people).
See also the [CREDITS](CREDITS) file for others.

## Code mirrors

The main development is done on [GitHub](https://github.com/Vincent-OS/Vincent-OS).
