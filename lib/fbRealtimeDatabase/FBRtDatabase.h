#ifndef _FBRTDATABASE_H_
#define _FBRTDATABASE_H_

    #include <Arduino.h>
    #include <FirebaseESP32.h>

    static String HOST = "esp32firebase-1e567-default-rtdb.firebaseio.com";
    static String AUTH = "eM8q1Ew73xkNkAmuy1DanDK0ND1FKMn7l4uAmmnu";

    enum Mode{set, push, update};

    class FBRtDatabase
    {
    private:
        String _firebaseHost;
        String _firebaseAuth;
        String _dataPath;
        String _keyData;
        FirebaseData _firebaseData;
        
    public:
        FBRtDatabase(){}
        FBRtDatabase(const FBRtDatabase&){}
        FBRtDatabase(String, String, String, String);
        ~FBRtDatabase(){}

        // setter
        void setFirebaseInfor(String, String);
        void setHost(String);
        void setAuth(String);
        void setDataPath(String);
        void setKeyData(String);
        void connect();

        // getter
        String dataPath(){return _dataPath;}
        String keyData(){return _keyData;}

        void sendData(String, String, Mode);
        void sendData(String, int , Mode);
        String getData(String);
        int getInt(String);
    };

#endif