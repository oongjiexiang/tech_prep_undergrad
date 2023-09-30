- [1 All valid points obtained at step x may be pivotal](#1-all-valid-points-obtained-at-step-x-may-be-pivotal)
- [2 Remove the first point of a type](#2-remove-the-first-point-of-a-type)


# 1 All valid points obtained at step x may be pivotal
I'm trying to see how far I can jump to a valid index (with "0") within a global limit [minJump, maxJump], but due to the presence of minJump, it may happen that the furthest index is reached due to a slightly smaller index -- can't just only compute from the furthest index attained so far!
<details>
<summary>Solution</summary>
<br>
BFS. Key reason is **any** index **is a possible pivot** in optimising the furthest index.

Source: [Jump Game VII](https://leetcode.com/problems/jump-game-vii/)
</details>

# 2 Remove the first point of a type
I have 2 types of points: R and D. In round robin, R and remove D, and vice versa. The greedy strategy is to remove the **first** opponent that comes next, but how can I know track **which** opponents are **already removed**, and which one is therefore the first opponent?
<details>
<summary>Solution</summary>
<br>
Queue. In fact, 2 queues for 2 types. You said you don't know how to track which point, so simply use queue to store the indices for points of that type, and pop it when you need to remove

Source: [Dota2 Senate](https://leetcode.com/problems/dota2-senate/description/)
</details>