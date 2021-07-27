// void Main(){
//   Serial.println("Main function");
//   DV[0].inverse();
//   String Str = "OFF";
//   if (!DV[0].deviceStt())
//     for (int i = 1; i < tDevice; i++) DV[i].turnOff();
//   else Str = "ON";
//   String Text = "{\"Main\":\""+ Str + "\"}";
//   webServer.send(200,"application/json",Text);
// }

// void Fan(){
//   Serial.println("Fan function");
//   if (DV[0].deviceStt()) DV[1].inverse();
//   String Str = "OFF";
//   if (DV[1].deviceStt()) Str = "ON";
//   String Text = "{\"Fan\":\""+ Str + "\"}";
//   webServer.send(200,"application/json",Text);
// }
// void Door(){
//   Serial.println("Door function");
//   if (DV[0].deviceStt()) DV[2].inverse();
//   String Str = "OFF";
//   if (DV[2].deviceStt()) Str = "ON";
//   String Text = "{\"Door\":\""+ Str + "\"}";
//   webServer.send(200,"application/json",Text);
// }
// void Lamp(){
//   Serial.println("Lamp function");
//   if (DV[0].deviceStt()) DV[3].inverse();
//   String Str = "OFF";
//   if (DV[3].deviceStt()) Str = "ON";
//   String Text = "{\"Lamp\":\""+ Str + "\"}";
//   webServer.send(200,"application/json",Text);
// }
// void PLamp(){
//   Serial.println("PLamp function");
//   if (DV[0].deviceStt()) DV[4].inverse();
//   String Str = "OFF";
//   if (DV[4].deviceStt()) Str = "ON";
//   String Text = "{\"PLamp\":\""+ Str + "\"}";
//   webServer.send(200,"application/json",Text);
// }

// void Updt(){
//   String Stt[tDevice];
//   for (int i = 0; i < tDevice; i++) 
//     if (DV[i].deviceStt()) Stt[i] = "ON";
//     else Stt[i] = "OFF";
//   String Text = "{\"Main\":\""+ Stt[0] +"\",\"Fan\": \"" + Stt[1] + "\",\"Door\":\""+ Stt[2] +"\",\"Lamp\":\""+ Stt[3] +"\",\"PLamp\":\""+ Stt[4] +"\"}";
//   webServer.send(200,"application/json",Text);
// }

// void Alm(){
//   String str_dv = webServer.arg("butAlm");
//   int dv = str_dv[0] - 48;
//   String str_Time = webServer.arg("Time");
//   DV[dv].Alarm = 0;
//   for (int i = 0; i < str_Time.length(); i++)
//     DV[dv].Alarm += (str_Time[i] -48)*pow(10,str_Time.length()-i-1);
//   Blynk.virtualWrite(DV[dv].bAlarm, DV[dv].Alarm, 0, DV[dv].tZone);
//   Serial.printf("\nwebAlarm: %d\n", DV[dv].Alarm);
// }

// void UpdtALm(){
//   String Str[tDevice];
//   for (int i = 0; i < tDevice; i++){
//     String Hour = (((int)DV[i].Alarm/3600)<10)?"0"+String((int)DV[i].Alarm/3600):String((int)DV[i].Alarm/3600);
//     int Mnt = (DV[i].Alarm - ((int)DV[i].Alarm/3600)*3600)/60;
//     String Minute = (Mnt < 10)?"0"+String(Mnt):String(Mnt);
//     Str[i] = Hour + ":" + Minute;
//   }
//   String Txt = "{\"almMain\":\""+ Str[0] +"\",\"almFan\": \"" + Str[1] + "\",\"almDoor\":\""+ Str[2] +"\",\"almLamp\":\""+ Str[3] +"\",\"almPLamp\":\""+ Str[4] +"\"}";
//   Serial.printf("\nUpdate Alarm: %s\n", Txt);
//   webServer.send(200,"application/json",Txt);
// }
