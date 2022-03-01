#pragma once
#include <vector>
#include <string>


class SubCourse
{
public:
    SubCourse() = default;

    inline void SetCourseWorkAssesments( int aCourse ) { m_acourse = aCourse; }
    inline void SetPortfolioAssesments( int aPort ) { m_aportfolio = aPort; }
    void Fill(int level, int n);
    inline double GetCourseMark() const { return m_coursemark; }
    inline void SetCourseMark( double m ) { m_coursemark = m; }

private:
    int m_acourse = 0;
    int m_aportfolio = 0;
    double m_coursemark = -1;
};

std::string EvaluateMark( double mark );
std::string MarkToString( double mark );
std::string IsGoodMark( double mark );