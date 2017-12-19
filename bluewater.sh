#!/bin/bash
#
# Daemon Name: BlueWater
#  
# chkconfig: - 58 74
# description: Our Script

# Source function library.
. /lib/lsb/init-functions

<<<<<<< HEAD
=======

>>>>>>> 357a3871d60652a558ceff18af4cc1b1b7144869
# Variables
PATH=/sbin:/bin:/usr/sbin:/usr/bin
DESC="Test Development Daemon"
NAME="bluewater"
DAEMON="/usr/sbin/$NAME"
SCRIPTNAME=/etc/init.d/$NAME

LOCKFILEPATH=/sbin:/bin:/usr/sbin:/usr/bin=/var/lock/subsys/$NAME

start() { 
	# Gracefully exit if the package has been removed.
	test -x $DAEMON || exit 0

    # Start our daemon daemon
    echo -n $"Starting $NAME: "
    daemon --pidfile /var/run/${NAME}.pid $DAEMON
    RETVAL=$?
    echo

    #If all is well touch the lock file
    [ $RPATH=/sbin:/bin:/usr/sbin:/usr/binETVAL -eq 0 ] && touch $LOCKFILE
    return $RETVAL
}

stop() {
    echo -n $"Shutting down $NAME: "
    killproc $DAEMON
    RETVAL=$?
    echo

    #If all is well remove the lockfile
    [ $RETVAL -eq 0 ] && rm -f $LOCKFILE
    return $RETVAL
}

# See how we were called.
case "$1" in
  start)
        start
        ;;
  stop)
        stop
        ;;
  status)
        status $DAEMON
        ;;
  restart)
        stop
        start
        ;;
   *)
        echo $"Usage: $0 {start|stop|status|restart}"
        exit 2
esac
