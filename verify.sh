#!/bin/sh -f

testcases="$1"
TESTDIR="./generated-output/"
total=0
tLimit=60s

runTestcase() {
	testcase=$testcases/$1
	pts=$2
	local score=5
	local testcaseName=`basename $testcase | sed 's:.in$::'`
	hLB=`head -1 $testcases/output/$testcaseName.out`
	hUB=`tail -1 $testcases/output/$testcaseName.out`

	echo "Using Testcase $testcaseName ($pts pts):"
	echo "------------------------------------------------------------------------------------------------------"
	# TEST FREQUENCIES
	if [ -f ./frequencies ]
	then
		timeout $tLimit ./frequencies < $testcase | sort > $TESTDIR/${testcaseName}-freq.out
		diff -bBwq $TESTDIR/${testcaseName}-freq.out $testcases/output/${testcaseName}-freq.out
		if [ $? -eq 0 ]
		then
			echo "Frequencies : OK  =>  +10"	
			score=`echo "$score + 10" | bc`
		else
			echo "Frequencies : FAIL"
		fi
	else
		echo " ERROR: Executable ./frequencies Not found"
	fi

	# TEST HUFFMAN
	if [ -f ./huffman ]
	then
		bitComplexity=`timeout $tLimit ./huffman < $TESTDIR/${testcaseName}-freq.out`
		if [ ! -f codewords.txt ]
		then
			echo "ERROR: Huffman did not create codewords.txt .."
		elif [ $bitComplexity -ge $hLB ] && [ $bitComplexity -le $hUB ]
		then
				echo "Huffman : OK  =>  +35"
				echo "  * (Expected bit size printed by ./huffman $bitComplexity is within acceptable [$hLB, $hUB] range)"
				score=`echo "$score + 35" | bc`
		else
				echo "Huffman : FAIL  "
				echo "  * (Expected bit size printed by ./huffman $bitComplexity is NOT within acceptable [$hLB, $hUB] range)"
		fi
	else
		echo " ERROR: Executable ./huffman Not found"
	fi

	# TEST ENCODE
	if [ -f ./encode ]
	then
		timeout $tLimit ./encode codewords.txt < $testcase > $TESTDIR/${testcaseName}.encoded
		encodedSize=`ls -l $TESTDIR/${testcaseName}.encoded | cut -d " " -f5`
		goldSizeLowerBound=`echo "$hLB / 8" | bc`
		goldSizeUpperBound=`echo "($hUB / 8) + 20" | bc`
		if [ $encodedSize -ge $goldSizeLowerBound ] && [ $encodedSize -le $goldSizeUpperBound ]
		then
			echo "Encode : OK  =>  +25"
			echo "  * (Encoded file has $encodedSize bytes, OK within [$goldSizeLowerBound, $goldSizeUpperBound] bytes)"
			score=`echo "$score + 25" | bc`
		else
			echo "Encode : FAIL  "
			echo "  * (Encoded file has $encodedSize bytes, OK within [$goldSizeLowerBound, $goldSizeUpperBound] bytes)"
		fi
	else
		echo " ERROR: Executable ./encode Not found"
	fi

	# TEST DECODE
	if [ -f ./decode ]
	then
		timeout $tLimit ./decode codewords.txt < $TESTDIR/${testcaseName}.encoded > $TESTDIR/${testcaseName}.decoded
		diff -bBwq $testcase $TESTDIR/${testcaseName}.decoded > /dev/null
		if [ $? -eq 0 ]
		then
			echo "Decode : OK  =>  +25"
			echo "  * The input ${testcaseName}.in and the decoded file ${testcaseName}.decoded are the same."
			score=`echo "$score + 25" | bc`
		else
			echo "Decode : FAIL"
			echo "  * The input ${testcaseName}.in and the decoded file ${testcaseName}.decoded are NOT the same."
		fi
	else
		echo " ERROR: Executable ./decode Not found"
	fi
	total=`echo "$total + $score/100 * $pts" | bc -l`
	
	echo "------------------------------------------------------------------------------------------------------"
	echo " Score: $score/100 for this testcase"
	echo "------------------------------------------------------------------------------------------------------"
	echo ""
}

grader() {
	echo "Working on your report"
	rm -rf $TESTDIR
	mkdir $TESTDIR
	rm -f frequencies huffman encode decode
	make
	if [ $? -eq 0 ]
	then
		echo "Makefile : OK => +5"
		echo "All Set to run testcases now.."
		echo ""
		runTestcase sample.in 10
		runTestcase large.in 20
		runTestcase padding.in 70
	else
		echo "ERROR : make failed. Manual Grading Needed.  => -5 pts"
	fi


	echo "=================================="
	echo $total | awk '{printf("Total Score : %d\n", $0)}'
	echo "=================================="
}


if [ $# -lt 1 ]
then
	echo "Usage $0 directory-of-testcases-from-piazza"
	exit
fi

echo "Verifying your code against expected results in $testcases..."
if [ ! -f $testcases/CHECKSUM ]
then
	echo "ERROR: file CHECKSUM not found!"
	echo "Is the directory $testcases is the one you downloaded from piazza?"
	echo "If yes, then the uncompressed directory must contain a file called CHECKSUM.. Try again maybe?"
	exit
fi
#find the directory with Makefile
drm=`find . -iname "*makefile*"`
if [ -z $drm ]
then
	echo "The current directory does not seem to have the makefile.."
	exit
fi

drm=`dirname $drm$`
cd $drm
grader
cd - > /dev/null

