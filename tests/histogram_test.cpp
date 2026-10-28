#include "histogram.hpp"

#include <cmath>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace
{
    int failures = 0;

    void check(bool condition, const char* message)
    {
        if (!condition)
        {
            std::cerr << "FAIL: " << message << "\n";
            ++failures;
        }
    }

    bool nearlyEqual(double a, double b, double tolerance = 1e-9)
    {
        return std::fabs(a - b) < tolerance;
    }

    template <typename Func>
    bool throwsInvalidArgument(Func func)
    {
        try
        {
            func();
        }
        catch (const std::invalid_argument&)
        {
            return true;
        }
        return false;
    }
}

int main()
{
    // Test 1: basic binning
    {
        dataviz::Histogram h({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 5);

        check(h.numBins() == 5, "numBins should be 5");
        check(nearlyEqual(h.rangeMin(), 1.0), "rangeMin should be 1");
        check(nearlyEqual(h.rangeMax(), 10.0), "rangeMax should be 10");
        check(nearlyEqual(h.binWidth(), 1.8), "binWidth should be 1.8");
        check(h.counts().size() == 5, "counts should have 5 entries");
        check(h.totalCount() == 10, "totalCount should be 10");
    }

    // Test 2: bin edges
    {
        dataviz::Histogram h({0, 10}, 4);

        const std::vector<double>& edges = h.binEdges();
        check(edges.size() == 5, "binEdges should have numBins + 1 entries");
        check(nearlyEqual(edges.front(), 0.0), "first edge should be 0");
        check(nearlyEqual(edges[1], 2.5), "second edge should be 2.5");
        check(nearlyEqual(edges.back(), 10.0), "last edge should be exactly 10");
    }

    // Test 3: exact counts per bin
    {
        // Bins: [0,2) [2,4) [4,6) [6,8) [8,10]
        dataviz::Histogram h({0, 1, 2, 3, 3, 4, 9, 10}, 5);
        const std::vector<std::size_t>& c = h.counts();

        check(c[0] == 2, "bin 0 should hold 0 and 1");
        check(c[1] == 3, "bin 1 should hold 2, 3, 3");
        check(c[2] == 1, "bin 2 should hold 4");
        check(c[3] == 0, "bin 3 should be empty");
        check(c[4] == 2, "bin 4 should hold 9 and 10");
        check(h.maxCount() == 3, "maxCount should be 3");
    }

    // Test 4: the maximum value goes into the last bin
    {
        dataviz::Histogram h({0, 5, 10}, 2);

        check(h.counts()[1] == 2, "5 and 10 should both be in the last bin");
        check(h.totalCount() == 3, "no value should be lost");
    }

    // Test 5: a value on an inner edge belongs to the upper bin
    {
        dataviz::Histogram h({0, 5, 10}, 2);

        check(h.counts()[0] == 1, "only 0 should be in the first bin");
    }

    // Test 6: all values equal (range is widened)
    {
        dataviz::Histogram h({7, 7, 7, 7}, 3);

        check(nearlyEqual(h.rangeMin(), 6.5), "rangeMin should be widened to 6.5");
        check(nearlyEqual(h.rangeMax(), 7.5), "rangeMax should be widened to 7.5");
        check(h.totalCount() == 4, "all four values should be counted");
        check(h.maxCount() == 4, "all values should share one bin");
    }

    // Test 7: single value, single bin
    {
        dataviz::Histogram h({42}, 1);

        check(h.counts().size() == 1, "one bin expected");
        check(h.counts()[0] == 1, "the bin should hold one value");
    }

    // Test 8: negative values
    {
        dataviz::Histogram h({-10, -5, 0, 5, 10}, 4);

        check(nearlyEqual(h.rangeMin(), -10.0), "rangeMin should be -10");
        check(nearlyEqual(h.rangeMax(), 10.0), "rangeMax should be 10");
        check(h.totalCount() == 5, "all five values should be counted");
    }

    // Test 9: counts always add up to the data size
    {
        std::vector<double> data;
        for (int i = 0; i < 1000; ++i)
        {
            data.push_back(std::sin(i) * 50.0);
        }

        dataviz::Histogram h(data, 17);
        check(h.totalCount() == data.size(), "totalCount should equal data size");
    }

    // Test 10: invalid input throws std::invalid_argument
    {
        check(throwsInvalidArgument([] {
            dataviz::Histogram h({}, 5);
        }), "empty data should throw");

        check(throwsInvalidArgument([] {
            dataviz::Histogram h({1, 2, 3}, 0);
        }), "zero bins should throw");

        check(throwsInvalidArgument([] {
            dataviz::Histogram h({1, std::nan(""), 3}, 3);
        }), "NaN should throw");

        check(throwsInvalidArgument([] {
            dataviz::Histogram h({1, INFINITY, 3}, 3);
        }), "infinity should throw");
    }

    if (failures == 0)
    {
        std::cout << "All Histogram tests passed.\n";
        return 0;
    }

    std::cerr << failures << " Histogram check(s) failed.\n";
    return 1;
}