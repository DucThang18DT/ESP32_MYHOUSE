#ifndef _LOGINPAGE_H_
#define _LOGINPAGE_H_

    class LoginPage
    {
    private:
        const char* _loginPage[];
    public:
        void setLoginPage();
        const char* buildLoginPage();
        LoginPage(/* args */);
        ~LoginPage();
    };

#endif