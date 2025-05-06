#include "charts_widget.h"

ChartsWidget::ChartsWidget(QWidget* parent) : QWidget(parent) {
    chartView = new QtCharts::QChartView(this);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(chartView);
    setLayout(layout);
}

void ChartsWidget::showSkillPieChart(const std::map<QString, int>& data) {
    auto *series = new QtCharts::QPieSeries();
    for (const auto& [skill, count] : data) {
        series->append(skill, count);
    }
    QtCharts::QChart* chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("技能热度分析");
    chartView->setChart(chart);
}

void ChartsWidget::showSalaryBarChart(const std::map<QString, double>& data) {
    auto *series = new QtCharts::QBarSeries();
    auto *set = new QtCharts::QBarSet("平均薪资");

    QStringList categories;
    for (const auto& [edu, salary] : data) {
        *set << salary;
        categories << edu;
    }

    series->append(set);
    auto *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("学历与平均薪资分布");

    auto *axisX = new QtCharts::QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    chartView->setChart(chart);
}
