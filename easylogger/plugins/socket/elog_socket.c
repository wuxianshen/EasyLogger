/*
 * This file is part of the EasyLogger Library.
 *
 * Copyright (c) 2015-2019, Qintl, <qintl_linux@163.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * 'Software'), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Function: Save log to file.
 * Created on: 2019-01-05
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>

#include <socket/elog_socket.h>
#include <socket/elog_socket_cfg.h>

/* initialize OK flag */
static bool init_ok = false;

//For user socket define
struct sockaddr_in local_socket_addr;
int local_socket;

void elog_set_user_socket_param(const char* _ip, unsigned short _port)
{
    local_socket_addr.sin_family = AF_INET;
    local_socket_addr.sin_port = htons(_port);
    local_socket_addr.sin_addr.s_addr = inet_addr(_ip);
}

ElogErrCode elog_socket_init(void)
{
    ElogErrCode result = ELOG_NO_ERR;

    if (init_ok)
        goto __exit;

    elog_socket_port_init();

    //create socket
    local_socket = socket(AF_INET, SOCK_DGRAM, 0);

    /*
    //client doesn't need bind port
    //bind socket and connection object
    int ret = bind(local_socket, (struct sockaddr*)&local_socket_addr, sizeof(local_socket_addr));
    if( 0 > ret)
    {
        result = ELOG_SOCKET_CREATE_ERR;
        goto __exit;
    }
    */

    init_ok = true;
__exit:
    return result;
}

void elog_socket_write(const char *log, size_t size)
{
    ELOG_ASSERT(init_ok);
    ELOG_ASSERT(log);

    elog_socket_port_lock();

    int send_len = sendto(local_socket, log, size, 0, (struct sockaddr*)&local_socket_addr, sizeof(local_socket_addr));
    if ( send_len != size )
    {
        //Error: send len error
    }
    //printf("send len : %d\n", send_len);

    elog_socket_port_unlock();
}

void elog_socket_deinit(void)
{
    ELOG_ASSERT(init_ok);

    elog_socket_port_deinit();
    close(local_socket);
}