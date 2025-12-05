EXEC="cmake-build-debug/DS_wet1_winter_2026.exe"

if [ ! -f $EXEC ]
	then
		echo "File $EXEC not found!"
		exit
fi

for test in tests/*.in
do
    echo "\nRunning test on file: $test"
    ./$EXEC < $test > ${test%.in}.res &&  \
    diff --brief --ignore-all-space ${test%.in}.res ${test%.in}.out
done

exit 0