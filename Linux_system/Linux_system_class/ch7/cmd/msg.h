
 struct msg_control {
   unsigned char cmd;
   
 };

 enum STATUS{
   OK=0,
   ERROR,
   UNKNOWN,
};



 struct msg_report {
     enum STATUS status; 
     int error_code;
     char data[16];


 };


 
