# TheOS

**Disclaimer: This operating system is still in very early stages of development. Please don't use this until a stable release is published.**

The Theos Operating System *(TheOS)* is an operating system tailored towards tinkerers who want complete control over their hardware.

## Installation

To install TheOS, you have to build an iso from source.

### Build from source

In order to build the iso from source, you are going to need to [install some packages](#package-managers) according to your package manager.

#### Package managers

Here is a list of the packages needed for some package managers:

``` bash
# apt
sudo apt install nasm xorriso grub-pc-bin grub-common mtools libisoburn-dev libburn-dev qemu qemu-system-x86 build-essential

# dnf 
sudo dnf install nasm xorriso grub2-pc grub2-common mtools libisoburn-devel libburn-devel qemu qemu-system-x86 build-essential

# pacman
sudo pacman -S nasm xorriso grub mtools libisoburn qemu base-devel

# brew
brew install nasm xorriso grub mtools libisoburn qemu
```

After installing the required packages, run the following command to build the iso into ```build/theos.iso```:

``` bash
sudo make
```

## Usage

After obtaining an iso, you have to run the operating system in a [virtual machine](). You can either use [QEMU](#qemu) or [VirtualBox](#virtualbox) for this.

For testing purposes, QEMU is recommended because the startup time is much faster than VirtualBox, however I recommend using VirtualBox if you're trying to closely resemble hardware.

### QEMU

A run script has already been set up for QEMU, you just need to run it. Type ```./run.sh``` in the terminal to run the script.

### VirtualBox

Set up a new 64-bit virtual machine and keep all the settings default as they are plenty. After setting it up, click 'Start' to run the machine.

## License

TheOS is under an Apache 2.0 license. More information can be found in the [LICENSE](./LICENSE) file.
