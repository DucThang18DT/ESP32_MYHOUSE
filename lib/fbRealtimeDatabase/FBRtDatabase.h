#ifndef _FBRTDATABASE_H_
#define _FBRTDATABASE_H_

    #include <Arduino.h>
    #include <FirebaseESP32.h>

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

        void setFirebaseInfor(String, String);
        void setHost(String);
        void setAuth(String);
        void setDataPath(String);
        void setKeyData(String);
        void connect();
        // Todo
        void setData();
        void pushData();
        String getData(String);
    };

#endif