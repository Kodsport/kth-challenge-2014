#!/bin/sh

SOLVER=per

echo "10 1" | python gen_rand.py > secret/01.in
echo "10 2" | python gen_rand_close.py > secret/02.in
echo "50 3" | python gen_rand.py > secret/03.in
echo "100 4" | python gen_rand_close.py > secret/04.in
echo "10000 5" | python gen_oneway_exact.py > secret/05.in
echo "1000 6" | python gen_rand.py > secret/06.in
echo "100000000 7" | python gen_oneway_exact.py > secret/07.in
echo "1000000 8" | python gen_rand_close.py > secret/08.in
echo "100000000 9" | python gen_rand.py > secret/09.in
echo "100000000 10" | python gen_oneway_exact.py > secret/10.in
echo "100000000 11" | python gen_oneway_exact_no.py > secret/11.in
echo "100000000 12" | python gen_rand.py > secret/12.in
echo "100000000 13" | python gen_oneway_exact.py > secret/13.in
echo "100000000 14" | python gen_oneway_exact_no.py > secret/14.in
echo "100000000 15" | python gen_rand.py > secret/15.in
echo "100000000 16" | python gen_oneway_exact.py > secret/16.in
echo "1000000 17" | python gen_rand_close.py > secret/17.in
echo "100000000 18" | python gen_oneway_exact_no.py > secret/18.in
echo "100000000 19" | python gen_oneway_exact.py > secret/19.in
echo "100000000 20" | python gen_rand.py > secret/20.in
cp edge_case1 secret/21.in
cp edge_case2 secret/22.in
echo "1000000 231" | python gen_rand_close.py > secret/23.in
echo "1000000 241" | python gen_rand_close.py > secret/24.in
echo "1000000 251" | python gen_rand_close.py > secret/25.in

for f in secret/*.in
do
    echo "solving ${f%???}"
    ./$SOLVER < $f > ${f%???}.ans
    echo "answer is:"
    ./$SOLVER < $f
done
