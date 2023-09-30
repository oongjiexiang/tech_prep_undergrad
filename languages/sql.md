<h1>Important but you often forget</h1>

- [Facts](#facts)
  - [Joins](#joins)
- [Tricky SQL Questions](#tricky-sql-questions)
  - [1 Replace GroupBy with Subquery](#1-replace-groupby-with-subquery)
  - [2 Find all groups with all attrX obeying condition](#2-find-all-groups-with-all-attrx-obeying-condition)
  - [3 Select row with the 2nd highest attrX](#3-select-row-with-the-2nd-highest-attrx)
  - [4](#4)
- [Commands](#commands)
  - [1 Skip and Take: `OFFSET`, `LIMIT`](#1-skip-and-take-offset-limit)


# Facts
## Joins
1. `NATURAL JOIN` is **`INNER JOIN`** with two caveats
   - without having duplicate join columns
   - cannot specify `ON col1=col2`

# Tricky SQL Questions
## 1 Replace GroupBy with Subquery
Q: Find total sales after 10/1/2005 **per product**.   
Schemas:
- Purchase(product, date, price, quantity)

<details><summary>Solution</summary>

```sql
SELECT DISTINCT x.product,
    (SELECT SUM(y.price * y.quantity)
    FROM Purchase y
    WHERE x.product = y.product AND date > '10/1/2005') AS Sales
FROM Purchase x
WHERE date > '10/1/2005';
```
</details>

## 2 Find all groups with all attrX obeying condition
Q: Find all companies with products **all** having price <100  
Schemas:
- Product(name, price, company)
- Company(name, city)

<details><summary>Solution</summary>

```sql
SELECT DISTINCT c.name
FROM Company c
WHERE name NOT IN (
    SELECT p.company
    FROM Product
    WHERE price >= 100
);
```
</details>

## 3 Select row with the 2nd highest attrX
Q: Find the eids of employees who make the second highest salary.
Schemas:
- EMPLOYEES(eid:integer, ename:string, salary:integer)

<details><summary>Solution</summary>

```sql
SELECT e1.eid, e1.salary
FROM EMPLOYEES e1
WHERE e1.salary = (
    SELECT MAX(e2.salary)
    FROM EMPLOYEES e2
    WHERE e2.salary <> (SELECT MAX(e3.salary) FROM EMPLOYEES e3)
);
```
</details>

## 4 
Q: Find the manufacturer(s) of computer (PC or laptop) with the highest available speed.

Schemas:
- PRODUCT(*model*, manufacturer, type)
- PC(*model*, speed, ram, hd, price)
- LAPTOP(*model*, speed, ram, hd, screen, price)

<details><summary>Solution</summary>

```sql
SELECT DISTINCT p.manufacturer
FROM PRODUCT p
WHERE p.model IN
(
  SELECT c2.model
  FROM (
    SELECT model, speed FROM PC 
    UNION
    SELECT model, speed FROM LAPTOP
  ) AS c2
  WHERE c2.speed = (
    SELECT MAX(c1.speed) 
    FROM (SELECT speed FROM PC UNION SELECT speed FROM LAPTOP) AS c1
  )
);
```
</details>


# Commands
## 1 Skip and Take: `OFFSET`, `LIMIT`
I want to skip the first 10, but I want everything after that
```sql
SELECT * FROM TABLE_X LIMIT 10, 999999999;  -- Large offset may seem hardcoded     
SELECT * FROM TABLE_X LIMIT 50 OFFSET 10;   -- OFFSET must be accompanied by LIMIT
SELECT * FROM TABLE_X WHERE id NOT IN (SELECT id FROM TABLE_X LIMIT 10)     -- if not sure how long the table is
```