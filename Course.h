#pragma once
#include <string>

#include "Level.h"

class Course
{
public:
    Course( int courseId, long startDate, long endDate, int levelId );
    Course() = delete;
    ~Course() = default;

    static int SelectCourse();
    static int SelectLevel();
    static int IdByName( std::string n )
    {
        int ind = 0;
        for ( int i = 0; i < m_ncourses; i++ )
        {
            if ( m_courses[i] == n )
            {
                ind = i;
                break;
            }
        }
        return ind;
    }

    void Fill();
    inline int GetLevel() const { return m_level; }
    inline void SetLevel( int l ) { m_level = l; }
    inline void SetId( int id ) { m_id = id; }

    inline void SetStartDate( long d ) { m_start = d; }
    inline void SetEndDate( long d ) { m_end = d; }
    inline long GetStartDate() const { return m_start; }
    inline long GetEndDate() const { return m_end; }

    void SetLevelSubMark( int level, int n, double grade ) { m_levels[level].SetSubcourseMark( n, grade); }
    void SetLevelMark( int level, double grade ) { m_levels[level].SetMark( grade ); }

    inline std::string GetName() const { return Course::m_courses[m_id]; }
    inline std::string GetStrStart() const { return std::to_string(m_start % 100) + "/" + std::to_string( (m_start / 100) % 100 ) + "/" + std::to_string( ( m_start / 10000 ) ); }
    inline std::string GetStrEnd() const { return std::to_string( m_end % 100 ) + "/" + std::to_string( ( m_end / 100 ) % 100 ) + "/" + std::to_string( ( m_end / 10000 ) ); }
    std::string GetMarks() const;
    std::string InfoMarks( int level ) const;
    double Calculate();
    std::string toString() const;
    void SetMarks( double l1, double l2, double l3, double tot );
    void SetSubcourseMarks( int level, double sb1, double sb2 );
private:
    static std::string m_courses[7];
    static const int m_ncourses = 7;

    int m_id;
    long m_start;
    long m_end;
    int m_level;
    double m_mark = -1;

    Level m_levels[3];

};

