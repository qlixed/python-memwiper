for py in tests/valgrind_tests/valgrind_*.py;do 
	echo $py.log
	valgrind --tool=memcheck --suppressions=tests/valgrind_test/valgrind-python.supp python3 $py 2>&1 | sed "s/==[0-9]*== *//g" | grep -A5 LEAK &> $py.log
done
