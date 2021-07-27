// void checkAlarm(){
//   if (DV[0].isAlarm()){
//     for (int i = 1; i < tDevice; i++) DV[i].turnOff();
//     esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
//     esp_deep_sleep_start();
//   }
//   else if (DV[0].deviceStt())
//     for (int i = 1; i < tDevice; i++) DV[i].isAlarm();
// }
// BLYNK_CONNECTED(){
//   for (int i = 0; i < tDevice; i++){
//     Blynk.virtualWrite(DV[i].bPin, DV[i].deviceStt());
//     Blynk.virtualWrite(DV[i].bAlarm, DV[i].Alarm, 0, DV[i].tZone);
//   }
// }

// BLYNK_WRITE(almFan){
//   DV[1].Alarm = param.asInt();
//   Serial.printf("\nFan Alarm: %d", DV[1].Alarm);
// }
// BLYNK_WRITE(almDoor){
//   DV[2].Alarm = param.asInt();
//   Serial.printf("\nDoor Alarm: %d", DV[2].Alarm);
// }
// BLYNK_WRITE(almLamp){
//   DV[3].Alarm = param.asInt();
//   Serial.printf("\nLamp Alarm: %d", DV[3].Alarm);
// }
// BLYNK_WRITE(almPLamp){
//   DV[4].Alarm = param.asInt();
//   Serial.printf("\nPLamp Alarm: %d", DV[4].Alarm);
// }
// BLYNK_WRITE(almMain){
//   DV[0].Alarm = param.asInt();
//   Serial.printf("\nMain Alarm: %d", DV[0].Alarm);
// }
// BLYNK_WRITE(butFan){
//   int butVal = param.asInt();
//   if (DV[0].deviceStt()) DV[1].changeStt(butVal);
//   else Blynk.virtualWrite(DV[1].bPin, 0);
// }
// BLYNK_WRITE(butDoor){
//   int butVal = param.asInt();
//   if (DV[0].deviceStt()) DV[2].changeStt(butVal);
//   else Blynk.virtualWrite(DV[2].bPin, 0);
// }
// BLYNK_WRITE(butLamp){
//   int butVal = param.asInt();
//   if (DV[0].deviceStt()) DV[3].changeStt(butVal);
//   else Blynk.virtualWrite(DV[3].bPin, 0);
// }
// BLYNK_WRITE(butPLamp){
//   int butVal = param.asInt();
//   if (DV[0].deviceStt()) DV[4].changeStt(butVal);
//   else Blynk.virtualWrite(DV[4].bPin, 0);
// }
// BLYNK_WRITE(butMAIN){
//   int pinVal = param.asInt();
//   if (!pinVal)
//     for (int i = 0; i < tDevice; i++) DV[i].changeStt(pinVal);
//   else DV[0].changeStt(pinVal);
// }

// void isConnect(){
//     if (cnnt.getValue()) cnnt.off();
//     else cnnt.on();
// //    Serial.print("Connect: ");
// //    Serial.println(cnnt.getValue());
// }
