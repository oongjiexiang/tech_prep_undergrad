# Setting up MySQL (Software System -- an RDBMS) manually on Windows
[Main Reference](https://www3.ntu.edu.sg/home/ehchua/programming/sql/MySQL_HowTo.html)
  
1. Setting Up
- Download the SQL Community Server package archive and extract it to a directory, e.g. `C:/SQLProject/mysql`
- `cd bin`
- Start server application with `mysqld --initialize --console` (mysql daemon, _, output on console)
    - When `--initialize` is run after installing once (just once), `root`'s password will be given. Save it
- Start client side with `mysql -u root -p` (user, prompt password)
- use the password given. Can change password with `ALTER USER 'root'@'localhost' IDENTIFIED BY 'myPassword';`
    - As MySQL saves passwords as SHA1, if I need to log in with js (i.e. not on cmd), change with `ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'myPassword';`
    - If this is just configured, please then run [`FLUSH PRIVILEGES;`](https://stackoverflow.com/questions/50093144/mysql-8-0-client-does-not-support-authentication-protocol-requested-by-server)
- One terminal must be open to run database server

2. Administration by `root` user
- `CREATE USER 'oong'@'localhost' IDENTIFIED WITH mysql_native_password BY 'hisPassword';`
- `GRANT ALL ON *.* TO 'oong'@'localhost';`
    - or `GRANT SELECT, INSERT ON STUDENTS.* TO 'oong'@'locahost';`. Give only the necessary privileges

3. Access all databases
- `SHOW DATABASES;` or `SHOW SCHEMAS;`
- `mysql -u user -p -e 'SHOW DATABASES';` can be used if I don't want to log in to see

