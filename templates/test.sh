for((i = 1; ; ++i)); do
    echo $i
    ./gen.out $i > input.txt
    ./sol.out < input.txt > out1.txt
    ./brute.out < input.txt > out2.txt
    diff -w out1.txt out2.txt || break
done
