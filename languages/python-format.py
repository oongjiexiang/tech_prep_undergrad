#format complex numbers
c = 4 - 3j
print('The complex number {0} consists of the real part {0.real} and \
imaginary part {0.imag}'.format(c))

#format lists
coord = 4,3
print('X: {0[0]}, Y: {0[1]}'.format(coord))

#' can be included with !r
print('repr() shows quotes :{!r}, whereas str() doesn\'t: {!s}'.format(\
    'test1', 'test2'))

#alignment with <^>
print('{:<30}'.format(10))
print('{:>30}'.format('right aligned'))
print('{:*^30}'.format('centre'))

#formatting the signs of numbers with -, ,+
print("{:-f}; {:-f}".format(3.14, -3.14))
print("{: f}; {: f}".format(3.14, -3.14))
print("{:+f}; {:+f}".format(3.14, -3.14))

#formatting with bases
print("{0:d}; {0:x}; {0:X}; {0:o}; {0:b}; {0:#o}; {0:#b}; {0:#x}".format(42))

#formatting with , for thousands
print("{:,}".format(123462454))

#formatting for significance or decimal numbers
print("{0:.3} uses significance; {0:.3%} uses % or f identifier".format(1.012423))

#format date: the sequence and letters are consistent
import datetime
d = datetime.datetime(2019, 9, 1, 9, 43, 12)
print("{:%Y-%m-%d %H:%M:%S}".format(d))

#nested formatting: usage of zip
for align, text in zip('<^>', ["left aligned", "centre", "right aligned"\
                                ,"justify"]):
    print("{0:{fill}{align}16}".format(text, fill = align, align = align))

#nested formatting: usage of string
width = 16
for i in range(5, 17):
    for base in 'dXob':
        print("{0:{width}{base}}".format(i, width = width, base = base), end = ' ')
    print()

#formatting: usage of list
octets = [129, 68, 55, 109]
print("{:02X}{:02X}{:02x}{:02x}".format(*octets))

#String Template
from string import Template
s = Template("$who likes $what")
print(s.substitute(who = 'tim', what = 'kung pao'))

d = dict(who = 'tim')
print(Template('$who likes $what').safe_substitute(d))
#print(Template('$who likes $what').substitute(d)) will raise an error\
#because there is only one element in d but there are two placeholders.
#safe_substitute always attempts to return a string instead of an exception.
#in truth, $$ is an escape character whereas $something is a placeholder.
#in safe_substitute, Python will read it as $, implying that it has ignored
#the malformed template
