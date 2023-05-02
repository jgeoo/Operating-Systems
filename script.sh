
score=0
checkc=0
if test -f $1
then 
if echo "$1" | egrep '\.c$' >/dev/null
then

score=`gcc -Wall "$1" 2>&1| egrep 'error:|warning:' | wc -l`
echo "For the file $1 there is $score warnings/errors"

else echo "Is not a C file"
echo `wc -l $1`
fi
else echo "Not a Directory"
fi
