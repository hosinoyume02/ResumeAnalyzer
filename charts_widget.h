#ifndef CHARTS_WIDGET_H
#define CHARTS_WIDGET_H

#include <QWidget>
#include <QtCharts>
#include <map>

class ChartsWidget : public QWidget {
public:
    ChartsWidget(QWidget* parent = nullptr);

    void showSkillPieChart(const std::map<QString, int>& data);
    void showSalaryBarChart(const std::map<QString, double>& data);

private:
    QtCharts::QChartView* chartView;
};

#endif // CHARTS_WIDGET_H
