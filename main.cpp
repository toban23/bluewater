/*
 * main.cxx
 * 
 * Copyright 2017  <pi@raspberrypi>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <syslog.h>
#include <string.h>

using namespace std;

#define DAEMON_NAME	"TESTER"

void process()
{
	syslog(LOG_NOTICE, "Writing to my Syslog");
}     

int main(int argc, char **argv)
{
	pid_t pid, sid;

	//
	//	Set the log mask for this process. LOG_UPTO is a marco 
	//	to mask all priorities up to and including the specified
	//	log priority 
	//
	setlogmask (LOG_UPTO (LOG_DEBUG));	
	
	//
	//	Opens the log facility. LOG_CONS specifies the system console
	//	(if available), LOG_PID logs the process ID, LOG_NDELAY opens
	//	the log immediately (instead of waiting for the first message)
	//	LOG_LOCAL1 is the facility identifier 
	//
	openlog (DAEMON_NAME, LOG_CONS | LOG_PID | LOG_NDELAY, LOG_USER);
	
	syslog(LOG_INFO, "Entering Daemon");
	
	//
	//	Fork a child process
	//
	pid = fork();
	
	if (pid < 0)
	{
		syslog(LOG_ERR, "Failed to fork the daemon process");
		exit(EXIT_FAILURE);
	}
	
	syslog(LOG_INFO, "Successfully created the daemon process");

	//
	//	Successfully created the child process. Close the parent
	//	process.
	//
	if (pid > 0) 
	{ 
		exit(EXIT_SUCCESS); 
	}
	
	//
	//	Change the file mask
	//
	umask(0);
	
	//
	//	Create a new session id and a unique id for the child process
	//
	sid = setsid();
	
	if (sid < 0)
	{
		syslog(LOG_ERR, "Unable to create a new session id.");
		exit (EXIT_FAILURE);
	}
	
	syslog(LOG_INFO, "Process ID: %d", getpid());	

	//
	//	Change working directory. 
	//
	if ((chdir("/")) < 0)
	{
		syslog(LOG_ERR, "Unable to change working directory.");
		exit(EXIT_FAILURE);
	}
	
	//
	//	Since the dameon is a background process, we close all input
	//	and output file descriptors
	//
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	
	//
	//	Main Process
	//
	while(true)
	{
		process();
		sleep(10);
	}
	
	//
	//	Close the log
	//
	closelog();
	
	return (EXIT_SUCCESS);
}
