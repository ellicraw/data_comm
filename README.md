# Ellis Crawford 
# Data Communication and Network Programming 
# TCP Programming 

Instructions to compile client:
gcc ./eclient.c -o eclient
./eclient <server IP> <server port> <file path> <to format> <to name>
Ex : ./eclient 127.0.0.1 20000 sample.bin 0 sample_recieve.bin

Instructions to compile server:
gcc ./eserver.c -o eserver
./eserver <port>


Resources used:
“Beej's Guide to Network Programming” for learning basic TCP Programming
https://youtu.be/9g_nMNJhRVk used for file transfer
