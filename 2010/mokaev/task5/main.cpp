#include <QApplication>
#include "ChatDialog.h"

int main( int argc, char* argv[] ){
	QApplication app( argc, argv );
        if( argc < 2 ){
            printf("Enter a port.\n");
            return 0;
        }
        int port = atoi( argv[1] );
        UDPChatDialog udpChat( NULL, port );
	udpChat.show();
	
	return app.exec();
}
