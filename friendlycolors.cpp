//#include "common/logger/log.h"
//#include "common/macrofactory/macro.h"
#include "friendlycolors.h"
#include "geomath.h"
//#include "common/helper/textfilehelper/textfilehelper.h"
//#include "opencv2/core/mat.hpp"
//#include "common/logger/log.h"
#include <QRegularExpression>
#include <QtMath>
//#include "friendlyrgb.h"

//const uint8_t FriendlyColors::_d = 16;
//const int FriendlyColors::_min_level = 70;//45;
//const QString FriendlyColors::_url = "http://172.16.1.62:8080";
//double FriendlyColors::simi3_range = 0;
//qreal FriendlyColors::_graylevel = 45;//25;//45
FriendlyColors::FriendlyColors()
{
    //_fcs = QSet<int>();

//    minr = ming = minb= UCHAR_MAX;
//    maxr = maxg = maxb = 0;
   // Clear();
    //_isMonitoring = true;
//    _graylevel = 25;//45
   // simi3_range = FriendlyRGB::ciede2000(FriendlyRGB::GREEN,FriendlyRGB::SPRINGGREEN)*1.5;

}

//void FriendlyColors::Clear()
//{
//    minr = ming = minb= UCHAR_MAX;
//    maxr = maxg = maxb = 0;
//    _fcs.clear();
//}



//void FriendlyColors::FromCsv(const QStringList& lines, FriendlyRGB::CsvType type)
//{
//    Clear();
//    if (lines.isEmpty()) return;
//    byte r, g, b;
//    bool ok;
//    QStringList s;

//    static QRegularExpression hexMatcher("[#$]?([0-9a-fA-F]{6})", QRegularExpression::CaseInsensitiveOption);
//    foreach (auto l, lines)
//    {
//        FriendlyRGB::CsvType ltype;
//        if (l.isEmpty()) continue;

//        auto m = hexMatcher.match(l);
//        if(m.hasMatch()) { l= m.captured(1); ltype= FriendlyRGB::CsvType::hex;}
//        else if (l.at(0)=='#') continue;
//        else ltype = type;

//        switch(ltype){
//        case FriendlyRGB::CsvType::txt:{
//            s = l.split(';');
//            if (s.length() < 3) continue;

//            r = static_cast<byte>(s[0].toInt(&ok));
//            if(!ok) continue;
//            g = static_cast<byte>(s[1].toInt(&ok));
//            if(!ok) continue;
//            b = static_cast<byte>(s[2].toInt(&ok));
//            if(!ok) continue;
//            Add(r, g, b);
//            break;
//        }
//        case FriendlyRGB::CsvType::hex:{

//            if (l.length() < 6) continue;
//            int i = l.toInt(&ok, 16);
////            r = static_cast<byte>(l.midRef(0, 2).toInt(&ok, 16));
////            if(!ok) continue;
////            g = static_cast<byte>(l.midRef(2, 2).toInt(&ok, 16));
////            if(!ok) continue;
////            b = static_cast<byte>(l.midRef(4, 2).toInt(&ok, 16));
////            if(!ok) continue;
//            Add(i);
//            break;
//        }
//        }


//        }
//    //}
//}

//bool FriendlyColors::Add(int i){
//    FriendlyRGB c = FriendlyRGB::FromInt(i);

////    auto fi = FriendlyRGB::ToFriendlyInt(i);

////    auto size = _fcs.size();
////    _fcs.insert(fi);
////    auto isAdded = _fcs.size()>size;

////    return isAdded;
//    auto isok =  Add(c.r, c.g, c.b);
//    return isok;
//}

//cv::Vec3b FriendlyColors::color()
//{
//    //auto i = _fcs.begin();
//    //auto a = FriendlyRGB::FromFriendlyInt(*i);
//    bool isok;
//    auto a = GetMostColor(&isok);
//    if(isok)
//    {
//        //auto a = GetAverageColor();//GetMostColor();
//        auto e = FriendlyRGB::Wheel(a);
//        return {e.r, e.g, e.b};
//    }
//    else return{a.r, a.g, a.b};
//}

//FriendlyRGB FriendlyColors::GetMostColor(bool *isok)
//{
//   if(_fcs.isEmpty())
//   {
//       *isok = false;
//       return FriendlyRGB::GRAY18;
//   }
//   FriendlyRGB drgb = FriendlyRGB::BLACK;
//   qreal dd = std::numeric_limits<qreal>::min();
//   for(auto i = _fcs.begin();i != _fcs.end();i++)
//   {
//       auto c = FriendlyRGB::FromFriendlyInt(*i);
//       auto d = GeoMath::dpl3dRgb(c.r, c.g, c.b);
//       if (d > dd)
//       {
//           dd = d;
//           drgb = c;
//       }

//   }
//   *isok = dd!=std::numeric_limits<qreal>::min();
//   return drgb;
//}

//FriendlyRGB FriendlyColors::GetAverageColor()
//{
//   if(_fcs.isEmpty())
//       return FriendlyRGB::GRAY18;

//   int r=0, g=0, b=0, n=0;
//   for(auto i = _fcs.begin();i != _fcs.end();i++)
//   {
//       auto c = FriendlyRGB::FromFriendlyInt(*i);
//       r+=c.r; g+=c.g;b+=c.b;n++;

//   }

//   return {(byte)(r/n), (byte)(g/n), (byte)(b/n)};
//}

//QList<FriendlyRGB> FriendlyColors::GetAll()
//{
//    QList<FriendlyRGB> e;
//    for(auto i = _fcs.begin();i != _fcs.end();i++) e.append(FriendlyRGB::FromFriendlyInt(*i));
//    return e;
//}

//bool FriendlyColors::Add(byte r, byte g, byte b, ApiHelper *h)
//{
//    auto fi = FriendlyRGB::ToFriendlyInt(r, g, b);
//    if(_fcs.contains(fi)) return false;
//    auto size = _fcs.size();
//    _fcs.insert(fi);
//    auto isAdded = _fcs.size()>size;
//    if (r < minr) minr = r;
//    if (g < ming) ming = g;
//    if (b < minb) minb = b;

//    if (r > maxr) maxr = r;
//    if (g > maxg) maxg = g;
//    if (b > maxb) maxb = b;

//    if (h && isAdded)
//    {
//        auto nix = _fcs.count();
//        auto a = FriendlyRGB::FromFriendlyInt(fi);
//        auto q = QStringLiteral("n=%1&r=%2&g=%3&b=%4&d=%5").arg(nix).arg(a.r).arg(a.g).arg(a.b).arg(16);
//        h->get("add",q);
//    }

//    return isAdded;
//}

//bool FriendlyColors::isFriendly(const QString& l) const
//{
//    if (l.length() < 6) return false;
//    bool ok;
//    int a = l.toInt(&ok, 16);
//    if(!ok) return false;

//    return isFriendly(a);
//}

//bool FriendlyColors::isFriendly(FriendlyRGB p0, FriendlyRGB p1, FriendlyRGB p2, byte r, byte g, byte b)
//{
//    qreal d0 = GeoMath::Distance3d(p0.r, p0.g, p0.b, r, g, b);
//    qreal d1 = GeoMath::DistaFriendlyRGBnce3d(p1.r, p1.g, p1.b, r, g, b);
// //   qreal d2 = GeoMath::Distance3d(p2.r, p2.g, p2.b, r, g, b);

//    qreal dd0 = GeoMath::Distance3d(p0.r, p0.g, p0.b, p1.r, p1.g, p1.b);
//    qreal dd1 = GeoMath::Distance3d(p1.r, p1.g, p1.b, p2.r, p2.g, p2.b);
//    qreal dd2 = GeoMath::Distance3d(p0.r, p0.g, p0.b, p2.r, p2.g, p2.b);


//    qreal d3 = GeoMath::dpl3d(p0.r, p0.g, p0.b, p1.r, p1.g, p1.b, p2.r, p2.g, p2.b);
//    qreal dd3 = GeoMath::dpl3d(p0.r, p0.g, p0.b, p1.r, p1.g, p1.b, r, g, b);

//    //return  d0 + d1 + d2 <= dd0 + dd1 + dd2;
//    //var isok =  (d0 + d1) < (dd1 + dd2);
//    //if()
//    if(dd1<1 || dd2<1) // nincs ellipszis
//        return (d0 + d1) < (dd0*1.07);
//    else
//        return(dd3 < d3) && ((d0 + d1) < (dd1 + dd2));
//    //return isok;
//}


//bool FriendlyColors::isFriendly(byte r, byte g, byte b) const{
//    return _fcs.contains(FriendlyRGB::ToFriendlyInt(r,g,b));
//}

//bool FriendlyColors::isFriendly(int i) const{
//    return _fcs.contains(FriendlyRGB::ToFriendlyInt(i));
//}

/*****/

//const int FriendlyColors::OK = 1;
//const int FriendlyColors::NOTINRANGE = -1;
//const int FriendlyColors::DARK = -2;
//const int FriendlyColors::LIGHT = -3;
//const int GRAY = -4;
//const int SIMI = -5;

//QString FriendlyColors::TryAddStateToString(int i)
//{
//    static const QString _OK = nameof(OK);
//    static const QString _OK_ADDED = nameof(OK_ADDED);
//    static const QString _OK_ADDED_NORMALIZED = nameof(OK_ADDED_NORMALIZED);
//    static const QString _OK_NORMALIZED = nameof(OK_NORMALIZED);
//    static const QString _NOTINRANGE = nameof(NOTINRANGE);
//    static const QString _DARK = nameof(DARK);
//    static const QString _LIGHT = nameof(LIGHT);
//    static const QString _GRAY = nameof(GRAY);
//    static const QString _SIMI = nameof(NOTSIMI);

//    switch(i)
//    {
//        case OK: return _OK;
//        case OK_ADDED: return _OK_ADDED;
//        case OK_ADDED_NORMALIZED: return _OK_ADDED_NORMALIZED;
//        case OK_NORMALIZED: return _OK_NORMALIZED;
//        case NOTINRANGE: return _NOTINRANGE;
//        case DARK: return _DARK;
//        case LIGHT: return _LIGHT;
//        case GRAY: return _GRAY;
//        case NOTSIMI: return _SIMI;
//    }
//    return "not_defined";
//}

//int FriendlyColors::TryAdd(byte r, byte g, byte b, float d, bool isForced, bool isNorm, qreal *rng, ApiHelper *h, int type)
//{
//    Q_UNUSED(d)
//    if (isDark(r, g, b, rng)) return DARK; // túl sötét
//    if (isLight(r, g, b, rng)) return LIGHT; // túl világos
//    if (isGray(r, g, b, rng)) return GRAY; // nincs benne elegendő színinformáció


//    if(!_fcs.isEmpty())
//    {
//        switch(type)
//        {
//        case 1: if( !isSimilar(r, g, b, isForced, rng)) return NOTSIMI; break;
//        case 2: if( !isSimilar2(r, g, b)) return NOTSIMI; break;
//        case 3: if( !isSimilar3(r, g, b, simi3_range, true, rng)) return NOTSIMI; break;
//        }
//    }
//    bool isAdded = Add(r, g, b, h);

//    if (isAdded && isNorm) return Normalize(h)?OK_ADDED_NORMALIZED:OK_ADDED;
//    return isAdded?OK_ADDED:OK;
//}

// var st_yellow = await _cameraApi.TryAddFc2(bodyPointId, 197, 174, 91);
// miért green?
// R   G   B   Y   O   P
// 44, 19, 72, 19, 20, 75
// távolságon alapul
//int FriendlyColors::TryAdd2(byte r, byte g, byte b, qreal *rng, int *iy, bool isVerbose, int n)
//{
////    if (isDark(r, g, b, rng)) return DARK; // túl sötét
////    if (isLight(r, g, b, rng)) return LIGHT; // túl világos
////    if (isGray(r, g, b, rng)) return GRAY; // nincs benne elegendő színinformáció

//    *iy=GetRYBIxWheelN(r,g,b,rng, isVerbose, n);
//    return OK;
//}

//Szögön alapul
//int FriendlyColors::TryAddWheelN(byte r, byte g, byte b, qreal *rng, int *iy, bool isVerbose, int n)
//{
//    *iy=GetRYBIxWheelN(r,g,b,rng, isVerbose, n);
//    return OK;
//}

int FriendlyColors::GetRYBIxWheelN(CIEDE2000::LAB l0, double* d_min, int n)
{
    if(n>FriendlyRGB::WheelColorsRYBLen) n = FriendlyRGB::WheelColorsRYBLen;
    CIEDE2000::LAB wheel_lab[FriendlyRGB::WheelColorsRYBLen];
    double alphas[FriendlyRGB::WheelColorsRYBLen];

    for(int i=0;i<FriendlyRGB::WheelColorsRYBLen;i++)
    {
        auto c = FriendlyRGB::WheelColorsRYB[i];
//        auto c = FriendlyRGB::WheelColors12[i];

        auto lab_c = FriendlyRGB::toLab(c.r, c.g, c.b);
        wheel_lab[i] = lab_c;
//        zInfo(QStringLiteral("%1: a:%2, b:%3").arg(i).arg(lab_c.a).arg(lab_c.b));
        double a, t;
        GeoMath::uIranyszogXY(0,0,lab_c.a, lab_c.b, &a, &t);
        alphas[i]=a;

        //auto ar = qRadiansToDegrees(a);

//        zInfo(QStringLiteral("%1(%5): a:%2, b:%3 - a:%4")
//                  .arg(i).arg(lab_c.a).arg(lab_c.b).arg(ar)
//                  .arg(FriendlyRGB::WheelColorsRYBNames[i]));
    }

    //bool isSimple=false;
    //auto l0 = FriendlyRGB::toLab(r, g, b);
    double a0, t0;
    int ix = -1;
    GeoMath::uIranyszogXY(0,0,l0.a, l0.b, &a0, &t0);
    if(t0>25)
    {
        *d_min = std::numeric_limits<double>::max();

        //ix = 0 ; a lyukat nézzük

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
//      if(ix>-1)
//      {
//          fc[ix].Add(r, g, b, nullptr);
//          st+=' '+QString::number(ix)+" ok";
//      }
    }
    return ix;
}


//int FriendlyColors::GetRYBIx(byte r, byte g, byte b, qreal range, qreal* d_min, bool isVerbose, int n)
//{
//    if(n>FriendlyRGB::WheelColorsRYBLen) n = FriendlyRGB::WheelColorsRYBLen;
//    bool isSimple=false;
//    auto l0 = FriendlyRGB::toLab(r, g, b);

//    *d_min = DBL_MAX;

//    int ix = -1;
//    for(int i=0;i<n;i++)
//    {
//        auto c = FriendlyRGB::WheelColorsRYB[i];
//        auto c_lab = FriendlyRGB::toLab(c.r, c.g, c.b);
//        auto d = FriendlyRGB::ciede2000(l0, c_lab);
//        if(isVerbose)
//        {
//            zInfo(QStringLiteral("%1:d=%2").arg(i).arg(d));
//        }
//        if(isSimple)
//        {
//            if(d<*d_min)
//            {
//                *d_min=d;
//                ix=i;
//            }
//        }
//        else
//        {

//        //if(d<d_min)
//            auto dist = d-*d_min;
//            if(dist<range)
//            {
//                /*if(i>=6) // kevert kevert
//                {
//                    *d_min=d;
//                    ix=i;
//                }
//                else*/
//                if(i>=3) // aktuális kevert
//                {
//                    if(ix==-1)//nincs korábbi találat, az aktuális lesz a találat
//                    {
//                        *d_min=d;
//                        ix=i;
//                    }
//                    else if(ix<3) // a korábbi sima, a kevert nyer , azaz az aktuális
//                    {
//                        *d_min=d;
//                        ix=i;
//                    }
//                    else // mindegyik kevert, a távolság dönt
//                    {
//                        if(d<*d_min)
//                        {
//                            *d_min=d;
//                            ix=i;
//                        }
//                    }

//                }
//                else // az aktuális sima
//                {
//                    if(ix==-1)//nincs korábbi találat, az aktuális lesz a találat
//                    {
//                        *d_min=d;
//                        ix=i;
//                    }
//                    else if(ix<3)//és a korábbi sima, a távolság dönt
//                    {
//                        if(d<*d_min)
//                        {
//                            *d_min=d;
//                            ix=i;
//                        }
//                    }
//                    else //és a korábbi kevert, a kevert nyer, azaz marad
//                    {

//                    }
//                }
//            }
//        }//end else notsimple
//    } //endfor;

//    if(isVerbose)
//    {
//        zInfo(QStringLiteral("%1:d_min=%2").arg(ix).arg(*d_min))
//    }
//    return ix;
//}


//bool FriendlyColors::Normalize(ApiHelper *h)
//{
//   if (_fcs.count() == 0) return false;
//   if (minr >= maxr) return false;
//   if (ming >= maxg) return false;
//   if (minb >= maxb) return false;

//   int minr0 = minr >> 4;
//   int maxr0 = maxr >> 4;
//   int ming0 = ming >> 4;
//   int maxg0 = maxg >> 4;
//   int minb0 = minb >> 4;
//   int maxb0 = maxb >> 4;

//   bool is_dark, is_light, is_color;
//   FriendlyRGB p0 = GetDarkest(&is_dark);
//   FriendlyRGB p1 = GetLightest(&is_light);
//   FriendlyRGB p2 = GetMostColor(&is_color);
//   if (!is_dark || !is_light || !is_color) return false;

//   bool e = false;
//   byte r2, g2, b2;
//   for (int r1 = minr0; r1 <= maxr0; r1++)
//   {
//       r2 = ToByte(r1<<4);
//       for (int g1 = ming0; g1 <= maxg0; g1++)
//       {
//           g2 = ToByte(g1<<4);
//           for (int b1 = minb0; b1 <= maxb0; b1++)
//           {
//               b2 = ToByte(b1<<4);
//               if (!isFriendly(p0, p1, p2, r2, g2, b2)) continue;
//               if (isNotInRange(r2, g2, b2)) continue;
//               qreal rng, rng2;
//               if (isGray(r2, g2, b2, &rng)) continue;
//               if (!isSimilar(r2, g2, b2, true, &rng2)) continue;
//               if(Add(r2, g2, b2, h))
//                   e=true; // size megnövekedett
//           }
//       }
//   }
//   return e;
//}

//byte FriendlyColors::ToByte(qreal i){
//    if (i >= 255) return 255;
//    if (i <= 0) return 0;
//    return (byte)i;
//}

//bool FriendlyColors::isDark(byte r, byte g, byte b, qreal* dd)
//{
//    *dd = GeoMath::Distance3d(0, 0, 0, (qreal)r, (qreal)g, (qreal)b);
//    return *dd < _min_level;
//}

//bool FriendlyColors::isLight(byte r, byte g, byte b, qreal* dl)
//{
//    *dl = GeoMath::Distance3d(255, 255, 255, (qreal)r, (qreal)g, (qreal)b);
//    return *dl < _min_level;
//}

//bool FriendlyColors::isGray(byte r, byte g, byte b, qreal* d)
//{
//    *d = GeoMath::dpl3dRgb(r, g, b);
//    return *d < _graylevel;// 30;//80;//60
//}


//bool FriendlyColors::isSimilar(qreal r, qreal g, qreal b, bool isForced, qreal* aout)
//{
//    if (_fcs.count() == 0) { *aout = -1; return false; }
//    RGBR r0(r, g, b);
//    bool isn;

//    for(auto i = _fcs.begin();i != _fcs.end();i++)
//    {
//        int ii = *i;
//        auto fc = FriendlyRGB::FromFriendlyInt(ii);

//        //zInfo(QStringLiteral("isSimilar: r:%1 g:%2 b:%3 - ii7%4 rr:%5 gg:%6 bb:%7").arg(r).arg(g).arg(b).arg(ii).arg(fc.r).arg(fc.g).arg(fc.b));
//        RGBR r1(fc.r, fc.g, fc.b);
//        isn = isNear(r0, r1, isForced ? 40 : 8);//8 //r0 a megadott, r1 a vizsgált

//        if (isn) return true;// van olyan szín amihez közel esik
//    }
//    return false;
//}

//bool FriendlyColors::isSimilar2(qreal r, qreal g, qreal b)
//{
//    if (_fcs.count() == 0) return false;

//    auto a = _fcs.begin();
//    auto fc = FriendlyRGB::FromFriendlyInt(*a);
//    auto wc = FriendlyRGB::WheelIx(fc);

//    auto fc0 = FriendlyRGB(r,g,b);
//    auto wc0 = FriendlyRGB::WheelIx(fc0);

//    if(wc==-1) return false;
//    if(wc0==-1) return false;
//    return wc==wc0;
//}


//bool FriendlyColors::isSimilar3(qreal r, qreal g, qreal b, qreal range,
//                                bool isForced, qreal* aout)
//{
//    Q_UNUSED(isForced)
//    if (_fcs.count() == 0) { *aout = -1; return false; }
//    auto l0 = FriendlyRGB::toLab(r, g, b);

////    bool isn;

//    qreal d_min = 12000;
//    for(auto i = _fcs.begin();i != _fcs.end();i++)
//    {
//        int ii = *i;
//        auto fc = FriendlyRGB::FromFriendlyInt(ii);
//        auto l = fc.toLab();

//        auto d = FriendlyRGB::ciede2000(l, l0);

//        *aout = d;
//        if(d<d_min)d_min = d;
//        if(d<=range)
//            return true;// van olyan szín amihez közel esik
//    }
//    return false;
//}

//bool FriendlyColors::near(qreal n, qreal n0, qreal mp)
//{
//    qreal nmin = n0 * (1 - (mp / 100));
//    qreal nmax = n0 * (1 + (mp / 100));
//    return nmin < n && n < nmax;
//}

//bool FriendlyColors::isNear(const RGBR &r, const RGBR &r2, qreal p)
//{
//    return
//        near(r2.rg, r.rg, p) &&
//        near(r2.rb, r.rb, p) &&
//        near(r2.gb, r.gb, p);
//}




//FriendlyRGB FriendlyColors::GetDarkest(bool *isok)
//{
//  FriendlyRGB drgb = FriendlyRGB::WHITE;// = null;
//  qreal dd = std::numeric_limits<qreal>::max();//qreal.MaxValue;
//  //foreach (var a in GetAll())
//  for(auto a = _fcs.begin();a != _fcs.end();a++)
//  {
//      auto fc = FriendlyRGB::FromFriendlyInt(*a);
//      auto d = GeoMath::Distance3d(0, 0, 0, (qreal)(fc.r), (qreal)(fc.g), (qreal)(fc.b));
//      if (d < dd)
//      {
//          dd = d;
//          drgb = fc;
//      }
//  }
//  *isok = dd != std::numeric_limits<qreal>::max();
//  return drgb;
//}

//FriendlyRGB FriendlyColors::GetLightest(bool *isok)
//{
//    FriendlyRGB drgb = FriendlyRGB::BLACK;// = null;
//    qreal dd = std::numeric_limits<qreal>::max();//qreal.MaxValue;
//    for(auto a = _fcs.begin();a != _fcs.end();a++)
//    {
//        auto fc = FriendlyRGB::FromFriendlyInt(*a);
//        auto d = GeoMath::Distance3d(255, 255, 255, fc.r, fc.g, fc.b);
//        if (d < dd)
//        {
//            dd = d;
//            drgb = fc;
//        }
//    }
//    *isok = dd != std::numeric_limits<qreal>::max();
//    return drgb;
//}

//bool FriendlyColors::isNotInRange(byte r, byte g, byte b)
//{
//    auto dd = GeoMath::Distance3d(0, 0, 0, r, g, b);
//    auto dl = GeoMath::Distance3d(255, 255, 255, r, g, b);
//    return dd < _min_level || dl < _min_level;
//}

//QString FriendlyColors::ToCSV(bool isHeader)
//{
//    //static const QString h_r("r");
//    //static const QString h_g("g");
//    //static const QString h_b("b");

//    if(isHeader) return QStringLiteral("#rrggbb...");
//    QString e;
//    for(auto i = _fcs.begin();i!=_fcs.end();i++)
//    {
//        if(!e.isEmpty()) e+='\n';
//        auto c = FriendlyRGB::FromFriendlyInt(*i);
//        e+=c.ToCsv(FriendlyRGB::hex);
//    }

//    return e;
//}

//void FriendlyColors::genetab2(FriendlyColors* fc, int n)
//{
//    QStringList sts;
//    zTrace()
//    qreal rng = 16;
//    byte r=0,g=0,b=0;
//    //for(int r = 0;r<256;r+=16)
//    do {
//        //for(int g = 0;g<256;g+=16)
//        do {
//            //for(int b = 0;b<256;b+=16)
//            do {
//                auto st = QString("#%1%2%3").arg(r, 2, 16, QChar('0')).arg(g, 2, 16, QChar('0')).arg(b, 2, 16, QChar('0'));

//                int ix = GetRYBIxWheelN(r,g,b, &rng, n);
//                if(ix>-1)
//                {
//                    fc[ix].Add(r, g, b, nullptr);
//                    st+=' '+QString::number(ix)+" ok";
//                }
//                sts.append(st);
//                //zInfo(st)
//                b+=16;
//            }while(b);
//            g+=16;
//        }while(g);
//        r+=16;
//    }while(r);
//    com::helper::TextFileHelper::save(sts.join('\n'), "fc.txt");
//}



//QString FriendlyColors::GetFileName(const QString& name, int i)
//{
//    if(i<0) return QLatin1String("");
//    if(i>FriendlyRGB::WheelColorsRYBLen) return "";
//    return name+'_'+QString::number(i)+'_'+FriendlyRGB::WheelColorsRYBNames[i]+".txt";
//}

QString FriendlyColors::GetName(int i)
{
    if(i<0) return QLatin1String("");
    if(i>FriendlyRGB::WheelColorsRYBLen) return "";
    return FriendlyRGB::WheelColorsRYBHumNames[i];
}


//void FriendlyColors::save(const QString& name, FriendlyColors* fcs, int n)
//{
//    if(n<FriendlyRGB::WheelColorsRYBLen) return;
//    for(int i=0;i<n;i++)
//    {
//        QString txt = fcs[i].ToCSV();
//        auto fn = GetFileName(name, i);//name+'_'+QString::number(i)+'_'+l[i]+".txt"
//        com::helper::TextFileHelper::save(txt, fn);
//        zInfo(QLatin1String("saved: ")+fn);
//    }
//}

//void FriendlyColors::uIranyszogXY(double p0x, double p0y, double p1x, double p1y, double *a, double *t){
//    double A, B;

//    A=p1y-p0y; // ez most irányvektor!!!
//    B=p1x-p0x;
//    *a=uSzog(A, B)-M_PI_2;
//    *t=hypot(A, B);
//}

//#define M_2PI (M_PI+M_PI)
//#define M_15PI (M_PI+M_PI_2)

//double FriendlyColors::uSzog(double A1, double B1){
//    if(A1==0 && B1>0) return 0;
//    if(A1>0 && B1==0) return M_PI_2;
//    if(A1==0 && B1<0) return M_PI;
//    if(A1<0 && B1==0) return M_15PI;
//    if(A1>0 && B1>0) return atan(A1/B1);
//    if(B1<0 && A1!=0) return M_PI+atan(A1/B1);
//    return M_2PI+atan(A1/B1);
//}

//double FriendlyColors::uSzogNormalize(double d)
//{
//    auto a = fmod(d, M_2PI);
//    if(a<-M_PI) return M_2PI-a;
//    if(a>M_PI) return a-M_2PI;
//    return a;
//}


/*
void FriendlyColors::genetab(FriendlyColors* fc)
{
    QStringList sts;

    double d0 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_RED,FriendlyRGB::RYB_RO); //11
    double d1 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_RO,FriendlyRGB::ORANGE); //10
    double d2 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_ORANGE,FriendlyRGB::RYB_YO);
    double d3 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_YO,FriendlyRGB::RYB_YELLOW);
    double d4 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_YELLOW,FriendlyRGB::RYB_YG);
    double d5 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_YG,FriendlyRGB::RYB_GREEN);
    double d6 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_GREEN,FriendlyRGB::RYB_BG);
    double d7 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_BG,FriendlyRGB::RYB_BLUE);
    double d8 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_BLUE,FriendlyRGB::RYB_BP);
    double d9 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_BP,FriendlyRGB::RYB_PURPLE);
    double d10 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_PURPLE,FriendlyRGB::RYB_RP);
    double d11 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_RP,FriendlyRGB::RYB_RED);

    double xd0 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_RO,FriendlyRGB::RYB_RED); //11

//        d0	11.052325441796322	double r -ro
//        d1	9.8393915696264802	double ro - o
//        d2	18.01540016104267	double o - yo
//        d3	14.341563536543763	double
//        d4	12.721196448345738	double
//        d5	14.102840768632012	double
//        d6	46.495930482487758	double
//        d7	21.307679746280037	double
//        d8	10.078014157575749	double
//        d9	11.86919733581518	double
//        d10	24.161460825805737	double
//        d11	28.630602688917524	double rp - r

    //            R   G   B   Y   O   P   RO  YO  YG  BG  BP RP
    //double DD[] ={29, 26, 19, 26, 29, 19, 11};

    double b0 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_YG,FriendlyRGB::RYB_RED); //11
    double b1 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_YG,FriendlyRGB::RYB_RO); //10
    double b2 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_YG,FriendlyRGB::RYB_ORANGE);
    double b3 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_YG,FriendlyRGB::RYB_YO);
    double b4 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_YG,FriendlyRGB::RYB_YELLOW);
    double b5 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_YG,FriendlyRGB::RYB_YG);
    double b6 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_YG,FriendlyRGB::RYB_GREEN);
    double b7 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_YG,FriendlyRGB::RYB_BG);
    double b8 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_YG,FriendlyRGB::RYB_BLUE);
    double b9 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_YG,FriendlyRGB::RYB_BP);
    double b10 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_YG,FriendlyRGB::RYB_PURPLE);
    double b11 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_YG,FriendlyRGB::RYB_RP);

//
//        b0	65.354795429133532	double
//        b1	54.076058599746602	double
//        b2	34.856573617235995	double
//        b3	18.594494085975409	double
//        b4	12.721196448345738	double //Y
//        b5	0	double //YG
//        b6	14.102840768632012	double //G
//        b7	54.660189136405805	double //BG
//        b8	78.371088949700237	double
//        b9	98.059797594081957	double
//        b10	96.372123910382669	double
//        b11	80.078718167925274	double

//

    double g0 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_GREEN,FriendlyRGB::RYB_RED); //11
    double g1 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_GREEN,FriendlyRGB::RYB_RO); //10
    double g2 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_GREEN,FriendlyRGB::RYB_ORANGE);
    double g3 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_GREEN,FriendlyRGB::RYB_YO);
    double g4 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_GREEN,FriendlyRGB::RYB_YELLOW);
    double g5 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_GREEN,FriendlyRGB::RYB_YG);
    double g6 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_GREEN,FriendlyRGB::RYB_GREEN);
    double g7 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_GREEN,FriendlyRGB::RYB_BG);
    double g8 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_GREEN,FriendlyRGB::RYB_BLUE);
    double g9 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_GREEN,FriendlyRGB::RYB_BP);
    double g10 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_GREEN,FriendlyRGB::RYB_PURPLE);
    double g11 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_GREEN,FriendlyRGB::RYB_RP);


    double bg0 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_BG,FriendlyRGB::RYB_RED); //11
    double bg1 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_BG,FriendlyRGB::RYB_RO); //10
    double bg2 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_BG,FriendlyRGB::RYB_ORANGE);
    double bg3 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_BG,FriendlyRGB::RYB_YO);
    double bg4 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_BG,FriendlyRGB::RYB_YELLOW);
    double bg5 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_BG,FriendlyRGB::RYB_YG);
    double bg6 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_BG,FriendlyRGB::RYB_GREEN);
    double bg7 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_BG,FriendlyRGB::RYB_BG);
    double bg8 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_BG,FriendlyRGB::RYB_BLUE);
    double bg9 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_BG,FriendlyRGB::RYB_BP);
    double bg10 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_BG,FriendlyRGB::RYB_PURPLE);
    double bg11 = FriendlyRGB::ciede2000(FriendlyRGB::RYB_BG,FriendlyRGB::RYB_RP);

    zInfo("genetab");
//    for(int i=0;i<n;i++)
//    {
//        auto c = FriendlyRGB::WheelColorsRYB[i];
//        wheel_lab[i] = FriendlyRGB::toLab(c.r, c.g, c.b);
//    }

    qreal rng = 16;
    for(int r = 0;r<256;r+=16)
    {
        for(int g = 0;g<256;g+=16)
        {
            for(int b = 0;b<256;b+=16)
            {
                auto st = QString("#%1%2%3").arg(r, 2, 16, QChar('0')).arg(g, 2, 16, QChar('0')).arg(b, 2, 16, QChar('0'));
                if(isDark((byte)r, (byte)g, (byte)b, &rng))
                {
                    st+=" DARK";
                    sts.append(st);
                    continue;
                }

                if(isLight((byte)r, (byte)g, (byte)b, &rng))
                {
                    st+=" LIGHT";
                    sts.append(st);
                    continue;
                }

                if (isGray((byte)r, (byte)g, (byte)b, &rng))
                {
                    st+=" GRAY";
                    sts.append(st);
                    continue;
                }

                //auto l0 = FriendlyRGB::toLab(r, g, b);
                //QString st = QString::number(r,16)+QString::number(g,16)+QString::number(b,16);
                //qreal d_min;
                int ix = GetRYBIx(r,g,b,2,&rng, false);
//                qreal range = 2;
//                qreal d_min = 12000;
//                int ix = -1;
//                for(int i=0;i<FriendlyRGB::WheelColorsRYBLen;i++)
//                {
//                    auto d = FriendlyRGB::ciede2000(l0, wheel_lab[i]);
////                    if(d<d_min)
////                    {
////                        d_min=d;
////                        ix=i;
////                    }
//                    auto dist = d-d_min;
//                    if(dist<range) // ha nem egyértelműen külömböznek, hanem átmenetet képeznek a két szín között,
//                    {
//                        if(i>=3)  // akkor a kevert szín javára döntünk
//                        {
//                            d_min=d;
//                            ix=i;
//                        }
//                        else
//                        {genetab
//                            if(d<d_min)
//                            {
//                                d_min=d;
//                                ix=i;
//                            }
//                        }
//                    }
//                }
                if(ix>-1)
                {
//                    if(D>0)
//                    {
//                        if (d_min<DD[ix])
//                        {
//                            fc[ix].Add(r, g, b, nullptr);
//                            st+=' '+QString::number(ix)+" ok";
//                        }

//                    }
//                    else
//                    {
                        fc[ix].Add(r, g, b, nullptr);
                        st+=' '+QString::number(ix)+" ok";
                    //}
                }
                //zInfo(st);
                sts.append(st);
            }
        }
    }
    com::helper::TextFileHelper::save(sts.join("\n"), "fc.txt");
    return ;
}


http://www.guiart.com/guien4.htm
5-14 for a* and within 10-24


c8ac98,cbab99,caab96,cbac95,c9ad95
c8a995,c9a996,c8a994,c7a992,c5a991
c7a896,c5a691,c8a793,c7a792,c6a891
c4a890,c7a694,caa596,c2a38e,c3a28f
c2a38f,c2a48d,c0a48d

c3a38f,c5a192,c6a195,c6a096,c6a098
be9d86,be9c87,be9d88,bc9d87,bd9f87
bf9f8c,c29c8c,c39a8d,c39a8e,c39990
bb9881,bd9983,ba9982,b99980,b89a7e
bb9983,bd9584,c29787

c19487,c1958c,b69279,b5927b,b49277
b39276,b19175,b7927b,b68d7b,b98d7e
bc8d80,be9186,b1886c,af8870,b0896e
ad8b6f,aa8b6d,b3886e,b38672,b58576
b58678,a87f64,a98167

a68266,a58163,a38264,ab8167,ac7e69
ae7f6e,ad7e71,a0765a,a0795f,9b775d
99795d,a2785d,a5755f,a57461,946c51
986f54,906f54,8f7054,976c52,9a6b54
514239,53433a,544239

846349,866048,8c624e,895f4d,775741
795945,775642,785444,775445,654d3e
644b3c,634b3f,664c41,63483e,544338
996a58,876249,89634c

skincolors


//void FriendlyColors::genetab(FriendlyColors* fc, int n)
//{
//    zTrace();
//    QStringList sts;

//    qreal rng = 16;
//    //for(byte r = 0;r<256;r+=16)
//    byte r=0,g=0,b=0;
//    do {
//        //for(int g = 0;g<256;g+=16)
//        do {
//            //for(int b = 0;b<256;b+=16)
//            do {
//                auto st = QString("#%1%2%3").arg(r, 2, 16, QChar('0')).arg(g, 2, 16, QChar('0')).arg(b, 2, 16, QChar('0'));
//                if(isDark(r, g, b, &rng))
//                {
//                    st+=QLatin1String(" DARK");
//                    sts.append(st);
//                    continue;
//                }

//                if(isLight(r, g, b, &rng))
//                {
//                    st+=QLatin1String(" LIGHT");
//                    sts.append(st);
//                    continue;
//                }

//                if (isGray(r, g, b, &rng))
//                {
//                    st+=QLatin1String(" GRAY");
//                    sts.append(st);
//                    continue;
//                }

//                int ix = GetRYBIx(r,g,b,2,&rng, false, n);
//                if(ix>-1)
//                {
//                    fc[ix].Add(r, g, b, nullptr);
//                    st+=' '+QString::number(ix)+" ok";
//                }
//                sts.append(st);
//                b++;
//            }while(b);
//            g++;
//        }while(g);
//        r++;
//    }while(r);
//    com::helper::TextFileHelper::save(sts.join("\n"), "fc.txt");
//}



#c8ac98
#cbab99
#caab96
#cbac95
#c9ad95
#c8a995
#c9a996
#c8a994
#c7a992
#c5a991
#c7a896
#c5a691
#c8a793
#c7a792
#c6a891
#c4a890
#c7a694
#caa596
#c2a38e
#c3a28f
#c2a38f
#c2a48d
#c0a48d

#c3a38f
#c5a192
#c6a195
#c6a096
#c6a098
#be9d86
#be9c87
#be9d88
#bc9d87
#bd9f87
#bf9f8c
#c29c8c
#c39a8d
#c39a8e
#c39990
#bb9881
#bd9983
#ba9982
#b99980
#b89a7e
#bb9983
#bd9584
#c29787

#c19487
#c1958c
#b69279
#b5927b
#b49277
#b39276
#b19175
#b7927b
#b68d7b
#b98d7e
#bc8d80
#be9186
#b1886c
#af8870
#b0896e
#ad8b6f
#aa8b6d
#b3886e
#b38672
#b58576
#b58678
#a87f64
#a98167

#a68266
#a58163
#a38264
#ab8167
#ac7e69
#ae7f6e
#ad7e71
#a0765a
#a0795f
#9b775d
#99795d
#a2785d
#a5755f
#a57461
#946c51
#986f54
#906f54
#8f7054
#976c52
#9a6b54
#514239
#53433a
#544239

#846349
#866048
#8c624e
#895f4d
#775741
#795945
#775642
#785444
#775445
#654d3e
#644b3c
#634b3f
#664c41
#63483e
#544338
#996a58
#876249
#89634c

*/
