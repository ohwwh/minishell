while :
do
	leaks $1 | grep 'LEAK: '
	sleep 1
done