1. `od` utility
```
od -b[c] input.txt     # print contents in octal format[character]
od -An[xdo] -c input.txt    # display byte offsets (first column): don't/ hexa/ decimal/ octal
od -j4 -N3 -w1 -v -     # skip 4 bytes; print 3 bytes; output width 1 per line; print duplicate characters; get from std input
od -i[ox] input.txt     # display output as decimal/ octal/ hexa byte units
```

2. `tee` utility
```
df -h | tee -i disk_usage.txt file2.txt     # output to file AND stdin; --ignore-interrupts and exit gracefully
cat file.txt | tee file.out >/dev/null      # don't print on screen
echo "newline" | sudo tee -a /etc/file.conf     # echo first then sudo, if reverse? denied access; append instead of its default -- overwrite
```

3. `xargs` utility
```
echo "file1 file2 file3" | xargs -t -n 1 touch      # --verbose; --max-args = 1
echo "file1;file2;file3" | xargs -t -d \; -I % sh -c '{touch %; ls %}'        # --delimiter = ';', --replace-str
xargs -t -L 1 -a ips.txt ping -c 1      # read line by line; --arg-file
find /var/www/.cache -type f -print0 | xargs -0 rm -f       # arguments are separated by \0
echo "  with whitespace around to trim " | xargs 
```

4. `parallel` utility
```
parallel --arg-sep ,, --arg-file-sep // echo ,, A B C // def-file       # `,,` instead of `:::`, `//` instead of `::::`
parallel -d _ echo :::: abc_-file       # record delimiter `_` instead of `\n`
parallel -0 echo :::: abc0-file     # same as `-d '\0'`
parallel -E stop echo ::: A B stop C D      # prints A B only
(echo 1; echo; echo 2) | parallel --no-run-if-empty echo    # prints 1 2

```