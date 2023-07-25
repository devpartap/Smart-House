// --DEBUG?
#define __DEBUG__ 

// --PLACETOCOMPILE?
#define _LOBBY_
//#define _MAINROOM_

#ifdef __MEGA2560__
#define ESP8266 Serial1
#endif

#ifdef __UNO__
#define ESP8266 Serial
#endif

#if defined(__MEGA2560__) && defined(__DEBUG__)
#define Console(x) Serial.x
#else
#define Console(x)
#endif


#define test_led 12

void processRequest(String &req);

// // AT+CIFSR
// 192.168.29.167
// GET / HTTP/1.1
// www.columbia.edu/~fdc/sample.html
// // AT+CIPMUX=1
// // AT+CIPSERVER=1,0080
// // AT+CIPSEND=0,1250
