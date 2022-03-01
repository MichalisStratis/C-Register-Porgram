#include "Level.h"


std::string Level::DecodeLevel( int level )
{
    switch ( level )
    {
    case LevelId::C:
        return "C";
    case LevelId::I:
        return "I";
    case LevelId::H:
        return "H";
    default:
        return "";
    }
}

void Level::FillSubcourseData( int n, int aCourse, int aPort )
{
    m_sbc[n].SetCourseWorkAssesments( aCourse );
    m_sbc[n].SetPortfolioAssesments( aPort );

    m_sbc[n].Fill(m_level, n);
    m_mark = Calculate();
}

double Level::Calculate()
{
    if ( m_sbc[0].GetCourseMark() != -1 && m_sbc[1].GetCourseMark() != -1 )
        m_mark = 0.5 * m_sbc[0].GetCourseMark() + 0.5 * m_sbc[1].GetCourseMark();
    else m_mark = -1;

    return m_mark;
}

double Level::GetMark() const
{
    return m_mark;
}