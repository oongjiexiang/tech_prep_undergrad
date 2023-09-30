# Environment for CTF
## Binary Exploitation
Turn off ASLR
```
sudo echo 0 >/proc/sys/kernel/randomize_va_space
```

Compile C code into 32-bit ELF binary
```bash
gcc <file>.c -o <file_object_name> -fno-stack-protector -z execstack -m32 # compile in 32-bit format
file <file_object_name> | tr "," "\n" # print out
```

Provide glibc to maintain environment (verify that `RUNPATH: b'<folder>'` is in with `file <file>`)



# Binary Exploitation Tools
## GDB
Intel Assembly syntax is more read-friendly than AT&T
```bash
mov esp, ebp # Intel uses (dest, src)
mov %ebp, %esp # AT&T uses (src, dest), symbols %$
```

To use GDB,
```bash
echo 'set disassembly-flavor intel' > ~/.gdbinit # set default
gdb -q <object_file>

set disassembly-flavor intel # add if not setting default flavor in line 1 (before entering gdb)

disassemble main
```
To find stack size of a frame
```bash
info proc all # find `objfile column=[stack]`
```

## Radare2
```bash
# Kick start analysis
r2 -d -A <binary>
aa      # analyse
pdf @ main  # disas main

# View useful data
dr  # debug: registers

ps <addr>   # print string starting from this addr
pxr 30 @ rsp    # Print 30 bytes from rsp; heX dump, human Readable (hence endiannes not shown here)
iS  # print file strings

# Breakpoints
db <addr>   # to remove breakpoint, db -<addr>; view with db
dc  # debug: continue

# Restart
oo
```

## Running Pwn file in Docker
```sh
# https://shakuganz.com/2022/04/20/use-dockerfile-for-debugging-with-pwntools/
sudo docker run -it --rm --cap-add=SYS_PTRACE --security-opt seccomp=unconfined -v $(pwd):/mnt <image>
```

## [Gadgets](https://ir0nstone.gitbook.io/notes/types/stack/return-oriented-programming/gadgets)
Any snippet of code that ends with `ret` = A subroutine code in the binary
- we can exploit by overwriting RIP with the gadget's address, thereby allowing the gadget to perform actions for us (avoids writing shellcode in NX area)
<image src='images/ropgadget-stack.png'/>

## Metasploit
Create patterns string to identify buffer overflow

```bash
/usr/share/metasploit-framework/tools/exploit/pattern_create.rb -l <random_number> > pattern.txt
cat pattern.txt # Copy
```
Calculate offset to eip
```
/usr/share/metasploit-framework/tools/exploit/pattern_offset.rb -q <eip_address_obtained>
```

## msvenom (Metasploit Venom)
Approximate the size of shellcode that will be inserted
```bash
msfvenom -p linux/x86/shell_reverse_tcp LHOST=127.0.0.1 lport=31337 --platform linux --arch x86 --format c
```

## [ROPgadget](https://github.com/JonathanSalwan/ROPgadget)
Displays addresses and gadgets that we can use in the binary when overwriting memory
```bash
ROPgadget --binary <file> | grep <register-name>
```

# Applications
## Telnet
```
sudo nmap -sV <target-ip>   # list service version: useful to identify old and vulnerable processes

# Based on the available ports, eg Telnet
telnet <target-ip>

# Misconfiguration of telnet may simply allow logging in as root, admin, administrator without authentication
```

## FTP
FTP is clear-text, thus vulnerable to MiTM. Better to use FTPS (FTP on SSL/TLS) or SFTP (SSH FTP). However, misconfigured SFTP allows no-password login as `anonymous`, thereby just `get <file>`

## SMB
On port 445, uses NBT (NetBios transport protocol over TCP/IP). SMB is application and presentation layer
```
smbclient -L <target-ip/hostname>   # list network shares. Shares without $ are custom-created, thus vulnerable to misconfig
smbclient \\\\<target-ip>\\<share>  # log in. Try logging in as guest or without password
```

## Redis
On port 6379
```
sudo apt-get redis-tools
redis-cli -h <target-ip>
info            # see everything about Redis server, including redis version, number of db and its dict counts
select 0        # select database 0
get <dict-name>
```

# Fuzzing
Without fuzzing, the manual way is to start from index.php, and then scan it for references and dig deeper. With fuzzing, we have two benefits:
1. Fuzzing of PHP files may reveal files not found with the manual method
2. automated :smile: 

## Tools
1. `ffuf`
2. `gobuster`

## Ffuf
```sh
ffuf -w <word-list-containing-possible-values> -u <base-url>/FUZZ.php -mc 304 305 # print out only those urls where <base-url>/<word>.php returns status codes 304 or 305
```

# LFI
Automate LFI exploitation
- [LFI Suite](https://github.com/D35m0nd142/LFISuite)
- [LFi Freak](https://github.com/OsandaMalith/LFiFreak)
- [liffy](https://github.com/mzfr/liffy)

# OSINT
## [MxToolbox](https://mxtoolbox.com/SuperTool.aspx)
- SPF Lookup, [DMARC lookup](https://mxtoolbox.com/dmarc/details/what-is-dmarc)

# Forensics
## Find Hidden Files (Steganography)
```
binwalk --dd='.*' <image>       # extract files in this directory
exiftool <image>            # note the comment section
```
1. CyberChef: decrypts strings

## Crack Passwords
```bash
fcrackzip -D -p <dict_path> <to_crack>  # dictionary attack, state dict file path

# John the Ripper
zip2john <encrypted_zip> > <tmp_file>
john <tmp_file>
```
