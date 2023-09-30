- [1 Assign a string to another group with the same property QUICKLY](#1-assign-a-string-to-another-group-with-the-same-property-quickly)


# 1 Assign a string to another group with the same property QUICKLY
Typically I use a dict to track the number of chars in a string, so that when I need to verify whether another string is its anagram, I simply compare the two dictionaries. But what if I have millions of strings to group into different anagrams? Impractical to compare the dict of string i with the existing dicts iteratively!

<details>
<summary>Solution</summary>
<br>
What I hope is a signature that I can immediately assign this string to the group of the same signature. What do I create the signature?

A dict's keys will only be 'a-z' for an anagram, so why not have a signature that is 26-digits long, digit i corresponding to the number of occurence of letter i! Then now I only have a single dict that maps signature to a list of anagrams!

Source: [Group Anagrams](https://leetcode.com/problems/group-anagrams/)
</details>