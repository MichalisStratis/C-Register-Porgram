
#pragma once
#include <string>
#include "SubCourse.h"

class Level
{
public:
    enum LevelId
    {
        EMPTY = -1, C = 0, I, H
    };

    Level() : m_level( LevelId::EMPTY ) {}
    explicit Level( int level ) : m_level( level ) {};
    ~Level() = default;

    static std::string DecodeLevel( int level );

    inline void SetLevel( int l ) { m_level = l; }
    void FillSubcourseData( int n, int aCourse, int aPort );
    double Calculate();
    double GetMark() const;
    inline void SetMark( double m ) { m_mark = m; m_sbc[0].SetCourseMark( m ); m_sbc[1].SetCourseMark( m ); }
    inline void SetSubcourseMarks( double sb1, double sb2 ) { m_sbc[0].SetCourseMark( sb1 ); m_sbc[1].SetCourseMark( sb2 ); m_mark = Calculate(); }
    inline void SetSubcourseMark( int n, double sb ) { m_sbc[n].SetCourseMark( sb ); m_mark = Calculate(); }
    inline double GetSubCourseMark( int sub ) const { return m_sbc[sub].GetCourseMark(); }

private:
    SubCourse m_sbc[2] = {};
    int m_level;
    double m_mark = -1;
};

