sed G test.sh

perl -Mbigint -E 'say 2**1024'

perl -e 'printf("%5s%5s\n","hi","h")';

nl color.sh
cat -b color.sh

(printf "PERM LINKS OWNER GROUP SIZE MONTH DAY HH:MM/YEAR NAME\n"; ls -l | sed 1d) | column -t

a=10
printf "hello\vtest\vnew\v%d\n" $a

int=1
while(( $int<=5 ))
do
	echo $int
	let "int++"
done

/usr/bin/basename include/stdio.h .h
