from sys import stdin
import re
import sys

MAX_VARS = 250
MAX_CLAUSES = 10000
MAX_WIDTH = 30

integer = "(0|-?[1-9][0-9]*)"
litstr = re.compile("[+-][a-z]{1,15}")

line = stdin.readline()
assert re.match(integer + "\n", line)

N = int(line)
assert 1 <= N <= MAX_CLAUSES

Vars = set()
for i in range(N):
    line = stdin.readline()
    assert line[-1] == '\n'
    tokens = line[:-1].split(' ')
    assert(re.match(integer, tokens[0]))
    cnt = int(tokens[0])
    assert(cnt == len(tokens) - 1)
    assert(1 <= cnt <= MAX_WIDTH)
    seen = set()
    for lit in tokens[1:]:
        assert litstr.match(lit)
        assert lit[1:] not in seen
        seen.add(lit[1:])
        Vars.add(lit[1:])

assert 1 <= len(Vars) <= MAX_VARS

assert len(stdin.readline()) == 0
sys.exit(42)
