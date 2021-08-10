#include "ciede2000.h"
#include "friendlyrgb.h"
#include "geomath.h"
#include <QtMath>

#include <QRegularExpression>

/*RGB*/

const FriendlyRGB FriendlyRGB::BLACK = FriendlyRGB(0, 0, 0);
const FriendlyRGB FriendlyRGB::WHITE = FriendlyRGB(255, 255, 255);

const FriendlyRGB FriendlyRGB::GRAY18 = FriendlyRGB(124, 124, 124);
const FriendlyRGB FriendlyRGB::MIDGRAY = FriendlyRGB(128, 128, 128);
const FriendlyRGB FriendlyRGB::LIGHTGRAY = FriendlyRGB(211, 211, 211); //https://www.w3schools.com/colors/colors_shades.asp

const FriendlyRGB FriendlyRGB::RED = FriendlyRGB(255, 0, 0);
const FriendlyRGB FriendlyRGB::GREEN = FriendlyRGB(0, 255, 0);
const FriendlyRGB FriendlyRGB::BLUE = FriendlyRGB(0, 0, 255);

const FriendlyRGB FriendlyRGB::YELLOW = FriendlyRGB(255, 255, 0);
const FriendlyRGB FriendlyRGB::CYAN = FriendlyRGB(0, 255, 255);
const FriendlyRGB FriendlyRGB::MAGENTA = FriendlyRGB(255, 0, 255);

const FriendlyRGB FriendlyRGB::ORANGE = FriendlyRGB(255, 128, 0);
const FriendlyRGB FriendlyRGB::CHARTEUSE = FriendlyRGB(128, 255, 0);
const FriendlyRGB FriendlyRGB::SPRINGGREEN = FriendlyRGB(0, 255, 128);
const FriendlyRGB FriendlyRGB::AZURE = FriendlyRGB(0, 128, 255);
const FriendlyRGB FriendlyRGB::VIOLET = FriendlyRGB(128, 0, 255);
const FriendlyRGB FriendlyRGB::ROSE = FriendlyRGB(255, 0, 128);


const FriendlyRGB FriendlyRGB::WheelColorsRGB[] = {
    RED,GREEN,BLUE,
    YELLOW,CYAN,MAGENTA,
    ORANGE,CHARTEUSE,SPRINGGREEN,AZURE,VIOLET,ROSE
};

const int FriendlyRGB::WheelColorsRGBLen = std::extent<decltype(WheelColorsRGB)>();

/*RYB*/
const FriendlyRGB FriendlyRGB::RYB_RED = FriendlyRGB(QStringLiteral("FE2712"));
const FriendlyRGB FriendlyRGB::RYB_ORANGE = FriendlyRGB(QStringLiteral("FB9902"));
const FriendlyRGB FriendlyRGB::RYB_YELLOW = FriendlyRGB(QStringLiteral("FEFE33"));

const FriendlyRGB FriendlyRGB::RYB_GREEN = FriendlyRGB(QStringLiteral("66B032"));
const FriendlyRGB FriendlyRGB::RYB_BLUE = FriendlyRGB(QStringLiteral("0247FE"));
const FriendlyRGB FriendlyRGB::RYB_PURPLE = FriendlyRGB(QStringLiteral("8601AF"));

const FriendlyRGB FriendlyRGB::RYB_RO = FriendlyRGB(QStringLiteral("FC600A"));
const FriendlyRGB FriendlyRGB::RYB_YO = FriendlyRGB(QStringLiteral("FCCC1A"));
const FriendlyRGB FriendlyRGB::RYB_YG = FriendlyRGB(QStringLiteral("B2D732"));
const FriendlyRGB FriendlyRGB::RYB_BG = FriendlyRGB(QStringLiteral("347C98"));
const FriendlyRGB FriendlyRGB::RYB_BP = FriendlyRGB(QStringLiteral("4424D6"));
const FriendlyRGB FriendlyRGB::RYB_RP = FriendlyRGB(QStringLiteral("C21460"));

const FriendlyRGB FriendlyRGB::WheelColorsRYB[] = {
    //0     1         2
    RYB_RED,RYB_GREEN,RYB_BLUE
    //3         4          5
    ,RYB_YELLOW,RYB_ORANGE,RYB_PURPLE
    //6     7      8      9      10     11
    ,RYB_RO,RYB_YO,RYB_YG,RYB_BG,RYB_BP,RYB_RP
};

const QString FriendlyRGB::WheelColorsRYBNames[] = {
    "RYB_RED","RYB_GREEN","RYB_BLUE",
    "RYB_YELLOW","RYB_ORANGE","RYB_PURPLE",
    "RYB_RO","RYB_YO","RYB_YG","RYB_BG","RYB_BP","RYB_RP"
};

const QString FriendlyRGB::WheelColorsRYBHumNames[] = {
    "Red","Green","Blue",
    "Yellow","Orange","Purple",
    "Vermillion","Amber","Chartreuse","Teal","Violet","Magenta"
};

const int FriendlyRGB::WheelColorsRYBLen = std::extent<decltype(WheelColorsRYB)>();

FriendlyRGB::FriendlyRGB()
{
    r=g=b=0;
}

FriendlyRGB::FriendlyRGB(byte rr, byte gg, byte bb)
{
    r = rr;
    g = gg;
    b = bb;
}

FriendlyRGB::FriendlyRGB(const QString& h)
{
    bool ok;
    auto c = FromCSV(h, CsvType::hex, &ok);
    r = c.r;
    g = c.g;
    b = c.b;
}

auto FriendlyRGB::FromCSV(QString str, CsvType ltype, bool *isok) -> FriendlyRGB
{
    *isok = false;
    if(str.isEmpty()) return {0,0,0};

    static QRegularExpression hexMatcher(QStringLiteral("[#$]?([0-9a-fA-F]{6})"), QRegularExpression::CaseInsensitiveOption);
    auto m = hexMatcher.match(str);
    if(m.hasMatch()) { str= m.captured(1); ltype= FriendlyRGB::CsvType::hex;}

    switch(ltype)
    {
        case CsvType::txt:
        {
            QStringList s;
            s = str.split(';');
            if (s.length() < 3) return {0,0,0};
            bool ok;
            byte r = static_cast<byte>(s[0].toInt(&ok));
            if(!ok)  return {0,0,0};
            byte g = static_cast<byte>(s[1].toInt(&ok));
            if(!ok) return {0,0,0};
            byte b = static_cast<byte>(s[2].toInt(&ok));
            if(!ok) return {0,0,0};
            *isok = true;
            return {r,g,b};
        }
        case CsvType::hex:
        {
            if (str.length() < 6) return {0,0,0};
            bool ok;
            int i = str.toInt(&ok, 16);
            if(!ok)  return {0,0,0};
            *isok = true;
            return FromInt(i);
        }
    }    
    return{};
}

auto FriendlyRGB::FromInt(int i) -> FriendlyRGB
{
    auto b = static_cast<byte>(i);
    auto g = static_cast<byte>(i>>8);
    auto r = static_cast<byte>(i>>16);

    return {r, g, b};
}

FriendlyRGB FriendlyRGB::FromFriendlyInt(int i)
{
    auto b = static_cast<byte>(i << 4);
    auto g = static_cast<byte>(i >> 4);
    auto r = static_cast<byte>(i >>12);

    return FriendlyRGB(r, g, b);
}

int FriendlyRGB::ToFriendlyInt(byte r, byte g, byte b){
    return ToFriendlyInt(r<<16 | g<<8 | b);
}

auto FriendlyRGB::ToFriendlyInt(int i) -> int{
    return (i & 0b111100001111000011110000)>>4;
}

auto FriendlyRGB::GetName(int i) -> QString
{
    if(i<0) return QLatin1String("");
    if(i>FriendlyRGB::WheelColorsRYBLen) return "";
    return FriendlyRGB::WheelColorsRYBHumNames[i];
}

auto FriendlyRGB::GetRYBIxWheelN(byte r, byte g, byte b, double* d_min, int n) -> int
{
    if(n>FriendlyRGB::WheelColorsRYBLen) n = FriendlyRGB::WheelColorsRYBLen;
    CIEDE2000::LAB wheel_lab[FriendlyRGB::WheelColorsRYBLen];
    double alphas[FriendlyRGB::WheelColorsRYBLen]; //NOLINT

    for(int i=0;i<FriendlyRGB::WheelColorsRYBLen;i++)
    {
        auto c = FriendlyRGB::WheelColorsRYB[i]; //NOLINT
        //        auto c = FriendlyRGB::WheelColors12[i];

        auto lab_c = FriendlyRGB::toLab(c.r, c.g, c.b);
        wheel_lab[i] = lab_c; //NOLINT
        //        zInfo(QStringLiteral("%1: a:%2, b:%3").arg(i).arg(lab_c.a).arg(lab_c.b));
        double a, t;

        GeoMath::uIranyszogXY(0,0,lab_c.a, lab_c.b, &a, &t);
        alphas[i]=a; // NOLINT

        //auto ar = qRadiansToDegrees(a);

        //        zInfo(QStringLiteral("%1(%5): a:%2, b:%3 - a:%4")
        //                  .arg(i).arg(lab_c.a).arg(lab_c.b).arg(ar)
        //                  .arg(FriendlyRGB::WheelColorsRYBNames[i]));
    }

    //bool isSimple=false;
    auto l0 = FriendlyRGB::toLab(r, g, b);
    double a0, t0;
    int ix = -1;
    GeoMath::uIranyszogXY(0,0,l0.a, l0.b, &a0, &t0);
    if(t0>25)
    {
        *d_min = std::numeric_limits<double>::max();

        for(int i=0;i<n;i++)
        {
            double d1 = a0-alphas[i];
            auto d2 = GeoMath::uSzogNormalize(d1);
            auto d = abs(d2);

            if(d<*d_min)
            {
                *d_min=d;
                ix=i;
            }
        }       
    }
    return ix;
}

auto FriendlyRGB::toLab()->CIEDE2000::LAB
{
    return toLab(r,g,b);
}

//https://www.easyrgb.com/en/math.php
//https://www.colourphil.co.uk/lab_lch_colour_space.shtml
CIEDE2000::LAB FriendlyRGB::toLab(byte sR, byte sG, byte sB)
{
    //sR, sG and sB (Standard RGB) input range = 0 ÷ 255
    //X, Y and Z output refer to a D65/2° standard illuminant.

    auto var_R = sR / 255.;
    auto var_G = sG / 255.;
    auto var_B = sB / 255.;

    if ( var_R > 0.04045 )
        var_R = qPow((( var_R + 0.055 ) / 1.055 ) , 2.4);
    else
        var_R = var_R / 12.92;
    if ( var_G > 0.04045 )
        var_G = qPow((( var_G + 0.055 ) / 1.055 ) , 2.4);
    else
        var_G = var_G / 12.92;
    if ( var_B > 0.04045 )
        var_B = qPow((( var_B + 0.055 ) / 1.055 ) , 2.4);
    else
        var_B = var_B / 12.92;

    var_R = var_R * 100.;
    var_G = var_G * 100.;
    var_B = var_B * 100.;

    auto X = var_R * 0.4124 + var_G * 0.3576 + var_B * 0.1805;
    auto Y = var_R * 0.2126 + var_G * 0.7152 + var_B * 0.0722;
    auto Z = var_R * 0.0193 + var_G * 0.1192 + var_B * 0.9505;

    //Reference-X, Y and Z refer to specific illuminants and observers.
    //Common reference values are available below in this same page.

    auto Reference_X = 100.;
    auto Reference_Y = 100.;
    auto Reference_Z = 100.;

    auto var_X = X / Reference_X;
    auto var_Y = Y / Reference_Y;
    auto var_Z = Z / Reference_Z;

    if ( var_X > 0.008856 )
        var_X = qPow(var_X , ( 1./3 ));
    else
        var_X = ( 7.787 * var_X ) + ( 16. / 116 );
    if ( var_Y > 0.008856 )
        var_Y = qPow(var_Y , ( 1./3 ));
    else
        var_Y = ( 7.787 * var_Y ) + ( 16. / 116 );

    if ( var_Z > 0.008856 )
        var_Z = qPow(var_Z , ( 1./3 ));
    else
        var_Z = ( 7.787 * var_Z ) + ( 16. / 116 );

    auto L = ( 116 * var_Y ) - 16;
    auto a = 500 * ( var_X - var_Y );
    auto b = 200 * ( var_Y - var_Z );

    return {L, a, b};
}

QString FriendlyRGB::GetFileName(const QString& name, int i)
{
    if(i<0) return QLatin1String("");
    if(i>FriendlyRGB::WheelColorsRYBLen) return "";
    return name+'_'+QString::number(i)+'_'+FriendlyRGB::WheelColorsRYBNames[i]+".txt";
}

