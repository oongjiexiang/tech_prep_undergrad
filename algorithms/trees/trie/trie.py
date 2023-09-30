class TrieNode:
    def __init__(self):
        self.children = {}
        self.end_of_node = False

class Trie:
    def __init__(self):
        self.root = TrieNode()


    def insert(self, word):
        cur = self.root

        for c in word:
            if not c in cur.children:
                cur.children[c] = TrieNode()
            cur = cur.children[c]
        cur.end_of_node = True


    def search(self, word) -> bool:
        cur = self.root

        for c in word:
            if not c in cur.children:
                return False
            cur = cur.children[c]
        return cur.end_of_node


    def prefix(self, word) -> bool:
        cur = self.root

        for c in word:
            if not c in cur.children:
                return False
            cur = cur.children[c]
        return True


### TESTS ###
trie = Trie()

# Test 1
trie.insert("apple")
assert trie.search("apple") == True
assert trie.search("bottle") == False

# Test 2
assert trie.prefix("ap") == True

# Test 3
trie.insert("api")
assert trie.prefix("api") == True