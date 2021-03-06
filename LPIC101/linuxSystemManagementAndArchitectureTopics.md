#/sys, /proc, /dev and /var

##/var

###/var/log

Central location for all logs

###/var/cache

Contains repository caches

###/var/lib

Contain libraries and some config for example networking

##/sys

Maintains references to devices from a config perspective. So the config of the devices is in these file:

1. */sys/devices/system/cpu/cpu0* -> holds file related to the cpu
2. */sys/devices/software*
3. */sys/kernel* -> programs use these to get system info

##/proc

Everything in Linux has a reference to a file. Processes live in */proc* and you can `cd` into a process.

Or get info on systems via:

```
/proc/cpuinfo
/proc/filesystems (gives info on the available file systems)
/proc/meminfo
/proc/sys/kernel
```

Write to `/proc/sys/kernel/hostname` to set the hostname

*/dev

Contains a list of devices that are on can be connected to the file system

So via /dev/stdout one can write to stdoutA

#lsmod

Nicely formats the information that is within */proc/modules*. (This is where kernel modules are loaded)[https://access.redhat.com/documentation/en-US/Red_Hat_Enterprise_Linux/5/html/Deployment_Guide/s2-proc-modules.html]

#lspci and lsusb

##lspci 

`lspci` -> list info on pci buses and devices connected to them
  1. `-v` -> verbose
  2. `-vv` -> more verbose
  3. `-vvv` -> even more verbose
  4. `-n` -> remove name lookup format from our system
  5. `-x` -> show heXadecimal dump of standard part of the config space
  6. `-b` -> bus-centric view: in order of all the buses
  7. `-t` -> get a tree view: see how stuff is connected in your system
  8. `-s DOMAIN` -> search within a domain. This is the same as doing `lspci | grep DOMAIN`
  9. `-m` -> Output machine readable form

lspci reads */usr/share/hwdata/pci.ids*


##lsusb

Same as lspci

`lsusb [OPTIONS]`
  1. `-s` get by port
  2. `d VENDOR:DEVICEID`
  3/ `-t` -> get a tree view, easy when you have a hub

#modprobe and lsmod

**mnemonic** probe means to examine

Add, remove and view loadable Linux kernel modules. Mod location = */lib/modules/KERNELVERSION/kernel*, so `cd /lib/modules/$(uname -r)/kernel`

In CentOS 7 (lsmod)[https://www.centos.org/docs/5/html/5.1/Deployment_Guide/s1-kernel-module-utils.html] is used to show the **loaded** the kernel modules. `lsmod` formats contents of */proc/modules* pseudo-file

1. `lsmod` -> list all the loaded modules
2. `modinfo MODNAME` -> get info on a mod
3. `modprobe MODNAME` -> load a module (older equavelent `insmod MODNAME`)
4. `modprobe -r MODNAME` -> remove a module. (older equavelent `rmmod MODNAME`)

Example: `modprobe floppy`. You could use the older insmod, but it needs the full path: `/lib/modules/3.10.0-327.28.2.el7.x86_64/kernel/drivers/block/floppy.ko`


#GRUB

GRUB2 is the default Linux (bootloader)[http://www.cs.tau.ac.il/telux/lin-club_files/linux-boot/slide0002.htm] for all distro's

In */etc/default/grub* is GRUB's default config. After editing this file, do `sudo update-grub` affectuate the changes. Comment out the following two lines to show the bootloader:

GRUB_HIDDEN_TIMEOUT=0
GRUB_HIDDEN_TIMEOUT_QUIET=true

*/etc/grub.d/* contains the config files for the GRUB menu. Contents:

```
-rwxr-xr-x. 1 root root  8702 Jan  5  2016 00_header
-rwxr-xr-x. 1 root root   992 May  4  2015 00_tuned
-rwxr-xr-x. 1 root root   232 Jan  5  2016 01_users
-rwxr-xr-x. 1 root root 10232 Jan  5  2016 10_linux
-rwxr-xr-x. 1 root root 10275 Jan  5  2016 20_linux_xen
-rwxr-xr-x. 1 root root  2559 Jan  5  2016 20_ppc_terminfo
-rwxr-xr-x. 1 root root 11169 Jan  5  2016 30_os-prober
-rwxr-xr-x. 1 root root   214 Jan  5  2016 40_custom
-rwxr-xr-x. 1 root root   216 Jan  5  2016 41_custom
-rw-r--r--. 1 root root   483 Jan  5  2016 README
```

update-grub reads these bash scripts from 00 to the highest number. Is is possible to add your own menu entry by adding a file in grub.d.

The GRUB config file is in: */boot/grub/menu.lst*

#Differentiate and Optimize Storage Input

##general: manipulate, mount, and df for disk space

1. Want to create and manipulate partitions of a block device under */dev*? -> `fdisk`
2. Want to mount a filesystem or see which filesystems are mounted? -> `mount`
3. Want to know disk space usage of a file system? -> `df`

##automount via fstab

*/etc/fstab* contains info on how a file system should be mounted. Linux uses this at boot to mount the filesystems automatically:
```
#
# /etc/fstab
# Created by anaconda on Mon Sep 29 21:48:54 2014
#
# Accessible filesystems, by reference, are maintained under '/dev/disk'
# See man pages fstab(5), findfs(8), mount(8) and/or blkid(8) for more info
#
UUID=0f790447-ebef-4ca0-b229-d0aa1985d57f /                       xfs     defaults        1 1
/root/swap swap swap sw 0 0 
```

1. The first field (fs_spec) describes  the  block  special  device  or remote filesystem to be mounted. This can be done via UUID. See (lsblk)[#lsblk]. The benefit of using UUID is that is not affected by the ordering of the filesystems, as for example sda1, sda2... are.
2. The second field describes the mount point for the filesystem.
3. The third field describes  the  type  of  the  filesystem.

##disk usage of file system

`df [OPTIONS] [FILE]` -> report file system disk space usage
  1. If [FILE] is omitted, df gives info on all the mounted file systems. If [FILE] is given, df gives info on the file sytem containing [FILE]

##lsblk

How to list block devices? -> `lsblk [OPTIONS]`
  1. How to get output on file systems? -> `-f`

What is lsblk the more user-friendly version of? -> `blkid`

##*/dev/disk*##

Get overview of all the disks. How to see how the disks are mounted?

`cd /dev/disk/by-uuid && ll`

#Differentiate and Demonstrate Hot and Cold Plug Devices

Extra: (sd stands for block device, the letter after sd signifies the order in which it was first found and the number stand for the partition)[http://superuser.com/a/558163]

Cold plug: any device that can only be connected when the device is powered off. Example: CPU

Hot plug: can be connected when the device is powered on. Example: USB Hard Drive

Remember, everything is Linux is a file. But, cold plug devices are listed in the */dev/* dir wether it is mounted or not. But for hot plug devices, this only happens when a device is detected (= logical).

HAL is responsible for detecting hot plug devices and reacting to them (such as loading a kernel module) the DBUS(Desktop BUS) broadcasts a message to other processes to let them know about the newly discovered device.

#Determine Hardware Device Resources (*/proc/*)

What hardware resources is our system using?

Where are processes represented in the file system? -> The */proc/* file system

Where are the mounts represented in the file system? -> */proc/mounts/*

How can I get cpu info? -> `cat /proc/cpuinfo`

How can I get meminfo -> `cat /proc/meminfo`

How can I find mem location info? -> `cat iomem`

Where are the interrupt request signals? (basically signals wanting the kernel's attention) -> */proc/irq/*

How can I find the loaded modules? -> `cat /proc/modules`

How can I find the OS version? -> `cat /proc/version`

So the */proc/* file system is you one-stop shop for getting hardware info on your computer.

Where can you find which dma channels are currently in use by the system? -> */proc/dma* DMA stands for (Direct Memory Access)[http://whatis.techtarget.com/definition/Direct-Memory-Access-DMA]

#Filesystem Hierarchy Standard

Filesystem Hierarchy Standard (FHS), is a standard to enforce a certain layout of the files in a Unix system. This ensures consistency. (offical source)[http://www.pathname.com/fhs/pub/fhs-2.3.html]

Where is the primary hierarchy? -> */*

Where are the essential commands, available even in (single user mode)[http://www.linfo.org/single_user_mode.html]? -> */bin/*

Where are the boot files? -> */boot/

Where are our device files? -> */dev/*

Originally miscelleaneous files, now there are important files such as configurations in these dir? -> */etc/*

Where are the user's dirs? -> */home/*

Where are our essential libraries binaries for */bin/* and */sbin* -> */lib/*

(Which dir is meant for mounting for storage devices?)[http://www.linfo.org/mnt.html] -> */mnt/*

Which dir is meant for (mounting)[http://askubuntu.com/a/20681] temporary media devices? -> */media/*

Where are **optional** application packages? -> */opt/*

Where is process info stored? -> */proc/*

Where is the root's home dir? -> */root/*

Where are system binaries, (necessary for booting, restoring, recovering and repairing the file system)[http://www.pathname.com/fhs/2.2/fhs-3.14.html] installed? -> */sbin/*

Where do processes store temporary files? -> */tmp/*

Where is the second hierarhcy for non-essential applications from user space? -> */usr/*

Where is a tertiary hierarchy where the local binaries are installed? (*/usr/local/*)[https://www.centos.org/docs/5/html/5.1/Deployment_Guide/s3-filesystem-usr-local.html]

The (offical FSH)[http://www.pathname.com/fhs/pub/fhs-2.3.html#USRLOCALSHARE1] states that */usr/* should be read-only and shareable across systems. That is why local config files and logs do not reside on */usr/* and another filesystem should be mounted on */usr/local/* where only locally installed applications should be. In practice this means */usr/local/* is where you install software that is not managed by a package manager, for instance unpacking a tarball yourself and all the software managed by a package manager is in */usr/*

Where are non-essential system binaries installed? -> */usr/sbin/*

Where is non-arch binaries installed? */usr/share/*

Where are source codes, such as the kernel source installed? -> */usr/source/*

Where are files that have to remain betweens boots, but have the tendency to change quite a bit? -> */var/*. The files in */var/log* are part of a secondary hierarchy.

So what is the differnce between */tmp/* and */var/tmp*? -> The files in */var/tmp/* remain between boots, the files in */tmp/* do not.

#System Boot Process

This is best to test on a virtual machine.

Where is the valuablu non-debug, non-critical booting info stored? -> */var/log/messages*

Where are the kernel messages (also during the boot process) logged? -> */var/log/dmesg*

However */var/log/messages* and */var/log/dmesg* (can overlap)[http://unix.stackexchange.com/a/35853]

Steps of booting:

1. System startup (Bios/BootMonitor)
2. Stage 1 bootloader (Master Boot Record, usually installed in sector 0 of hard drive), this just detects where your bootloader is installed
3. Stage 2 bootloader (GRUB), defines where on your partition scheme the kernel exists
4. Kernel (Linux)
5. Init (User-space)

@todo: look up how you can enter commands to your bootloader (from 6.30 in the lecture)

#Init and Telinit

There are 6 run levels

In CentOS, the initial (system 5 init stack)[http://www.tldp.org/LDP/sag/html/run-levels-intro.html] is followed, with run level 0 to 6.

In Ubuntu this is little bit different and will be explained in another lecture.

Change the run level via `sudo /sbin/telinit 1` -> go to single level mode. `/sbin/telinit` is an invoker for `/sbin/init`
