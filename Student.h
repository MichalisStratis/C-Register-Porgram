#pragma once

#include <string>

#include "Course.h"

class Student
{
public:
    Student( std::string studentName, long studentId, int courseId, long startDate, long endDate, int levelId ) :
        m_name( studentName ),
        m_id( studentId ),
        m_course( courseId, startDate, endDate, levelId )
    { }

    Student() = delete;
    ~Student() = default;

    void FillCourse();
    inline int GetId() const { return m_id; }
    inline void SetId( long ind ) { m_id = ind; }
    inline void SetName( std::string name ) { m_name = name; }
    inline void SetCourseId( int id ) { m_course.SetId( id ); }
    
    inline void SetStartDate( long d ) { m_course.SetStartDate( d ); }
    inline void SetEndDate( long d ) { m_course.SetEndDate( d ); }
    inline long GetStartDate() const { return m_course.GetStartDate(); }
    inline long GetEndDate() const { return m_course.GetEndDate(); }

    void SetLevelSubMark( int level, int n, double grade ) { m_course.SetLevelSubMark( level, n, grade ); }
    void SetLevelMark( int level, double grade ) { m_course.SetLevelMark( level, grade ); }

    std::string toString() const;
    std::string Info() const;
    void SetMarks( double l1, double l2, double l3, double tot );
    void SetLevelSubCourseMarks( double sb1, double sb2, double sb3, double sb4, double sb5, double sb6 );
    std::string GetLevelInfo( int levelId ) const { return m_course.InfoMarks( levelId ); }

    static Student fromString( std::string& s );
    static Student FromInfo( std::string& s );

private:
    long m_id;
    std::string m_name;
    
    Course m_course;
};

