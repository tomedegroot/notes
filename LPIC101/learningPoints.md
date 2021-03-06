#Learning Points

##gzip (DONE)

Remember: (A gzip is just one big file)[https://github.com/tomedegroot/study-material/blob/master/linux%2BLPICLevel1Exam1/managingFilesInLinux.md#the-gzip-and-gunzip-command]

###Append a zip to another zip:

```
Multiple  compressed  files  can  be  concatenated.  In this case, gunzip will extract all members at once. For example:

       gzip -c file1  > foo.gz
       gzip -c file2 >> foo.gz

Then

       gunzip -c foo.gz

is equivalent to

cat file1 file2
```

###Append a file to a zip

Well, since a zip is just one compressed item, you can easily just append zip files. See the above paragraph. Only with tar

##tar (DONE)

###Append a tar to another tar

Use the -A flag. So:

`tar -Avf archive.tar archiveToAppend.tar`, example:

```
[tom@t-degroot1 ~]$ tar cvf file.tar file1
file1
[tom@t-degroot1 ~]$ tar cvf file2.tar file2
file2
[tom@t-degroot1 ~]$ tar -Avf file.tar file2.tar
[tom@t-degroot1 ~]$ tar -tvf file.tar 
-rwxr-xr-- tom/tom          30 2016-12-18 17:44 file1
-rw-rw-r-- tom/tom          20 2016-12-20 09:02 file2
```

###Append a file to a tar -> `-r`

`tar -rvf archive.tar fileToAppend` **Mnemonic**: add file entRy

```
[tom@t-degroot1 ~]$ echo "je moeder" > file3
[tom@t-degroot1 ~]$ tar -rvf file.tar file3
file3
[tom@t-degroot1 ~]$ tar -tvf file.tar
-rwxr-xr-- tom/tom          30 2016-12-18 17:44 file1
-rw-rw-r-- tom/tom          20 2016-12-20 09:02 file2
-rw-rw-r-- tom/tom          10 2016-12-20 09:14 file3
```

###Using the '-f -'

For testing purposes, we gzip an archive and pipe it to the `tar` command to list the contents:

`gzip -c dropbox_x84_64.tar | tar ztvf -`

`-f -`; the dash has a special value for the `-f option` which means to read from stdin

###Double zipped tars

Modern versions of tar filter a file through gzip automatically.

Sometimes a tar can be double zipped. Use this info to check this:

```
You can check this by running head hello-02.tar.gz and head hello-02.tar. GZip is a very binary format, whereas tar is quite human readable. If the .tar file appears "too binary" you have a doubly encoded file on your hands.
```

[source](http://stackoverflow.com/a/14349164/1941737)

###Filter tar through bzip2

`tar -j` -> filter through bzip2

##Special value of `-` for commands

1. `cd -` -> go to previous dir
2. `tar -f -` -> read the file from stdin

##Updating & upgrading via YUM/RPM (Make a diagram)

##Partitions (To do)

How can a file system be on both /xvdf and /xvdf1?

Yes this is possible, but the filesystems will be corrupted:

1. (stackoverflow)[http://stackoverflow.com/a/41358393/1941737]
2. (linuxacademy)[https://linuxacademy.com/cp/community/view/id/13331]

##Locking and Unlocking accounts

`usermod [OPTIONS] USER` -> modify users
  1. `-L USERNAME` -> lock a user's account
  2. `-U USERNAME` -> unlock a user's account

`passwd [OPTIONS] [USER]` -> set a password [FOR USER]
  1. `-l` -> lock a user's account
  2. `-u` -> unlock a user's account
  3. `-S` -> get status of a password

So in `usermod` capitalized, but in `passwd` uncapitalized. **mnemonic** usermod has a broader purpose, so the uncapitalized letters were already taken for the options

##See which filesystems are supported by the kernel     

Check in */proc/filesystems* [source](https://www.centos.org/docs/5/html/5.1/Deployment_Guide/s2-proc-filesystems.html)

#runlevels

0	Halt the system.
1	Single-user mode (for special administration).
2	Local Multiuser with Networking but without network service (like NFS)
3	Full Multiuser with Networking
4	Not Used
5	Full Multiuser with Networking and X Windows(GUI)
6	Reboot.

#Random

1. PID = Process Identification
2. `/etc/sudoers` -> holds who can executed with elevated privileges (root)
3. `usermod -a -G group1 group2 user1` -> group1 and group2 supplementary groups for user1:
  1. `-G` -> set supplementary groups
  2. `-g` -> set login group
4. `userdel -r USERNAME` -> remove a user and remove of all the files belonging to the user
5. `useradd -m USERNAME` -> add USERNAME and create a homedir if the CREATE_HOME is set to false
6. Setting the defaults for add a user `/etc/default/useradd`
7. `top -d DELAYTIME` -> set the delay (interval) time
8. `umask OCTALNOTATIONS` -> umask only accepts octal notation
9. `rmdir -p test/file` -> Removes all the parents of the basedir file, so in this case the dir test will also be removed
10. `find -xdev` -> only search the local filesystem
11. `0x82` -> the linux swap filesystem typecode (or identifier); 0x83 -> Linux xfs/ext2/3/4 filesystem typecode
12. `du -c` -> produce a grand total (complete overview)
13. `find . -mtime +3` -> find files modified at least 3 days ago
14. `grub-mkconfig -> /boot/grub/grub.cfg` -> So grub-mkconfig sends the output by default to STDOUT
15. `shutdown -f` -> Reboot Fast, by suppressing the normal call to fsck when rebooting.
16. `shutdown -F` -> FORCE filesystem check **mnemonic** Force with capital F
17. `uniq -d` -> only print Duplicate lines. So uniq is the test for duplicate lines and the options determine what you want to output.
18. `tune2fs -c` -> set the number of times before a filesystem will be checked
19. `apt-get -s install` -> simulate an install. (**does not exist in YUM**)
20. `setopt +0` and `unset` lets you unset bash options
21. `which` tells you which command will be executed and `whereis` returns multiple matches and will not tell which will be executed.
22. */usr/local* contains shareable apps and */usr/share* is for files for multiple architectures.
23. */proc/cmdline* Holds boot parameters. These are passed by the bootloader to the kernel on boot
24. Find distro in */etc/os-release*
#dependencies

##rpm based
1. `rpm -qRp lynx-2.8.8-0.3.dev15.el7.x86_64.rpm` -> get the Requerements (dependencies) of a package. `yum deplist` is the yum equavelent
2. `rpm -i PACKAGEFILE` -> if you miss a requirement, RPM will give an error
3. `yum install NAMEOFREQUIREMENT...` -> install the requirement(s)
4. `rpm -i PACKAGEFILE` -> install the pacakge should work

##dpkg based
1. `dpkg -I PACKAGEFILE` -> get information including requirements for a package. `apt-cache depends|showpkg` is the apt equavelent
2. `dpkg i PACKAGEFILE` -> install a package, if you miss dependencies it will fail
3. `apt-get install` -> will install the missing dependencies
4. `dpkg i PACKAGEFILE` -> reinstall a package

1. `dpkg --force-depends` -> turn all errors into warning, so you can install a package even if you do not have the required dependencies

So with rpm you have to specify the missing requirements: `yum install NAMEOFREQUIREMENT`, but with dpkg, you just have to do an apt-get install without specifying the requirements

@todo: Linux System Management and Architecture
@todo: parted
