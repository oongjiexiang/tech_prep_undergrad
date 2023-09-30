1. `wget` utility
```
wget https://example.com    # download to .   ; wget will first resolve domain's IP addr, connect to remote server, then transfer and show progress bar
wget -b -c --limit-rate 1g -P alt_dir -O alt_name.zip https://github/archive.tar.gz      # background run with status available via `tail -f wget-log` in same folder; resume download or overwrite if remote server bans resuming of download; limit 1MBps; save in different folder; different file name
wget -user-agent="Mozilla/5.0 (X11; Linux x86_64; rv:60.0) Gecko/20100101 Firefox/60.0" http://wget-forbidden.com/
wget -i linuxes.txt     # multiple URLs, each on a line in txt file. Could also be `-`
wget --ftp-user=FTP_USERNAME --ftp-password=FTP_PASSWORD ftp://example.com/filename.tar.gz
wget -m -k -p http://example.com       # mirror (complete local copy) of website; for local browsing, convert links to make them suitable for local viewing; download all necessary files for displaying HTML page
wget -q -O - "https://example.tarz" | tar -xzf - -C /var/www    # quiet status; eventually extract
wget --no-check-certificate https://domain-with-invalid-ss.com      # download file over HTTPS from host that has invalid SSL certificate
```