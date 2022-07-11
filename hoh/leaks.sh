while :
do
	leaks $1 | grep 'error'
	sleep 1
done