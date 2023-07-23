#define DEBUG
#define ESP8266 Serial1

#ifdef DEBUG

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
