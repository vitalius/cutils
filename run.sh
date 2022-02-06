# build with profile
gcc -Wall -pg test_llist.c llist.c -o a.out && ./a.out


# run profile
gprof -p -b a.out gmon.out
