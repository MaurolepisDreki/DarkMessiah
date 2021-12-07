/* Dark Messiah Loader (FCGI) */

#include <fcgi_stdio.h>
#include <stdlib.h>

void main( void ) {
	int count = 0;
	while( FCGI_Accept() >= 0 )
		printf( "Content-type: text/html\r\n"
			"\r\n"

			"<html>"
				"<head>"
					"<title>FastCGI Demo</title>"
				"</head>"
				"<body>"
					"<h1>FastCGI Demo</h1>"
					"<p>Request number %d running on host <i>%s</i></p>"
					"<p>%s</p>"
					"<p><i>%s</i></p>"
					"<p><b>%s</b></p>"
				"</body>"
			"</html>\n",
			++count, getenv( "SERVER_NAME" ), getenv( "SCRIPT_NAME" ), getenv( "PATH_INFO" ), getenv( "QUERY_STRING" )
		);
}

