1. `curl` utility
```
curl https://jsonplaceholder.typicode{choose, one}[1-10].com/
curl -o hello.txt https://jsonplaceholder.typicode.com/ # fetch data and store locally in hello.txt
curl -O https://mockend.com/banner.svg                  # fetch data and store locally. Filename same as remote filename
curl [-i/--include] https://mockend.com/banner.svg      # show response header too
curl [-I/--head] https://mockend.com/banner.svg     # show only response header
curl --limit-rate 1g https://mockend.com/banner.svg     # limit transfer rate to 1GB
curl -u oong@test.com:password [-T/--upload-file] https://mockend.com/banner.svg    # username: passsword
curl [-L/--location] http://google.com      # enables redirection
curl [-d/--data] "title=oong&body=Hello" https://mockend.com/banner.svg     # send data in url-encoded format
curl -X POST -d "title=oong@body=Hello" https://mockend.com/banner.svg  # select METHOD method
curl -X DELETE https://mockend.com/banner.svg       # delete the files remotely
curl -v https://jsonplaceholder.typicode.com/       # show even including TLS handshakes
```

2. `grep` utility
- Global Regular Expression Print searches input files
    - For each line, it copies a line into the buffer, compares the screen, and output it to the screen
    - *grep does not store lines, modify lines or search only a part of the line*
```
grep "boo" filename
grep -ivn "BoO" filename        # ignore-case, negative results (those that don't match), line number
grep -c "boo" filename          # number of matched lines
grep -l "boo" *                 # list all files containing "boo" in the directory
grep -x "boo" filename          # exact matches
grep -A2 "boo" filename         # print 2 additional lines after searched string
grep -E "boot|boots" filename   # egrep, more powerful than basic grep above
```

2. `awk` utility


3. `sed` utility
```
echo "abc 123" | sed 's/[0-9][0-9]*/& &/'       # abc 123 123
echo "abc 123" | sed 's/[0-9]*/& &/'            #  abc 123 123
echo "abc 123" | sed -r 's/[0-9]+/& &/'         # abc 123 123, turns on extended regex
echo "abc def" | sed -r 's/([a-z]+) ([a-z]+)/\2 \1/'    # swap words. with -r, escape characters can be interpreted
echo "abc def" | sed 's/\([a-z][a-z]*\) \([a-z][a-z]*\)/\2 \1'
sed -rn '/([a-z]+) \1/p'        # \1,... can also be used in the middle entry, not necessarily the rightmost entry
echo "abc abc abc " | sed 's/[a-z]* //2g'   # remove duplicates, starting from the second occurence (delete globally thereafter)
sed -n 's/pattern/&/' <inputfile
sed -n '/abc/I p' <old >new                 # ignore case
sed -e s/a/A -e s/b/B <old >new             # similar to sed 's/a/A' <old | sed 's/b/B' >new , but uses two processes instead of one
sed -e 's/#.*//' filename | grep -vc '^$'
sed -n 's/PATTERN/&/p' file                     # = grep PATTERN file
sed 's/PATTERN/&/p' file                        # if not PATTERN at all, cat file; else, print PATTERN twice
sed -i '1i new_texttoinsert' file           # insert into first line 
sed -i '1d' file                            # delete the first line
```

4. `find` command
```
find . -user oong -group oong -perm 777 -type f -name '*.js' -atime +30 -print
# find in current directory; user is oong; group is oong; permission is 777; plain file type; filename *.js; access time (read/write) > 30 days; print them
find . -mtime +10 -size -1000c -size +500c -perm -20 -print0
# modified time > 10 days; file size < 1000B but > 500B; group has write permission; print full file name on stdout followed by '\0' instead of '\n' -- useful when filename contains whitespaces
```

5. `wc` command
```
wc < /proc/cpuinfo      # get from standard input, prints line count, word count, byte count, filename
wc -lwmcL /proc/cpuinfo /proc/meminfo       # print line, word, char, byte count, max length of a line
find /etc -name 'host*' -printf0 | wc -l --files0-from=-    # read from std input where filenames are separated by NULL
find . -type f | wc -l
```