<h1>Database Systems Principles</h1>

- [Cheatsheets](#cheatsheets)
- [Indexes](#indexes)
- [Isolation](#isolation)
  - [Reads](#reads)
  - [Writes: Serializable Anomaly](#writes-serializable-anomaly)
- [Deadlocks](#deadlocks)
  - [Optimistic Lock](#optimistic-lock)
- [Locks](#locks)
  - [Row-level](#row-level)


# Cheatsheets
1. [Good summary of isolation and deadlocks prelim, with SQL code](https://medium.com/@gsigety/dbms-transaction-sheet-cheat-6b8e0f698ba3)

# Indexes
Two types:
1. Clustered index: the default id created for the table with a primary key
2. Unclustered index: the index we always talk about (ie I wrote this because we often take Clustered index for granted -- or because it has less use)

Pros:
1. Reduce query time: index columns are sorted

Cons:
1. DML operations get slower: therefore indexes are suitable for databases in data warehouses that get new data updated on a **scheduled basis**, not for production databases that receive writes frequently.
   - Otherwise, the non-clusteed index worsens DML ops, because each op now has to **update the indexes on each write**!

# Isolation
1. The possibility of deadlocks is not affected by isolation levels. Because isolation level changes the behavior of read operations (except serializable), but deadlock occurs due to write operations.

## Reads
[Problems arise](https://stackoverflow.com/questions/11043712/what-is-the-difference-between-non-repeatable-read-and-phantom-read#:~:text=The%20Non%2DRepeatable%20Read%20anomaly,a%20given%20query%20filtering%20criteria.) when data modification operations from a different transaction are committed in between your two identical transactions (queries)
- Dirty reads: read UNCOMMITED data from another transaction
- Non-repeatable reads: read COMMITTED data from an UPDATE query from another transaction
- Phantom reads: read COMMITTED data from an INSERT or DELETE query from another transaction

## Writes: Serializable Anomaly
2 DML transactions are non-serializable: the first transaction that commits wins, whereas the second encounters an error.
- Serializable: execute open transactions in **any order**, but **same result**

# Deadlocks
## Optimistic Lock
No im(ex)plicit lock. Creates column 'version' to track version number of row
- Avoids deadlock as update operations fail once version check fails
- However, tedious error update process: need to check logs for "0 row affected after update"

# Locks
## Row-level
1. Shared locks
2. Exclusive locks

For a row, only either lock can be held by a transaction. Impossible for A to hold shared lock but allowing B's request for exclusive lock to be successful.