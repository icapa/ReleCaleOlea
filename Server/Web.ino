///----------------------------------------------------------
void setup_pins(){
  pinMode(5, OUTPUT); digitalWrite(5, 0);
  pinMode(6, OUTPUT); digitalWrite(6, 0);
  pinMode(7, OUTPUT); digitalWrite(7, 0);
  pinMode(8, OUTPUT); digitalWrite(8, 0);
} 
///----------------------------------------------------------
uint16_t http200ok(void)
{
  return(es.ES_fill_tcp_data_p(buf,0,PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n")));
}
///----------------------------------------------------------
void WEBprocessing(){
// read packet, handle ping and wait for a tcp packet:
    dat_p=es.ES_packetloop_icmp_tcp(buf,es.ES_enc28j60PacketReceive(BUFFER_SIZE, buf)); 

    if(dat_p==0){
      // no http request
      return;
    }   
    
    // tcp port 80 begin
    if (strncmp("GET ",(char *)&(buf[dat_p]),4)!=0){
      // head, post and other methods:
      dat_p=http200ok();
      dat_p=es.ES_fill_tcp_data_p(buf,dat_p,PSTR("<h1>200 OK</h1>"));
      goto SENDTCP;
    }
    
    analyse_req((char *)&(buf[dat_p+5]));
    Relay_Control();
    
    dat_p=print_webpage(buf);
    
    /*
    if (authentified == 0){
       dat_p=print_webpage_login(buf);
       }
    else{
        Relay_Control();
        dat_p=print_webpage(buf);
        }
     authentified = 0;
     */

SENDTCP:
    es.ES_www_server_reply(buf,dat_p); // send web page data
    // tcp port 80 end

}
///----------------------------------------------------------
uint16_t print_webpage(uint8_t *buf)
{

        int i=0;
        uint16_t plen;
        
        plen=es.ES_fill_tcp_data_p(buf,0,PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n"));
        
        //plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("<center><table border=0><tr><td align=right>"));
        
        
        plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("<p><h1>Caliente: "));
        if(digitalRead(A5)==1) plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("SI"));
           else plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("NO"));
        plen=es.ES_fill_tcp_data_p(buf,plen,PSTR(" "));
        /*
        if(digitalRead(A4)==1) plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("1"));
           else plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("0"));
        plen=es.ES_fill_tcp_data_p(buf,plen,PSTR(" "));
        if(digitalRead(A3)==1) plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("1"));
           else plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("0"));
        plen=es.ES_fill_tcp_data_p(buf,plen,PSTR(" "));
        if(digitalRead(A2)==1) plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("1"));
           else plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("0"));
        plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("</p> </h1>"));
        
        plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("<p><h1>Relays: "));
        if(digitalRead(8)) plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("1"));
           else plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("0")); 
        plen=es.ES_fill_tcp_data_p(buf,plen,PSTR(" "));
        if(digitalRead(7)) plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("1"));
           else plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("0")); 
        plen=es.ES_fill_tcp_data_p(buf,plen,PSTR(" "));
        if(digitalRead(6)) plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("1"));
           else plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("0")); 
        plen=es.ES_fill_tcp_data_p(buf,plen,PSTR(" "));
        if(digitalRead(5)) plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("1"));
           else plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("0")); 
        plen=es.ES_fill_tcp_data_p(buf,plen,PSTR(" "));
        
        plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("</p> </h1>"));
        */
        plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("<p><h1>Control: "));
        ///---------------------------- 1 ----------------------------------------------
        if(digitalRead(8))
                 //plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("1"));
                 {
                 plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("<a href="));
                 plen=es.ES_fill_tcp_data(buf,plen,baseurl);
                 plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("FF0100>APAGAR</a> "));
                 }
        else
                 //plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("0"));
                 {
                 plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("<a href="));
                 plen=es.ES_fill_tcp_data(buf,plen,baseurl);
                 plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("FF0101>ENCENDER</a> "));
                 }
                 
        plen=es.ES_fill_tcp_data_p(buf,plen,PSTR(" "));
        /*
        ///---------------------------- 2 ----------------------------------------------
        if(digitalRead(7))
                 //plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("1"));
                 {
                 plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("<a href="));
                 plen=es.ES_fill_tcp_data(buf,plen,baseurl);
                 plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("FF0200>1</a> "));
                 }
        else
                 //plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("0"));
                 {
                 plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("<a href="));
                 plen=es.ES_fill_tcp_data(buf,plen,baseurl);
                 plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("FF0201>0</a> "));
                 }
                 
        plen=es.ES_fill_tcp_data_p(buf,plen,PSTR(" "));
        ///---------------------------- 3 ----------------------------------------------
        if(digitalRead(6))
                 //plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("1"));
                 {
                 plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("<a href="));
                 plen=es.ES_fill_tcp_data(buf,plen,baseurl);
                 plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("FF0300>1</a> "));
                 }
        else
                 //plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("0"));
                 {
                 plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("<a href="));
                 plen=es.ES_fill_tcp_data(buf,plen,baseurl);
                 plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("FF0301>0</a> "));
                 }
                 
        plen=es.ES_fill_tcp_data_p(buf,plen,PSTR(" "));
        ///---------------------------- 4 ----------------------------------------------
        if(digitalRead(5))
                 //plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("1"));
                 {
                 plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("<a href="));
                 plen=es.ES_fill_tcp_data(buf,plen,baseurl);
                 plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("FF0400>1</a>"));
                 }
        else
                 //plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("0"));
                 {
                 plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("<a href="));
                 plen=es.ES_fill_tcp_data(buf,plen,baseurl);
                 plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("FF0401>0</a>"));
                 }
        */
        plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("</p>"));
        plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("<a href="));
        plen=es.ES_fill_tcp_data(buf,plen,baseurl);
        plen=es.ES_fill_tcp_data_p(buf,plen,PSTR(">Refrescar</a> "));
                 
        plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("</tr></table> </h1>"));
        plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("</p> </h1>"));
        
        
        //plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("<center><p><h4>KMTronic DINo Web Server v2.1</h4></p> "));
        
        
        return(plen);
}
///----------------------------------------------------------
uint16_t print_webpage_login(uint8_t *buf){
  int i=0;
  uint16_t plen;
          plen=es.ES_fill_tcp_data_p(buf,0,PSTR("HTTP/1.1 401 OK\n"));
          plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("WWW-Authenticate: Basic realm=\""));
          plen=es.ES_fill_tcp_data(buf,plen,baseurl);
          plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("\"\n"));
          plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("Date: Wed, 07 Aug 1996 11:15:43 GMT\n"));
          plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("Server: Webserv test\n"));
          plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("Content-Length: 0\n"));
          plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("Content-Type: text/html\n\n"));
}
///----------------------------------------------------------
void analyse_req(char *str){
  //authentification, modifier dGVzdDp0ZXN0 pour ta propre authentification
  if (strstr( str, pass) != NULL) authentified = 1;
}
///----------------------------------------------------------
