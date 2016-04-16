#!/bin/sh
if [ $# != 2 ]; then
	echo usage: test.sh PORTNUM ITERS
	echo "Should be run from inside unpv12e/servers directory."
	echo "Arguments:"
	echo "PORTNUM is the port the server will listen on.  It should not"
	echo "be in the range of ports used by your OS for ephemeral ports."
	echo "ITERS is the number of ports used by each client;"
	echo "set it to slightly less than one tenth your ephemeral port range"
	echo "(since this script runs ten copies of the client on one machine)."
	echo ""
	echo "For instance, on Linux, if /proc/sys/net/ipv4/ip_local_port_range is"
	echo "  1024	32767"
	echo "you'd want to set ITERS to 3000, and PORTNUM to e.g. 40000."
	exit 1
fi

PORT=$1
ITERS=$2

if [ ! -f serv00 ]; then
	echo 'serv00 not found.  Are you in the right directory?'
	exit 1
fi

rm *.out

set -x

# Make sure all previous connections have expired
if netstat -ant | grep -q :$PORT 
then
	echo last run not done yet, try later
	exit 1
fi

# Calculate baseline
./serv00 $PORT > serv00.out &
PROC=$!
sleep 1
./client 127.0.0.1 $PORT 1 ${ITERS}0 4000
kill -INT $PROC
sleep 1
echo serv00.out:
cat serv00.out

# Do single-thread tests
for serv in 1 6 ; do
	# Let old connections time out
	sleep 60
	PORT=`echo $PORT 1 + p | dc`
	./serv0$serv 127.0.0.1 $PORT > serv0$serv.out &
	PROC=$!
	sleep 1
	./client 127.0.0.1 $PORT 10 ${ITERS} 4000
	kill -INT $PROC
	sleep 1
	echo serv0$serv.out:
	cat serv0$serv.out
done
	
# Do multi-thread tests
for serv in 2 3 4 5 7 8 9; do
	# Let old connections time out
	sleep 60
	PORT=`echo $PORT 1 + p | dc`
	./serv0$serv 127.0.0.1 $PORT 15 > serv0$serv.out &
	PROC=$!
	sleep 1
	./client 127.0.0.1 $PORT 10 ${ITERS} 4000
	kill -INT $PROC
	sleep 1
	echo serv0$serv.out:
	cat serv0$serv.out
done
