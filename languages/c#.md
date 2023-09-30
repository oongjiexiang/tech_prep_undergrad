<h1>C# Omnibus</h1>
Your refuge when preparing for C# coding tests with just a source

- [Read these to gain all you need](#read-these-to-gain-all-you-need)
- [Linq](#linq)
- [Conversion](#conversion)
  - [Convert string to integer](#convert-string-to-integer)
  - [Convert numbers to any others](#convert-numbers-to-any-others)
- [How to Write](#how-to-write)
  - [Multiline string](#multiline-string)
  - [Dictionary](#dictionary)
  - [Array](#array)
- [Sort](#sort)

# Read these to gain all you need
- [Most complete, includes OODP, multithreading rules](https://blog.christian-schou.dk/csharp-cheat-sheet/)
- [String functions](https://quickref.me/cs.html) 

# Linq
[Complete Cheatsheet](https://vslapp.files.wordpress.com/2011/11/linq-cheatsheet.pdf)

# Conversion
## Convert string to integer
```cs
if(int.TryParse(Console.ReadLine(), out input var_to_store)){
    Console.WriteLine($"{var_to_store} entered");
}
else{
    Console.WriteLine("Input invalid but .TryParse() does not throw error");
}

try{
    Int32.Parse("-abc");
}
catch(FormatException){}
```

## Convert numbers to any others
```cs
Convert.ToString(123);
Convert.ToInt32(0.1);
Convert.ToSingle(3);    // ie Float x Double
```

# How to Write
## Multiline string
```cs
string x = @"as
sadf"
```

## Dictionary
```cs
var dict = new Dictionary<char, int>(){
  ['a'] = 1, ['b'] = 2
};
var dict = new Dictionary<char, int>(){
  {'a', 1}, {'b', 2}
};
```

## Array
```cs
Array.Fill(arr, 1);   // memset(arr, 1, sizeof(arr))
foreach(var i in Enumerable.Range(0, m-1))    // for(int i = 0; i < m; i++), or `for i in range(m)` in Python
```

# Sort
```cs
Array.Sort(arr_var);  // for array
list_var.Sort();  // for lists
list_var.Sort((x, y) => y.customKeyName.CompareTo(x.customKeyName));    // custom sort. Descending sort since y compareto x

// Dictionary
var ordered = dict.OrderBy(x => x.Key).ToDictionary(x => x.Key, x => x.Value);  // dict sorted by its value
var sortedDict = SortedDictionary<string, int>(unsortedDict.ToDictionary(x=>x, y=>y));
List<CustomClass> brandNewObj = unsortedObj.OrderBy(x => x.customKeyName).ToList(); // Linq, but low performance as non-inplace sort
```
