#/bin/bash

rm -rf differences
for i in 1 2 3 4 5
do
echo Compiling main$i
g++ -o hashiitb main$i.cpp Event.cpp
echo Running executable $i
./hashiitb > studentoutput$i
echo Finding differences for executable $i
diff studentoutput$i expectedoutput$i >> differences
done
echo Differences between your output and expected output:
cat differences


echo "--------------"
echo Compiling performance measuring main
g++ -o hashiitb mainPerf.cpp Event.cpp timeTracker.cpp
echo Running performance measuring executable
./hashiitb 7643
rm -rf hashiitb
