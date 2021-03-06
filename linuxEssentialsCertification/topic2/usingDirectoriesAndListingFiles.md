#Using dirs and listing files#

##The Linux File System##

File system is used to control how data is stored and retrieved on a storage device.

Requirements:

1. Data is organized and easily located
2. Data can be saved in a persistent manner
3. Data integrity is preserved
4. Data can quickly be retrieved for a user in a later point in time

It shouldn't matter if it is a hard disk, usb-stick or cloud storage.  

In reality there are more disk file systems. These disk file systems are implementations of specific file systems.

Linux has the file system hierarchy standard (FHS). This means:
1. Hierarchy to structure data. At the top is root(/).
2. Linux systems have standard where the root dir has certain sub dirs in a certain order.
3. [See the logic of the dirs and files](http://www.pathname.com/fhs/pub/fhs-2.3.html)

In FHS one can expect amongst others the following under */*:

1. /bin -> contains essential binaries that need to be available in single user mode for all users such, e.g. cp, rm
2. /sbin -> binaries needed by the system for booting, e.g. init mount
3. /boot -> contains boot loader files necessary for booting
4. /dev -> files that represent hardware
  1. Character orientated device files: devices that receive or send characters sequentially (such as printers and mice)
  2. Block orientated device files: device that manage data in blocks, such as your hard drive or your usb-drive.

Remember: when you interact with hardware you do that via the interface /dev/particularDevice represents.
5. /etc -> text based Config files and services running on our system.
  1. /etc/aliases -> Contains a table to redirect all local users
  2. /etc/exports -> Configured file systems to be exported to remove NFS clients
  3. /etc/fstab -> List partitions and file systems that will be automatically mounted
  4. /etc/ftpusers -> Controls users access to ftp service running on a linux file system
  5. /etc/group -> Contains local group definitions.
  6. /etc/grub.conf -> Contains config parameters for the init process
  7. /etc/hosts -> This contains a list of hostname to IP Address mappings for resolving hostnames.
  8. /etc/inittab -> Contains config params for init process
  9. /etc/init.d -> Subdir containing startup scripts and services
  10. /etc/rc.d/init.d/ -> Red Hat or CentOS based startup scripts
  11. /etc/passwd -> Users accounts file
  12. /etc/shadow -> Contains encrupted passwords for user accounts
  13. /etc/resolv.conf -> Contains DNS server and domain suffix
  14. /etc/X11 -> Contains X Window config files
6. /home -> Contains subdirs that are the home dirs for the users, for example: /home/tom
7. /lib -> Contains code libs used by programs
8. /media -> Used by some distro's to mount external devices
9. /mnt -> Used by some distro's to mount external devices
10. /opt -> Optional, files for programs you can install manually
11. /proc -> Interface for accessing processes
12. /root -> Root user's home dir
13. /sbin -> Similiar to bin, this contains **system** management files. Example ifconfig, init, shutdown etc.
14. /srv -> Services(Apache) save their files here
15. /sys -> Contains information on the hardware in our system
16. /tmp -> Contains temporary files
17. /usr -> Contains application files. Anything in here is [non-required](http://unix.stackexchange.com/questions/5915/difference-between-bin-and-usr-bin) for linux

  1. /usr/bin -> Binaries not needed in single user mode for all users
  2. /usr/sbin -> Non-essential system binaries such as deamons as httpd
  3. /usr/lib -> Libraries
  4. /usr/lib64 -> 64 bit libraries
  5. /usr/local -> Locally installed software e.g. not done via a package manager
  6. /usr/share -> Documentation
18. /var -> Variable data such as log files

###Most Important stuff on where stuff is stored###

```
/bin/       Essential command binaries that need to be available in single user mode;
            for all users, e.g., cat, ls, cp

/sbin/      Essential system binaries, e.g., init, ip, mount.

/usr/bin/   Non-essential command binaries (not needed in single user mode); 
            for all users

/usr/sbin/  Non-essential system binaries, e.g. daemons for various network-services.

/usr/local/ Tertiary hierarchy for local data, specific to this host e.g. stuff NOT installed by a package manager or part              of the distribution.
            Typically has further subdirectories, e.g., bin/, lib/, share/
```

[source](http://superuser.com/a/325196)

Linux Disk File System is responsible for the reliability of storing data on a hard drive and making it retrievable. Different formats:
1. ext2 = Second Extended File System (1993), stores data in standard hierarchical way of dirs and files. Most widely used. Fast. Aspects:
  1. Max files size = 2 Terabyte
  2. Max volume = 4 Terabyte
  3. Max filename = 255 bytes
  4. Supports Linux Files System Groups and Users
  5. Supports compression
  6. Must check entire file system if the system goes down uncleanly (power outage) not properly unounting the file system
2. ext3 = Updated version of ext2. Ext2 is upgradeable to ext3 and ext3 is downgradeable to ext2. Key advantage of ext3 is journaling. Ext3 uses the journal to check the integrity of the files thus not having to check the entire file system. Ext3 only checks those transactions which are not marked as completed in the journal. Thus ext3 takes a few seconds where ext2 takes hours.
3. Reiser = Also uses journaling, but completely different internal structure that ext2. This allow larger file sizes, such as 8 TB and max volume of 16 TB. And it is faster.
4. ext4 = Updated version ext3. Supports files up to 16 TB and volumes of up to 1 Exabyte. Maximum of  billion files on a system. Also uses checksums to check the journal file.

##Files, Dirs##

For navigation:
1. `pwd` -> print working dir
2. `cd [dir]` -> change working dir to dir. 
  1. Without `[dir]` argument ->  go to ~
  2. `.` -> current dir
  3. `..` -> up one dir
  4. `../..` -> up two dir
3. `ls` -> list content of dir
  1. `-a` -> show all files, including hidden files
  2. `-l` -> long, give type and rights on files
  3. `-R` -> Recursive, pipe to `more` to be able to read better
 
##Hidden files and dirs##

Files or dir that is prefixed with a '.' is hidden. The hidden files are only shown by the ls with `ls -a`

##Home##

Configs in the home folder take precedence over system wide configs. The user has complete control of his home dir. 

The FHS says that home is a site specific file system, but suggests */home/username*

##Absolute and relative paths##

Relative from the working dir.
Absolute from the root path, prefix with the root dir (/)

##Case Sensitivity##

Linux is case sensitive for:
1. Commands
2. Filenames
3. Dirnames

##Globbing and Quoting##

What is you don't know the exact file name : globbing. Use a wildcard symbol that stands for one or more characters. Globbing is a form of expansion. The certain characters expand:

`*` -> zero or more characters.
`?` -> one character
`[a-z]` -> one time the characters a through z

On quoting:
1. " The double quote. Protects eveything enclosed, except for:
  1.$
  2.' -> [this means itside the double quotes, a single quotes gets its literal value again.](http://unix.stackexchange.com/a/169511)
  3. "
  4. \
Use the doule quotes when you want only variables and command substition: echo $(date)

2. ' The single quote protects everything enclosed by it, this turn OFF special meaning of character.

3. \ The backslash
  1. Escape special meaning of ' and ": with the backslash it becomes literal again.
  2. Escape special meaning:`echo "\$PATH"`

The following is not mandatory for the exam, but it is handy. Note these only work with `echo -e` or with `printf`:

1. `\a` -> alert (bell)
2. `\b` -> backspace
3. `\e` -> an escape character
4. `\f` -> form feed
5. `\n` -> new line
6. `\r` -> carriage return
7. `\t` -> horizontal tab
8. `\v` -> vertical tab
9. `\\` -> backslash
10. `\'` -> single quote
11. `\nnn` -> the eight bit character whose value is the octal value nnn (one to three digits) in [ASCII](http://www.asciitable.com/)
12. `\xHH` -> the eight bit character whose value is the hexadecimal value HH

You can also use the backslash to continue inputting the command on the next line
