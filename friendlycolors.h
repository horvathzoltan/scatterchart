#ifndef FRIENDLYCOLORS_H
#define FRIENDLYCOLORS_H

//#include "opencv2/opencv.hpp"
//#include <QSet>
#include <QString>
#include "friendlyrgb.h"
//#include "apihelper.h"

class FriendlyColors
{        
private:
    //byte minr,ming,minb,maxr, maxg, maxb;
    //bool _isMonitoring;
    //static const QString _url;
public:    
    //static const byte _d;
    //static const int _min_level;
    //QSet<int> _fcs;
    FriendlyColors();
    //void Clear();
    //static double simi3_range;
    
//    enum CsvType {txt, hex};
    //void FromCsv(const QStringList& lines, FriendlyRGB::CsvType);
    //bool Add(byte r, byte g, byte b, ApiHelper * = nullptr);
    //bool isFriendly(byFriendlyRGBte r, byte g, byte b) const;
//    bool isFriendly(const QString &l) const;
//    bool isFriendly(FriendlyRGB p0, FriendlyRGB p1, FriendlyRGB p2, byte r, byte g, byte b);
//    bool isFriendly(int i) const;
//    bool Add(int i);
    //cv::Vec3b color();
    //QList<FriendlyRGB> GetAll();
    //FriendlyRGB GetMostColor(bool *);
    //FriendlyRGB GetAverageColor();


    static const int OK = 1;
    static const int OK_ADDED = 2;
    static const int OK_ADDED_NORMALIZED = 3;
    static const int OK_NORMALIZED = 4;
    static const int NOTINRANGE = -1;
    static const int DARK = -2;
    static const int LIGHT = -3;
    static const int GRAY = -4;
    static const int NOTSIMI = -5;

    //int TryAdd(byte r, byte g, FriendlyRGBbyte b, float d, bool isForced, bool isNorm,  qreal* rng, ApiHelper *, int );
    //int TryAdd2(byte r, byte g, byte b,  qreal* rng, int*, bool isVerbose = false);
//    static bool isDark(byte r, byte g, byte b, qreal* dd);
//    static bool isLight(byte r, byte g, byte b, qreal* dd);
//    static bool isGray(byte r, byte g, byte b, qreal* d);
    //static qreal _graylevel;

//    struct RGBR
//    {
//        public:
//            qreal rg, rb, gb;

//        RGBR(qreal r, qreal g, qreal b)
//        {
//            rg = (qreal)r / ((qreal)g+1);
//            rb = (qreal)r / ((qreal)b+1);
//            gb = (qreal)g / ((qreal)b+1);
//        }
//    };
    //bool isSimilar(qreal r, qreal g, qreal b, bool isForced, qreal* aout);
    //bool isSimilar2(qreal r, qreal g, qreal b);
//    bool isSimilar3(qreal r, qreal g, qreal b, bool isForced, qreal* aout);
    //bool isSimilar3(qreal r, qreal g, qreal b, qreal range, bool isForced, qreal* aout);

//    bool isNear(const RGBR &r, const RGBR &r2, qreal p);
//    bool near(qreal n, qreal n0, qreal mp);
    //static byte ToByte(qreal a);
    //bool Normalize(ApiHelper *h = nullptr);
//    FriendlyRGB GetDarkest(bool *);
//    FriendlyRGB GetLightest(bool *);
//    static bool isNotInRange(byte r, byte g, byte b);
    //QString ToCSV(bool = false);
    //static QString TryAddStateToString(int i);
    //static QString ToCSVHex(int i, bool isHeader);
    //static void genetab(FriendlyColors*, int n);
    //static void save(const QString& name, FriendlyColors*, int);
    //static QString GetFileName(const QString &name, int i);
    //static int GetRYBIx(byte r, byte g, byte b, qreal range, qreal* d_min, bool isVerbose, int n);
    static QString GetName(int i);
//    static void uIranyszogXY(double p0x, double p0y, double p1x, double p1y, double *a, double *t);
//    static double uSzog(double A1, double B1);
//    static double uSzogNormalize(double d);
    //static void genetab2(FriendlyColors *fc, int n);
    //int TryAdd2(byte r, byte g, byte b, qreal *rng, int *iy, bool isVerbose, int n);
    //static int TryAddWheelN(byte r, byte g, byte b, qreal *rng, int *iy, bool isVerbose, int n);
    static int GetRYBIxWheelN(CIEDE2000::LAB l, double* d_min, int n);

};

#endif // FRIENDLYCOLORS_H
