<h1>FAQ for Technical Interviews</h1>

- [1 Differences](#1-differences)
  - [1.1 C++ vs Java](#11-c-vs-java)
  - [1.2 Hashing vs Encryption](#12-hashing-vs-encryption)
  - [1.3 Sessions vs JWTs](#13-sessions-vs-jwts)
  - [1.4 TDD vs BDD](#14-tdd-vs-bdd)
- [2 Algorithms](#2-algorithms)
  - [2.1 How do you prove a problem can be solved by greedy?](#21-how-do-you-prove-a-problem-can-be-solved-by-greedy)
  - [2.2 What is Dynamic Programming (DP)?](#22-what-is-dynamic-programming-dp)
- [3 Operating Systems](#3-operating-systems)
  - [3.1 RAID](#31-raid)
- [4 Design Decisions](#4-design-decisions)
  - [4.1 How do you determine whether to put input validation at the frontend or backend?](#41-how-do-you-determine-whether-to-put-input-validation-at-the-frontend-or-backend)
- [5 Testing](#5-testing)
  - [](#)


# 1 Differences
## 1.1 C++ vs Java
1. C++ code is compiled into machine code; Java into Bytecode, which is then interpreted with Just-in-time compiler (JIT) and runs on Java Virtual Machine (JVM)
2. C++ runs **faster** than Java as it's already in machine code before runtime
3. Java is more portable across machines (platform independent), since JVM for the corresponding machine would have been installed. Write once, run anywhere.
4. C++ has manual control over memory management (use/free pointers); Java has automatic garbage collection.
   - C++ allows manipulation of pointers; Java only has object references

## 1.2 Hashing vs Encryption


## 1.3 Sessions vs JWTs

| Aspect | Session                                                                 | JWT                                                                                    |
| ------ | ----------------------------------------------------------------------- | -------------------------------------------------------------------------------------- |
| Token  | 128-bit random string (SSID)                                            | HMAC-SHA256(server_secret, base64(header), base64(payload))                            |
| Stored | SSID, userid, start & expiry time, IP addr in server                    | JWT in client                                                                          |
| Pros   | Stronger guarantees that each individual requests is authorised         | Faster authorisation (server no need to check db), interoperability with external apps |
| Cons   | Server response latency because read-write-update session details in db | Cannot invalidate tokens once they are issued! Logouts or downgrading user privilege cannot work immediately like Session does |

## 1.4 TDD vs BDD
Source: [Cucumber](https://cucumber.io/blog/bdd/bdd-vs-tdd/), [Browser Stack](https://www.browserstack.com/guide/tdd-vs-bdd-vs-atdd)

Test-driven development and Behavior DD are testing methodologies. TDD has been used in Agile development long ago, whereas BDD is new.

- TDD is focused on testing small pieces of functionality in isolation; BDD is designed to test an application's behaviour from an **end user's standpoint**.
  - TDD is a development technique that focuses more on the **implementation** of a feature; BDD on the **system’s behavior**
- A TDD test asserts the result of a **method**; BDD is only concerned about the result of a **high-level scenario**.
- TDD involves only developers; BDD **involves product managers**, test engineers and developers to create concrete examples of desired functionality.
- During discussion, TDD cases are written in coding languages; BDD/ Acceptance Test DD cases are written in English or Gherkin

BDD gives stakeholders greater confidence that the software code is not only correct, but it models the feature's behaviour as expected by users.

# 2 Algorithms
## 2.1 How do you prove a problem can be solved by greedy?
Greedy algorithm's property: the **locally optimal** choice can be made at each step **without considering** its consequence on future steps.

## 2.2 What is Dynamic Programming (DP)?
- Optimal substructure principle
- **Breaks down** a problem into smaller overlapping problems and 
- solve each subproblem **only once**, storing the results to avoid redundant computation

# 3 Operating Systems
## 3.1 RAID
[RAID systems](https://www.javatpoint.com/what-is-raid)

# 4 Design Decisions
## 4.1 How do you determine whether to put input validation at the frontend or backend?
Backend for 
- critical validation rules
- Security-sensitive validation like authen and authorisation checks, as backend is the final line of defense to malicious input. Attackers can send requests directly to server.
- Consistency in data validation across frontend platforms
- Validation rules depend on business logic

Frontend for 
- better user experience. Feedback input errors immediately to reduce round trips to server.
- Reducing load on server

# 5 Testing
## 