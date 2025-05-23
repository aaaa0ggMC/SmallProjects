#ifndef CTOOL_INC
#define CTOOL_INC
#include <windows.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <sys/stat.h>
#include <math.h>
#include "acKernel.h"

using namespace std;

#ifdef BUILD_DEBUG
#define O(x) cout << x
#define Oln(x) cout << x << endl
#endif // BUILD_DEBUG

namespace ctk{

    struct TMST0{
        DWORD all;
        DWORD offset;
    };

    class Clock : public OnDestroyHandler{
    public:
        Clock(bool start = true);
        void Start();
        TMST0 Stop();
        DWORD GetALLTime();//Do not set pre time
        DWORD GetOffset();//Set Pre Time
        TMST0 Now();//Do not reset preTime
    private:
        DWORD m_StartTime;
        DWORD m_PreTime;
        bool m_start;
    };
}

namespace strps{
    string GetTranslateString(string in);
    void split(vector<string> & vct,const string & line,const char sep);
    string Trim(string & str);
    void Stringsplit(string str, string splits, vector<string>& res);
    namespace encoding{
        string GBKToUTF8(const string &strGBK);
        string UTF8ToGBK(const string &strUTF8);
    }
}

namespace fileIO{
    int file_size(char* filename);
    b�ol check_exists(char* filename);
}

namespace num{
    namespace random{
        typedef struct RandomShakeStruct : public OnDestroyHandler{
            float shakeValue;
            float time;
            float timePerRound;
            float mn;
            float mx;
            float start;
            int stDirection;
            ctk::Clock insideClock;
        } ShakeSt;
        void ShakeInit(ShakeSt & st,float timePerRound,float minv,float maxv,float start,int startDiection = 1);
        void Shake(ShakeSt & st);
    }
    namespace vectors{
        struct Vector : public OnDestroyHandler{
            float x;
            float y;
            float z;
            Vector(float v0,float v1,float v2);
        };
        Vector Normalize(Vector);
  � }
}

#endif // CTOOL_INC
