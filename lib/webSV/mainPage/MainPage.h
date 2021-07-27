#ifndef _MAINPAGE_H_
#define _MAINPAGE_H_

// #include 
class MainPage
{
private:
    const char* _mainPage[];
public:
    void setMainPage();
    const char* buildMainPage();
    MainPage(/* args */);
    ~MainPage();
};

#endif
