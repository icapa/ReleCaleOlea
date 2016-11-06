///----------------------------------------------------------
void Relay_Control(){
                    
                   if ((buf[59]==0x46)&(buf[60]==0x46))
                      {
                      if ((buf[61]==0x30)&(buf[62]==0x31))  // Relay 01
                         {
                           if (buf[64]==0x31) digitalWrite(8, 1);
                           if (buf[64]==0x30) digitalWrite(8, 0);
                           return;
                         }
                      
                      if ((buf[61]==0x30)&(buf[62]==0x32))  // Relay 02
                         {
                           if (buf[64]==0x31) digitalWrite(7, 1);
                           if (buf[64]==0x30) digitalWrite(7, 0);
                           return;
                         }
                      
                      if ((buf[61]==0x30)&(buf[62]==0x33))  // Relay 03
                         {
                           if (buf[64]==0x31) digitalWrite(6, 1);
                           if (buf[64]==0x30) digitalWrite(6, 0);
                           return;
                         }
                         
                      if ((buf[61]==0x30)&(buf[62]==0x34))  // Relay 04
                         {
                           if (buf[64]==0x31) digitalWrite(5, 1); 
                           if (buf[64]==0x30) digitalWrite(5, 0); 
                           return;
                         }
                   
                      }                  
}
///----------------------------------------------------------
