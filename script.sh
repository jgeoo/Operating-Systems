
score=0
checkc=0
if test -f $1
then 
checkc=`$2|grep \.c$|wc -l`
if test checkc != 0 
then

score=`gcc -Wall "$1" 2>&1| egrep 'error:|warning:' | wc -l`
echo "For the file $1 there is $score warnings/errors"

else echo "Is not a C file"
fi
else echo "Not a Directory"
fi
