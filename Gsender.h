#ifndef G_SENDER
#define G_SENDER
#define GS_SERIAL_LOG_1         
//#define GS_SERIAL_LOG_2       
#include <WiFiClientSecure.h>

class Gsender
{
    protected:
        Gsender();
    private:
        const int SMTP_PORT = 465;
        const char* SMTP_SERVER = "smtp.gmail.com";
        const char* EMAILBASE64_LOGIN = "login do email que enviará em base_64";
        const char* EMAILBASE64_PASSWORD = "senha do email que enviará em base_64";
        const char* FROM = "Email que enviará a mensagem";
        const char* _error = nullptr;
        char* _subject = nullptr;
        String _serverResponce;
        static Gsender* _instance;
        bool AwaitSMTPResponse(WiFiClientSecure &client, const String &resp = "", uint16_t timeOut = 10000);

    public:
        static Gsender* Instance();
        Gsender* Subject(const char* subject);
        Gsender* Subject(const String &subject);
        bool Send(const String &to, const String &message);
        String getLastResponce();
        const char* getError();
};
#endif // G_SENDER
