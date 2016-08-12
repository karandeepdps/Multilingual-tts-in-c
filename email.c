#include <winsock2.h>

#define MAX_MSG         40000                   // max message length
#define COMM_SUFF       "\r\n"
#define COMM_USER       "USER "
#define COMM_PASS       "PASS "
#define COMM_STAT       "STAT\r\n"
#define COMM_LIST       "LIST\r\n"
#define COMM_QUIT       "QUIT\r\n"
#define COMM_RETR       "RETR "
#define COMM_TOP        "TOP "
#define COMM_DELETE     "DELE "
#define COMM_NOOP       "NOOP\r\n"

SOCKET sock_no;                             // SOCKET no
struct sockaddr_in sok = {0};               // SOCKET struct
struct hostent *hp;
string_o command, s, msg_num;
string_o user = "EMAIL_USERNAME";
string_o passw = "EMAIL_PASSWORD";
char buff[MAX_MSG];                         // pop-3 output buffer
sock_no = socket (AF_INET, SOCK_STREAM, 0); // init socket
sok.sin_family = AF_INET;
int n_bytes = 0;                            // num of return bytes

s = "gorth@Vettrasoft.com";
hp = gethostbyname(s.data());             // get server IP address
if (hp != NULL)
    bcopy ((u_char *) &sok.sin_addr, (const u_char *) hp->h_addr, hp->h_length);
else
    return -1;

sok.sin_port = (unsigned short int) htons(110);

//..........................................................
// connect to pop-3 server and logon
//..........................................................
if (::connect(sock_no, (sockaddr *) &sok, sizeof (sockaddr_in)) != 0)
    return -1;

n_bytes = ::recv (sock_no, buff, MAX_MSG, 0); // skip first server answer

// send "user" command
command = COMM_USER + user + COMM_SUFF;
n_bytes = ::send (sock_no, command.data(), command.size(), 0);

// get server answer
n_bytes = ::recv (sock_no, buff, MAX_MSG, 0);

// send PASS command
command = COMM_PASS + passw + COMM_SUFF;
n_bytes = ::send (sock_no, command.data(), command.size(), 0);

n_bytes = ::recv (sock_no, buff, MAX_MSG, 0); // get server answer

//..........................................................
// get list of messages; get number of messages in inbox
//..........................................................
command = COMM_STAT;
n_bytes = ::send (sock_no, command.data(), command.size(), 0);
n_bytes = ::recv (sock_no, buff, MAX_MSG, 0);

// extract number of messages
msg_num = get_field(buff, "+OK ");
pos = msg_num.find(' ', &ie);
msg_num = msg_num.substring(0, pos);
count = ::z_str_to_int (msg_num.data());

//..........................................................
// do all messages from list. # of messages begins from 1
//..........................................................
for (i = 1; i <= count && !ie; i++)
    ie = process_nextmail (sock_no, i, buff, do_kill);

//..........................................................
// quit and disconnect pop-3 server; send "QUIT" command
//..........................................................
command = COMM_QUIT;
n_bytes = ::send (sock_no, command.data(), command.size(), 0);
return ::closesocket(sock_no);