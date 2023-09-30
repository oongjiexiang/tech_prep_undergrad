import string


class TrieNode():
    def __init__(self):
        self.children = {}
        self.endOfString = False

class Trie():
    def __init__(self):
        self.root = TrieNode()

    def insert(self, word):
        current = self.root
        for char in word:
            node = current.children.get(char)
            if node is None:
                node = TrieNode()
                current.children[char] = node
            current = node
        current.endOfString = True


    def delete(self, word):
        self.deleteRecursive(self.root, word, 0)


    def deleteRecursive(self, trienode: TrieNode, word: string, index: int):
        # base case
        if index == len(word):
            if not trienode.endOfString:
                return False
            trienode.endOfString = False
            return len(trienode.children) == 0

        # expected iteration
        node = trienode.children.get(word[index])
        if node is None:
            return False
        shouldDelete = self.deleteRecursive(node, word, index + 1)

        # received decision: delete or not
        if shouldDelete:    # yes
            trienode.children.pop(word[index])
            return len(trienode.children) == 0
        return False        # no

    

    def search(self, word):
        current = self.root
        for char in word:
            next = current.children.get(char)
            if next is None:
                return False
            current = next
        return current.endOfString

    def exist_prefix(self, word):
        current = self.root
        for char in word:
            node = current.children.get(char)
            if node is None:
                return False
            current = node
        return True

example = Trie()
example.insert('pineapplepie')
example.insert('applepie')
example.insert('aguamenti')
example.insert('expecto')
print(example.search('applepie'))
example.delete('applepie')
print(example.search('applepie'))
print(example.exist_prefix('exp'))
