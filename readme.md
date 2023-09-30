<h1>Software-related Technical Interview Preparation for Undergraduates</h1>

> Omnibus of Refreshers for Undergrads

*Currently maintained by Nanyang Technological University (NTU) fresh/undergraduates in software-related degrees*

<h2>Table of Contents</h2>

- [Why This Document](#why-this-document)
  - [Target Audience](#target-audience)
  - [What It Doesn't Do](#what-it-doesnt-do)
- [How to Get the Best Here?](#how-to-get-the-best-here)
- [How to Contribute?](#how-to-contribute)
  - [Standard](#standard)

# Why This Document
Software-related roles span many fields: software engineering, artificial intelligence, cyber security, big data are among the few pillars. But it does not mean that they are mutually exclusive. If you are a software-seeking student, you may have encountered the following issues:
1. I heard of a new technology, but I do not know **where to start**, and even worse, I don't want to live the nightmare of following a long but actually wrong and incomplete tutorial! Is there a trusted knowledge base that is concise, with code that is result-replicable, and written in a way that's easily understood by students at my level?
2. I never know whether I can have a **high confidence** of possessing the **necessary** knowledge for virtually all **medium-level** interviews. What should be known by a competent CS student/software-seeker when I **just graduate**?
3. Man, another question I can't answer on Networking! **Is this question beyond** undergraduate level, or did I simply skipped this important part?

This repo is meant to address your pain points, and hopefully, increases your interview success rate . It's not easy to find internships or graduate roles while juggling with acads and CCAs!

## Target Audience
This repo is useful for:
1. School of Computer Science and Engineering, Electrical Engineering specialising in Computing undergraduates in any year
2. Students aspiring to be in software-roles that need an example or source of truth to verify their understanding
3. Students or fresh graduates without their own knowledge base, but looking to **refresh** concepts as fast as possible

## What It Doesn't Do
We have to be frank. We provide the benefits above, but we are not the best fit when
1. You hope to completely understand a field without encountering the subject: Assume you never know what client-server architecture, or software architecture is. While reading `system-design` folder will show you the terms you might encounter in this domain, it is unlikely that you can really understand the techniques and types of architecture by reading the document a few times, because you need to know the basics. This document is mainly an omnibus of refreshers.
2. You hope to ace in highly competitive interviews like quants: Quants interviews are very difficult, and often ask advanced algorithms. While we try our best to include the most complete info, our repo is to cater for acing medium-level interviews like Shopee, Grab and Tiktok.

# How to Get the Best Here?
Each folder represents a field:
- basics: what **everybody** must know. Networking, operating systems. Questions interviews always ask.
- algorithms: Greedy, dynamic programming, including data structures. This is the largest folder.
- data-analysis: Data science techniques, such as Pandas/Matplotlib
- databases: From querying as a user, to building as a data engineer
- devops: CI/CD, deployment
- languages: Cheatsheets for various programming languages, handy when your online assessment (OA) requires you to use a language you never use
- linux: bash commands, useful for software engineers.
- machine-learning: ML techniques.
- neural-networks: and deep learning techniques. Split from machine learning because natural language processing and computer vision should be in this folder.
- security: Cybersecurity.
- system-design: From software patterns from the perspective of a junior developer, to software systems as a software architect.

This table shows the recommended folders to go through before your interview for each role:

| Role                                | Recommended Folders                                        |
| ----------------------------------- | ---------------------------------------------------------- |
| Software Engineer                   | basics, databases, linux, system-design, devops, languages |
| Data Engineer                       | basics, databases, data-analysis, devops                   |
| Data Analyst, Business Intelligence | basics, data-analysis                                      |
| AI/ML Engineer                      | basics, data-analysis, machine-learning, neural-networks   |
| Pentester                           | basics, databases, languages, linux, security              |

# How to Contribute?
We really appreciate your willingness to contribute. To ensure consistency and non-redundancy in the information added, we shall use **Pull Request (PR)**. Please create a branch from `main` branch, modify the files, and commit and run
```
git push -u origin <name_of_this_branch>
```

Go to GitHub to create the pull request and wait for an approver :blush:

## Standard
Unless you strongly feel that you have identified a new field, we encourage you to add your information based on the corresponding folder. The details of each folder is [above](#how-to-get-the-best-here).

If you find a new YouTube video or article that best summarises the concept, which you think is short and easily understandable enough, you can insert the link in the file. For example, I find an online C# cheatsheet that describes 80% of what we normally use. I will then insert the link and write the rest 20% in the file.