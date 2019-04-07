#!/bin/bash -xv

for i in {1..6}
do
	echo $i
done

i=3;

case i in
	3):	echo "test\n";;
	*):	echo hello;;
esac

echo "Script executed"
