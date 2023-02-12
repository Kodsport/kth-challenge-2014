import sys
import argparse
import math
import random
import string

filenameprefix = 'pizzaproblems'
shuffle_data = True
case_number = 1
maxVars = 250
maxClauses = 10000
maxNameLen = 15
maxWidth = 30

fixed_desc = [
]

fixed_cases = [
]


def next_files():
    global case_number
    filename = '%s-%02d' % (filenameprefix, case_number)
    case_number +=1 
    infile = open(filename + '.in', 'w')
    ansfile = open(filename + '.ans', 'w')
    descfile = open(filename + '.desc', 'w')
    return (infile, ansfile, descfile)

def gen_name():
    res = ''
    while len(res) < maxNameLen:
        res += random.choice(string.ascii_lowercase)
        if random.randint(1, 3) == 1: break
    return res

def gen_names(V):
    seen = set()
    names = []
    for i in range(V):
        while True:
            name = gen_name()
            if name not in seen:
                break
        seen.add(name)
        names.append(name)
    return names

def print_case(V, clauses, descr = None):
    (infile, ansfile, descfile) = next_files()

    names = gen_names(V)
    assign = [1 for i in range(V)]

    if shuffle_data:
        random.shuffle(clauses)
        assign = [2*random.randint(0, 1)-1 for i in range(V)]

    infile.write('%d\n' % (len(clauses)))
    for clause in clauses:
        if shuffle_data:
            random.shuffle(clause)
        infile.write('%d' % len(clause))
        for var in clause:
            infile.write(' %c%s' % ('+-'[var*assign[abs(var)-1]<0], names[abs(var)-1]))
        infile.write('\n')

    for i in range(V):
        if assign[i] == 1: ansfile.write('%s\n' % names[i])

    if descr is not None:
        descfile.write('%s\n' % descr)

    infile.close()
    descfile.close()

    
def get_stats(V, clauses):
    stat = [[0,0] for i in range(V)]
    for C in clauses:
        for lit in C:
            stat[abs(lit)-1][1] += 1
            stat[abs(lit)-1][0] += lit/abs(lit)
    return stat


def gen_basic_plant(V, C, Wmin, Wmax, trivialvars, disagreevars, rare_clauses):
    sys.stderr.write('Gen basic plant %d %d %d %d %d %d %d.\n' %(V, C, Wmin, Wmax, trivialvars, disagreevars, rare_clauses))
    clauses = []
    assert 3*trivialvars < Wmin
    TrivialVars = range(1,trivialvars+1)
    DisagreeVars = range(trivialvars+1, trivialvars+disagreevars+1)
    RemainingVars = range(trivialvars+disagreevars+1, V+1)

    for i in range(rare_clauses):
        W = random.randint(Wmin, Wmax)
        W23 = (2*W+2)/3
        base = random.sample(DisagreeVars, W23)
        rest = random.sample(RemainingVars, W-W23)
        clause = base + [-x for x in rest]
        clauses.append(clause)

    for i in range(C-rare_clauses):
        W = random.randint(Wmin, Wmax)
        agreeing = (2*W+2)/3 - trivialvars
        disagreeing = W - agreeing - trivialvars
        Disagreeing = random.sample(DisagreeVars + RemainingVars, disagreeing)
        Avail = [x for x in RemainingVars if x not in Disagreeing]
        Agreeing = random.sample(Avail, agreeing)
        clause = TrivialVars + Agreeing + [-x for x in Disagreeing]
        clauses.append(clause)

    stats = get_stats(V, clauses)
    for i in range(V):
        sys.stderr.write('  x(%d): bias %d/%d ~ %.3f\n' % 
                         (i, stats[i][0], stats[i][1], 1.0*stats[i][0]/stats[i][1]))

    descr = 'Planted instance %d variables, %d clauses, clause widths in [%d,%d].\n' % (V, C, Wmin, Wmax)
    if trivialvars > 0:
        descr += 'There are %d trivial variables occuring with same sign in every clause.\n' % trivialvars
    if rare_clauses > 0:
        descr += 'There are %d disagreeing variables occuring with wrong sign in most of their clauses, but %d clauses on these variables forcing some of them to go in other direction' % (disagreevars, rare_clauses)
    print_case(V, clauses,  descr)

def gen_double_plant(V, C, W, free=0):
    pass

def gen_fixed_cases():
    for i in range(len(fixed_cases)):
        (infile, descfile) = next_files()
        infile.write(fixed_cases[i])
        descfile.write(fixed_desc[i])
        infile.close()
        descfile.close()

    

def gen_random_cases(args):
    for w in [3, 6, 9]:
        gen_basic_plant(min(maxVars, int(maxClauses/(0.7*2**w))), maxClauses, w, w, 0, 2*w, 2*w)
        gen_basic_plant(min(maxVars, int(maxClauses/(0.7*2**w))), maxClauses, w, w, (w-1)/3, 2*w, 2*w)

    # some random choices of params
    for i in range(10):
        clauses = random.randint(maxClauses/10, maxClauses)
        vars = random.randint(maxVars/10, maxVars)
        minW = random.randint(3, min(maxWidth, vars))
        maxW = random.randint(3, min(maxWidth, vars))
        if minW > maxW:
            (minW, maxW) = (maxW, minW)
        if random.randint(1, 4) == 1: # 25% chance of having some trivial variables
            trivial = random.randint(0, (minW-1)/3)
        else:
            trivial = 0
        # 80% chance of disagree clauses, or no chance if not enough remaining variables
        if random.randint(1, 5) == 1 or (2*maxWidth+2)/3 > (vars-trivial)/3:
            rare_clauses = 0
            disagree = 0
        else:
            rare_clauses = random.randint(1, clauses/10)
            disagree = random.randint((2*maxWidth+2)/3, (vars-trivial)/3)
        gen_basic_plant(vars, clauses, minW, maxW, trivial, disagree, rare_clauses)

    # not very interesting, just to get max size test case
    gen_basic_plant(maxVars, maxClauses, maxWidth, maxWidth, 0, (2*maxWidth+2)/3, 1)


parser = argparse.ArgumentParser(description='generate testdata for %s (a bunch of fixed cases and a bunch of random cases)' % filenameprefix)
parser.add_argument('-r', help='generate r times as many random cases (set to 0 to skip random cases)', type=int)
parser.add_argument('-s', help='random seed', type=int)
parser.add_argument('--no-fixed-cases', help="don't generate the fixed cases", action='store_true')

args = parser.parse_args()

r = 1
if args.r is not None:
    r = args.r
if args.s is not None:
    random.seed(args.s)

if not args.no_fixed_cases:
    gen_fixed_cases()

for i in range(r):
    gen_random_cases(args)

