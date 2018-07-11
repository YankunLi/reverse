// Copyright (c) 2004-2012 Sergey Lyubka
// This file is a part of civetweb project, http://github.com/bel2125/civetweb

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>

#include "civetweb.h"


static int begin_request_handler(struct mg_connection *conn)
{
    fprintf(stdout, "===============start handle request==============\n");
#if defined(REVERSE)
    fprintf(stdout, "===============start reverse==============\n");
    reverse(conn);
#endif
//    if (!strcmp(mg_get_request_info(conn)->uri, "/handle_post_request")) {
//        mg_printf(conn, "%s", "HTTP/1.0 200 OK\r\n\r\n");
//        mg_upload(conn, "/tmp");
//    } else {
//        // Show HTML form. Make sure it has enctype="multipart/form-data" attr.
//        static const char *html_form =
//            "<html><body>Upload example."
//            "<form method=\"POST\" action=\"/handle_post_request\" "
//            "  enctype=\"multipart/form-data\">"
//            "<input type=\"file\" name=\"file\" /> <br/>"
//            "<input type=\"submit\" value=\"Upload\" />"
//            "</form></body></html>";
//
//        mg_printf(conn, "HTTP/1.0 200 OK\r\n"
//                  "Content-Length: %d\r\n"
//                  "Content-Type: text/html\r\n\r\n%s",
//                  (int) strlen(html_form), html_form);
//    }

    // Mark request as processed
    return 1;
}

static void upload_handler(struct mg_connection *conn, const char *path)
{
    mg_printf(conn, "Saved [%s]", path);
}

void sig_handle(int sig) {
    signal(SIGINT, sig_handle);
    signal(SIGHUP, sig_handle);
}

int main(void)
{
    struct mg_context *ctx;
    const char *options[] = {"listening_ports", "8080", NULL};
    struct mg_callbacks callbacks;

    memset(&callbacks, 0, sizeof(callbacks));
    callbacks.begin_request = begin_request_handler;
    callbacks.upload = upload_handler;
    ctx = mg_start(&callbacks, NULL, options);
    getchar();  // Wait until user hits "enter"
    mg_stop(ctx);

    return 0;
}
