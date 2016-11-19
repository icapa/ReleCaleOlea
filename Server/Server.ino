#include <dnslkup.h>
#include <enc28j60.h>
#include <EtherShield.h>
#include <ip_arp_udp_tcp.h>
#include <ip_config.h>
#include <net.h>
#include <websrv_help_functions.h>




// please modify the following two lines. mac and ip have to be unique
// in your local area network. You can not have the same numbers in
// two devices:
uint8_t mymac[6] = {0xBE,0xBA,0x50,0x2C,0x6F,0x67}; 
uint8_t myip[4] = {192,168,2,77};
uint8_t mymask[4] = {255,255,255,0};
uint16_t MYWWWPORT = 80; // listen port for tcp/www (max range 1-254)
char baseurl[]="http://192.168.2.77/";
char pass[]="nopassword";

#define BUFFER_SIZE 750
static uint8_t buf[BUFFER_SIZE+1];

uint8_t authentified = 0;

EtherShield es=EtherShield();

uint16_t plen, dat_p;

///----------------------------------------------------------
void setup(){
  
  setup_pins();
  es.ES_enc28j60Init(mymac);
  es.ES_init_ip_arp_udp_tcp(mymac,myip, MYWWWPORT);
  Serial.begin(9600);
  setup_pins();
  digitalWrite(5, 0);
  digitalWrite(6, 0);
  digitalWrite(7, 0);
  digitalWrite(8, 0);
  

} // end setup

///----------------------------------------------------------
void loop(){
  //Serial.print("HOlaaa");
  
  WEBprocessing();
   
} // end loop
///----------------------------------------------------------
