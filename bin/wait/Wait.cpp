/*
 * Copyright (C) 2009 Niek Linnenbank
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "Wait.h"

#include <sys/wait.h>

Wait::Wait(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Wait for a process to finish");
    parser().registerPositional("PID", "SWait for a process to finish running");
}

Wait::~Wait()
{
}

Wait::Result Wait::exec()
{
    int pid = 0;
	int status;

    // Convert input to seconds
    if ((pid = atoi(arguments().get("PID"))) <= 0)
    {
        ERROR("invalid pid `" << arguments().get("PID") << "'");
        return InvalidArgument;
    }

	int result = waitpid(pid, &status, 0);
	
    // Wait now
    if (result >= 0)
    {
        ERROR("failed to sleep: " << strerror(errno));
        return Sucess;
    }
	else
	{
		ERROR("process does not exist: " << strerror(errno));
		return InvalidArgument;
	}

    // Done
    return Success;
}