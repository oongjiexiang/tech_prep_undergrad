# 1. System Information

| Command            | Description                                                         |
| ------------------ | ------------------------------------------------------------------- |
| whoami             | Username                                                            |
| id                 | Uid,gid. Observe non-standard or privilege-giving groups            |
| hostname           | Computer name                                                       |
| uname -a           | Kernel name, hostname, kernel release, version, machine hw name, OS |
| ifconfig           | View/configure network interface (has mtu info)                     |
| ip                 | manipulate routing, network dev, interface and tunnels              |
| netstat            | Show network status                                                 |
| who                | anybody logging in?                                                 |
| env                | Env var                                                             |
| ls(blk,usb,of,pci) | lists block devices, usb, open files, PCI devices                   |

1. Find shell specified for this user, disregarding what he is using now: `echo "$SHELL"`
2. Find current shell: `ps -p $$`, `echo $0`

# 2. User Management
## Useradd
```bash
useradd -m -d <customised_home_dir> -u <customised_uid> -g <customised_gid> -G <secondary_groups> -s <login_shell> -c <comment> -e <YYYY-mm-dd> # Create home directory  

uid -gn <username>  # find group name of this user
```

## Usermod
```bash
usermod -a -G <group1,group2> <username>    # Append, not overwrite
usermod -g <username>       # change primary group
usermod -L <username>       # Lock user account
```

## Su
Useful when user cannot login as root via SSH (security measure)
```bash
su -    # su --login
su -c <command>     # execute command AS another user
```
sudo is more secure than su because
- `su` fails when there's no root user account: use `sudo su -` to change to root
- even if there's root account, root password is not shared among multiple admin accounts
- `sudo` allows running only specific programs, not full privileges

# 3. Package Management
Package: an archive file containing several ".deb" files

## apt
- Packages together all dependencies needed to install a program (another package)
- Each distro uses its software repos, detailed in `/etc/apt/sources.list`

```bash
apt-cache search <name-present-inpackage> # APT db displaying info of installed packages

# Once found
apt-cache show <package>

# List installed packages
apt list --installed
dpkg -l | grep -c '^ii'
sudo apt install <package> -y
```

## dpkg
```
dpgk -i <*.deb>
```

# 4. Service and Process Management
- `systemd` daemon is an Init process started first (hence PID=1) that monitors and ensures the orderly starting and stopping of services
- Processes are found in `/proc/<PID>`

## Starting, finding and checking services
```bash
systemctl list-units --type=service     # List all services
systemctl start <service>
systemctl status <service>  # Check if it is running
systemctl enable <service>  # Add it to SysV script to tell system to run this service after startup

# Reboot machine
ps -aux | grep <service>    # Check whether it's running
journalctl -u <service_name.service> --no-pager     # View logs if service fails to start
```

## Stop services
```bash
kill 9 <PID>

```

## Move Services to Background
Taking `ping -c 10 www.google.com` as an example service
1. Signal 20 (`SIGTSTP`) or `[Ctrl] + Z` after executing a command
2. `bg` after executing
3. Add `&` at the back before executing

## Move Services back to Foreground
```bash
jobs    # Find status of services sent to background
fg <Job_ID_shown_in_jobs>
```

## Multiple Commands in One Go
1. `<command1>; <command2>; <command3>`: each command executes regardless of others' failure
2. `&`: stop all other commands if previous command fails
3. `|` piping


# 5. Web Services
```bash
# Servers
apt install apache2 -y
python3 -m http.server
http-server -p 8080
php -S localhost:8080

# Downloads
curl <website>
wget <website> # curl that stores transferred files locally
```

# 6. Find Files and Dirs
```bash
which <program_file>    # find path of binary
# find file with this name, owned by root, of size (20k, 22kB), created after 3 Mar 20; print the results like `ls`, and hide all errors
find / -type f -name *.conf -user root -size +20k -size -22k -newermt 2020-03-03 -exec ls -al {} \; 2>/dev/null

sudo updatedb   # run once to update local db
locate <file_pattern>      # faster than find, but has less filters
```

# 7. File Redirections
A file descriptor is an indicator of **connection** to perform IO operations. It's maintained by kernel
```bash
# Concepts: separate directions, piping, append
# discard errors. Since the only other output is 1 (STDOUT), '1' is optional before `>>results.txt`
find /etc/ -name shadow 2>/dev/null >> results.txt | wc -l
```

# 8. Filter Contents Utilities
```bash
### Read files or echo to screen for further processing
more <file>
less <file>     # `more` that removes output from console upon exit
head/tail <file>

### Start Processing
# Assuming a file is printed by any utility and piped (`|`) to
grep -Po "https://localhost/[^\"']*"    # print only matching results

# Find unique lines (3 ways)
sort -u     # find unique lines, then sort
awk '!seen[$0]++'   # find unique lines
uniq        # print unique lines. Either `sort | uniq` or `sort -u`

cut -d":" -f1   # Delimit by ":", print 1st column
tr ":" " "      # substitute ":" with space
column -t       # display delimited result as table
awk '{print $1, $NF}'   # print 1st and last element for each line
sed 's/bin/HTB/g'   

### Example
cat /etc/passwd | grep -v "false\|nologin" | tr ":" " " | awk '{print $1, $NF}' | sed 's/bin/HTB/g'

curl -s https://www.inlanefreight.com | grep -o "https://www.inlanefreight.com/[^ '\"]*" -o | sort | uniq | wc -l
```